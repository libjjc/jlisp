#ifndef JLISP_CORE_JARRAY_HH
#define JLISP_CORE_JARRAY_HH
#include <stdlib.h>

typedef void* arraynode;
typedef struct _j_array {
    size_t len;
    size_t unused;
    void*(*dup)(void*);
    int(*cmp)(void*,void*);
    void(*free)(void*);
    arraynode buf[];
}jarray;

typedef arraynode* ja_t;

size_t jarrLen(ja_t arr);
size_t jarrUnused(ja_t arr);
size_t jarrCap(ja_t arr);
ja_t jarrCreate(size_t size);
ja_t jarrResize(ja_t arr, size_t size);
ja_t jarrClear(ja_t arr);
void jarrRelease(ja_t arr);

void jarrSetDup(ja_t arr,void*(*dup)(void*));
void jarrSetDup(ja_t arr,void(*free)(void*));
void jarrSetDup(ja_t arr,int(*cmp)(void*,void*));

size_t jarrEnlarge(ja_t arr);

ja_t jarrAdd(ja_t arr,void* value);
ja_t jarrErase(ja_t arr,int at);
ja_t jarrConcat(ja_t arr, ja_t append);
void* jarrAt(ja_t arr, int at);
size_t jarrFind(ja_t arr, size_t offset,void* key);
void jarrReverse(ja_t arr);

size_t jarrCountAll(ja_t arr, size_t offset, void*key);
size_t jarrFindFirstIf(ja_t arr, size_t offset, void* key, int(*cmp)(void*, void*));

#endif//JLISP_CORE_JARRAY_HH
