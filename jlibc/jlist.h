#ifndef JLISP_CORE_JLIST_HH
#define JLISP_CORE_JLIST_HH

#include <stdlib.h>

typedef struct _j_list_node {
    struct _j_list_node* prev;
    struct _j_list_node* next;
    void* value;
}jlistnode;

typedef struct _j_list_iter{
    jlistnode* next;
    int direction;
}jlistiter;

typedef struct _j_list {
    jlistnode* head;
    jlistnode* tail;
    void*(*dup)(void* ptr);
    void(*free)(void* ptr);
    int(*cmp)(void* ptr,void* key);
    unsigned int len;
}jlist;

enum iteratorOrder {
    ITER_TAIL = 0,
    ITER_HEAD = 1
};

jlist* listCreate(void);
void listFree(jlist* lst);
void listClear(jlist* lst);
int listEmpty(jlist* lst);
int listLen(jlist* lst);

jlist* listDup(jlist* src);
jlist* listConcat(jlist* lst, jlist* append);
jlist* listReverse(jlist* lst);
void listErase(jlist* lst, jlistnode*node);
jlistnode* listAt(jlist* lst, int at);
jlist* listPush(jlist* lst, void* value);
jlist* listPrepend(jlist* lst, void* value);
jlist* listInsert(jlist* lst, jlistnode* place, void* value);

void listSetDup(jlist* lst, void*(*dup)(void*));
void listSetCmp(jlist* lst, void*(*cmp)(void*,void*));
void listSetFree(jlist* lst, void(*free)(void*));

jlistiter* listIter(jlist* lst, int direction);
void listIterRelease(jlistiter* iter);
jlistiter* listForward(jlist* lst);
jlistiter* listBackward(jlist* lst);
jlistnode* listIterNext(jlistiter* iter);
#endif//JLISP_CORE_JLIST_HH
