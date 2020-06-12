#ifndef JLISP_CORE_STACK_HH
#define JLISP_CORE_STACK_HH

#include <stdlib.h>

typedef void* jstacknode;
typedef struct _j_stack {
    size_t top;
    size_t unused;
    void*(*dup)(void*);
    void(*free)(void*);
    jstacknode buf[];
}jstack;


jstack* stackCreate(size_t size);
jstack* stackDup(jstack* stack);
void stackFree(jstack* stack);
jstack* stackResize(jstack* stack, size_t size);
size_t stackSizeEnlarge(jstack* stack);
jstack* stackClear(jstack* stack);
size_t stackLen(jstack* stack);
size_t stackCap(jstack* stack);

jstack* stackPush(jstack* stack,jstacknode node);
void stackPop(jstack* stack);
jstacknode stackTop(jstack* stack);


#endif//JLISP_CORE_STACK_HH
