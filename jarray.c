#include <string.h>
#include "jmalloc.h"
#include "jarray.h"

#define _JAP(ja) ((struct _j_array*)(&ja[0]-sizeof(struct _j_array)))

size_t 
jarrLen(ja_t arr){
    return _JAP(arr)->len;
}

size_t 
jarrUnused(ja_t arr){
    return _JAP(arr)->unused;
}

size_t 
jarrCap(ja_t arr){
    return _JAP(arr)->len + _JAP(arr)->unused;
}

ja_t 
jarrCreate(size_t size){
    jarray* arr = NULL;
    if (NULL == (arr = (jarray*)jmalloc(sizeof(jarray) + size * sizeof(arraynode)))) {
        return NULL;
    }
    arr->dup = NULL;
    arr->cmp = NULL;
    arr->free = NULL;
    arr->len = 0;
    arr->unused = size;
    return &arr->buf[0];
}

ja_t 
jarrResize(ja_t arr, size_t size){
    jarray* o = _JAP(arr);
    jarray* a = NULL;
    if (NULL == (a = jarrCreate(size))) {
        return NULL;
    }

    memcpy(&a->buf[0], arr, (size < _JAP(arr)->len) ? size : _JAP(arr)->len);
    a->len = o->len;
    a->unused = size - a->len;
    jarrRelease(arr);
    return a;
}

ja_t 
jarrClear(ja_t arr){
    jarray* a = _JAP(arr);
    while (a->len--) {
        if (a->free) {
            a->free(a->buf[a->len]);
        }
        else {
            jfree(a->buf[a->len]);
        }
    }
    a->len = 0;
    return arr;
}

void 
jarrRelease(ja_t arr){
    jarrClear(arr);
    jfree(_JAP(arr));
}

void 
jarrSetDup(ja_t arr,void *(*dup)(void *)){
    _JAP(arr)->dup = dup;
}

void 
jarrSetDup(ja_t arr,void(*free)(void *)){
    _JAP(arr)->free = free;
}

void 
jarrSetDup(ja_t arr,int(*cmp)(void *, void *)){
    _JAP(arr)->cmp = cmp;
}

size_t 
jarrEnlarge(ja_t arr){
    if (_JAP(arr)->len == 0) return 1;
    return _JAP(arr)->len + 1 + _JAP(arr)->len / 2;
}

ja_t 
jarrAdd(ja_t arr,void * value){
    if (_JAP(arr)->unused) {
        arr[_JAP(arr)->len] = value;
        _JAP(arr)->len++;
        _JAP(arr)->unused--;
        return arr;
    }
    jarray* a = jarrResize(arr, jarrEnlarge(arr));
    if (NULL == a) {
        return NULL;
    }
    a->buf[a->len] = value;
    a->unused--;
    return &a->buf[0];
}

ja_t 
jarrErase(ja_t arr,int at){
    if (at >= _JAP(arr)->len) {
        return arr;
    }
    memcpy(arr[at], arr[at + 1], sizeof(arraynode)*(_JAP(arr)->len - at - 1));
    _JAP(arr)->len--;
    _JAP(arr)->unused++;
    return arr;
}


ja_t 
jarrConcat(ja_t arr, ja_t append){
    size_t newsize = jarrCap(arr);
    while (newsize < jarrCap(arr) + jarrLen(append)) {
        newsize = jarrEnlarge(arr);
    }
    arr = jarrResize(arr, newsize);
    memcpy(&arr[_JAP(arr)->len], append, sizeof(arraynode)*_JAP(append)->len);
    _JAP(arr)->len += _JAP(append)->len;
    _JAP(arr)->unused -= _JAP(append)->unused;
    return arr;
}

void * 
jarrAt(ja_t arr, int at){
    if (at >= _JAP(arr)->len) {
        return NULL;
    }
    return arr[at];
}

size_t 
jarrFind(ja_t arr, size_t offset, void * key){
    if (_JAP(arr)->cmp) {
        for (int i = offset; i < _JAP(arr)->len; i++) {
            if (0 == _JAP(arr)->cmp(arr[i], key)) {
                return i;
            }
        }
        return -1;
    }

    for (int i = offset; i < _JAP(arr)->len; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

void 
jarrReverse(ja_t arr){
    if (_JAP(arr)->len <= 1)return;
    size_t i = 0, j = _JAP(arr)->len - 1;
    arraynode* tmp = NULL;
    while (i < j) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        i++;
        j--;
    }
}

size_t 
jarrCountAll(ja_t arr, size_t offset, void * key){
    size_t count = 0;
    if (_JAP(arr)->cmp) {
        for (int i = offset; i < _JAP(arr)->len; i++) {
            if (0 == _JAP(arr)->cmp(arr[i], key)) {
                count++;
            }
        }
    }
    else {
        for (int i = offset; i < _JAP(arr)->len; i++) {
            if (arr[i], key) {
                count++;
            }
        }
    }
    return count;
}

size_t 
jarrFindFirstIf(ja_t arr, size_t offset, void * key, int(*cmp)(void *, void *)){
    for (int i = offset; i < _JAP(arr)->len; i++) {
        if (0 == cmp(arr[i], key)) {
            return i;
        }
    }
    return -1;
}

