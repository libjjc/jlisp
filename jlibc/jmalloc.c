#include "jmalloc.h"


void* 
jmalloc(size_t size) {
    return malloc(size);
}

void*
jcalloc(size_t size) {
    return calloc(1 , size);
}

void*
jrealloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

void jfree(void* ptr) {
    free(ptr);
}