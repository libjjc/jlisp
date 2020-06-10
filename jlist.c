#include "jmalloc.h"
#include "jlist.h"

#define LSTLEN(l) ((l)->len)
#define LSTHEAD(l) ((l)->head)
#define LSTNODETAIL(l) ((l)->tail)
#define LSTNODEPREV(n) ((n)->prev)
#define LSTNEXT(n) ((n))->next)
#define LSTNODEVALUE(n) ((n)->value)

jlist * 
listCreate(void){
    jlist* lst = (jlist*)jmalloc(sizeof(struct _j_list));
    if (NULL == lst) {
        return NULL;
    }
    lst->head = NULL;
    lst->tail = NULL;
    lst->dup = NULL;
    lst->free = NULL;
    lst->cmp = NULL;
    lst->len = 0;
    return lst;
}

void 
listFree(jlist * lst){
    listClear(lst);
    jfree(lst);
}

void listClear(jlist * lst){
    jlistnode* cur = lst->head;
    jlistnode* next = NULL;
    while (lst->len--) {
        next = cur->next;
        if (lst->free) {
            lst->free(cur->value);
        }
        jfree(cur);
        cur = next;
    }
    lst->head = lst->tail = NULL;
    lst->len = 0;
}

int listEmpty(jlist * lst){
    return lst->len%1;
}

int listLen(jlist * lst){
    return lst->len;
}

jlist * listDup(jlist * src){
    jlist* dup = NULL;
    jlistnode* node = NULL;
    void* value = NULL;
    if (NULL == (dup = listCreate())) return dup;
    dup->dup = src->dup;
    dup->cmp = src->cmp;
    dup->free = src->free;

    jlistiter* iter = listForward(src);
    while (NULL != (node = listIterNext(iter))) {
        if (dup->dup) {
            if (NULL == (value = dup->dup(node->value))) {
                listFree(dup);
                listIterRelease(iter);
                return NULL;
            }
        }
        else {
            value = node->value;
        }
        if (NULL == listPush(dup, value)) {
            listIterRelease(iter);
            listFree(dup);
            return NULL;
        }
    }
    
    return dup;
}

jlist * listConcat(jlist * lst, jlist * append){
    if (append->head) append->head->next = lst->tail;
    if (lst->tail) {
        lst->tail->next = append->head;
    }
    else {
        lst->head = append->head;
    }
    if (append->tail)lst->tail = append->tail;
    lst->len += append->len;
    append->len = 0;
    return lst;
}

jlist * listReverse(jlist * lst){
    if (lst->len <= 1)return lst;
    jlistiter* itr = listForward(lst);
    jlistnode* cur = NULL, *next = NULL, *prev = NULL;
    while (NULL != (cur = listIterNext(itr))) {
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        cur = next;
        prev = cur;
    }
    listIterRelease(itr);
    return lst;
}

void listErase(jlist * lst, jlistnode * node) {
    if (node->prev) {
        node->prev->next = node->next;
    }
    else {
        lst->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    else {
        lst->tail = node->prev;
    }
    if (lst->free) lst->free(node->value);
    jfree(node);
    lst->len--;
}

jlistnode * listAt(jlist * lst, int at){
    jlistnode* node = NULL;
    jlistiter* iter = listIter(lst, at < 0 ? 0 : 1);
    if (at < 0) at = -1 * at + 1;
    while (at-- && (NULL != (node = listIterNext(iter))));
    listIterRelease(iter);
    return node;
}

jlist * listPush(jlist * lst, void * value){
    jlistnode* node = NULL;
    if (NULL == (node = (jlistnode*)jmalloc(sizeof(struct _j_list_node)))) {
        return NULL;
    }
    node->value = value;
    node->prev = node->next = NULL;
    if (lst->tail) {
        lst->tail->next = node;
        node->prev = lst->tail;
        lst->tail = node;
    }
    else {
        lst->head = lst->tail = node;
    }
    lst->len++;
    return lst;
}

jlist * listPrepend(jlist * lst, void * value){
    jlistnode* node = NULL;
    if (NULL == (node = (jlistnode*)jmalloc(sizeof(struct _j_list_node)))) {
        return NULL;
    }
    node->value = value;
    node->prev = node->next = NULL;
    if (lst->head) {
        node->next = lst->head;
        lst->head->prev = node;
        lst->head = node;
    }
    else {
        lst->head = lst->tail = node;
    }
    return lst;
}

jlist * listInsert(jlist * lst, jlistnode * place, void * value){
    jlistnode* node = NULL;
    if (NULL == (node = (jlistnode*)jmalloc(sizeof(struct _j_list_node)))) {
        return NULL;
    }
    node->value = value;
    node->prev = node->next = NULL;
    if (place->next) {
        node->next = place->next;
        place->next->prev = node;
        place->next = node;
        node->prev = place->prev;
    }
    else {
        place->next = node;
        node->prev = place;
        lst->tail = node;
    }
    lst->len++;
    return lst;
}

void listSetDup(jlist * lst, void *(*dup)(void *)){
    lst->dup = dup;
}

void listSetCmp(jlist * lst, void *(*cmp)(void *, void *)){
    lst->cmp = cmp;
}

void listSetFree(jlist * lst, void (*free)(void *)){
    lst->free = free;
}

jlistiter * listIter(jlist * lst, int direction){
    return direction ? listForward(lst) : listBackward(lst);
}

void listIterRelease(jlistiter * iter){
    jfree(iter);
}

jlistiter * listForward(jlist * lst){
    jlistiter* iter = NULL;
    if (NULL == (iter = (jlistiter*)jmalloc(sizeof(struct _j_list_iter)))) {
        return NULL;
    }
    iter->next = lst->head;
    iter->direction = ITER_HEAD;
    return iter;
}

jlistiter * listBackward(jlist * lst){
    jlistiter* iter = NULL;
    if (NULL == (iter = (jlistiter*)jmalloc(sizeof(struct _j_list_iter)))) {
        return NULL;
    }
    iter->next = lst->tail;
    iter->direction = ITER_TAIL;
    return iter;
}

jlistnode * listIterNext(jlistiter * iter){
    jlistnode* cur = iter->next;
    if (NULL == cur) {
        return NULL;
    }
    iter->next = iter->direction == ITER_HEAD ? cur->next : cur->prev;
    return cur;
}
