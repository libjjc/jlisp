#ifndef JLISP_MALLOC_HH
#define JLISP_MALLOC_HH

#include <malloc.h>

void* jmalloc(size_t size);

void* jcalloc(size_t size);

void* jrealloc(void* ptr, size_t size);

void jfree(void* ptr);

#endif//JLISP_MALLOC_HH
