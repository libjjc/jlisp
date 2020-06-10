#ifndef JLISP_CORE_JARRAY_HH
#define JLISP_CORE_JARRAY_HH
#include <stdlib.h>

typedef void* arraynode;
typedef struct _j_array {
    size_t len;
    size_t free;
    void*(*dup)(void*);
    int(*cmp)(void*,void*);
    void(*free)(void*);
    arraynode buf[];
}jarray;

typedef arraynode* ja_t;

size_t jarrLen(ja_t);
size_t jarrFree(ja_t);
size_t jarrSize(ja_t);
ja_t jarrCreate(size_t size);
ja_t jarrCreateWith(size_t size, void* ptr);
ja_t jarrInit(ja_t arr, void*ptr);
ja_t jarrResize(ja_t arr, size_t size);
ja_t jarrClear(ja_t arr);
void jarrRelease(ja_t arr);

void jarrSetDup(void*(*dup)(void*));
void jarrSetDup(void(*free)(void*));
void jarrSetDup(int(*cmp)(void*,void*));

ja_t jarrAdd(void* value);
ja_t jarrErase(int at);
ja_t jarrSort(ja_t arr);
ja_t jarrConcat(ja_t arr, ja_t append);
void* jarrAt(ja_t arr, int at);
size_t jarrFind(ja_t arr, size_t offset,void* key);
void jarrReverse(ja_t arr);

ja_t jarrCountAll(ja_t arr, size_t offset, void*key);
ja_t jarrFindGreater(ja_t arr, size_t offset,void* key);
ja_t jarrFindLesser(ja_t arr, size_t offset,void* key);
size_t jarrFindFirstIf(ja_t arr, size_t offset, void* key, int(*cmp)(void*, void*));
size_t* jarrFindIndexesIf(ja_t arr, size_t offset, void* key, int* olen, int(*cmp)(void*, void*));
ja_t jarrFindAll(ja_t arr, size_t offset, void*key, int(*cmp)(void*, void*));

#endif//JLISP_CORE_JARRAY_HH
