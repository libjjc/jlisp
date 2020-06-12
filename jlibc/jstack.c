#include "jmalloc.h"
#include "jstack.h"

jstack* 
stackCreate(size_t size) {
    jstack* stack = NULL;
    if (NULL == (stack = (jstack*)malloc(sizeof(jstack) + sizeof(jstacknode)*size))) {
        return stack;
    }
    stack->top = 0;
    stack->unused = size;
    stack->dup = NULL;
    stack->free = NULL;
    return stack;
}

jstack * 
stackDup(jstack * stack){
    jstack* stk = stackCreate(stackCap(stack));
    if (NULL == stk) {
        return NULL;
    }
    stk->dup = stack->dup;
    stk->free = stk->free;
    while (stk->top < stack->top) {
        stackPush(stk, 
            stk->dup ? (stk->dup(stack->buf[stk->top])) : (stack->buf[stk->top]));
    }
    return stk;
}

void 
stackFree(jstack * stack){
    stackClear(stack);
    jfree(stack);
}

jstack * 
stackResize(jstack * stack, size_t size){
    jstack* stk = stackCreate(size);
    size_t _size = stack->top < size ? stack->top : size;
    memcpy(&stk->buf[0], &stack->buf[0], sizeof(jstacknode)*_size);
    stk->top = _size;
    stk->unused = size - _size;
    stk->dup = stack->dup;
    stk->free = stack->free;
    stackFree(stack);
    return stk;
}

size_t 
stackSizeEnlarge(jstack * stack){
    if (stack->top <= 3) return stack->top + 1;
    return (size_t)(stack->top * 1.5);
}

jstack * 
stackClear(jstack * stack){
    return NULL;
}

int 
stackLen(jstack * stack){
    stack->top;
}

size_t 
stackCap(jstack * stack){
    return stack->top + stack->unused;
}

jstack* 
stackPush(jstack * stack, jstacknode node){
    if (stack->unused) {
        stack->buf[stack->top++] = node;
        stack->unused--;
        return stack;
    }
    stack = stackResize(stack, stackSizeEnlarge(stack));
    return stackPush(stack, node);
}

void
stackPop(jstack * stack){
    if (stack->top) {
        if (stack->free) {
            stack->free(stack->buf[stack->top]);
        }
        stack->top--;
        stack->unused++;
    }
}

jstacknode 
stackTop(jstack * stack){
    if (stack->top) {
        return stack->buf[stack->top - 1];
    }
    return NULL;
}
