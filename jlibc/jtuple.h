#ifndef JLISP_CORE_JTUPLE_HH
#define JLISP_CORE_JTUPLE_HH

#include <stdlib.h>
typedef struct _j_tuple {
    size_t size;
    void(*free)(void*);
    void*(*dup)(void*);
    void* buf[];
}jtuple;
typedef void* tpnode;
typedef void** jtp_t;

jtp_t tupleCreate(size_t size);
jtp_t tupleDup(jtp_t tp);
void tupleFree(jtp_t tp);

size_t tupleSize(jtp_t tp);
void* tupleGet(jtp_t tp, size_t index);
void tupleSet(jtp_t tp, size_t index, void* value);

#endif//JLISP_CORE_JTUPLE_HH
