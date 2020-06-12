#include <string.h>
#include "jmalloc.h"
#include "jtuple.h"

#define _JTP(tp) ((jtuple*)(&tp[0]-sizeof(struct _j_tuple)))
jtp_t 
tupleCreate(size_t size){
    jtuple* tp = jmalloc(sizeof(struct _j_tuple) + sizeof(jtp_t)*size);
    if (NULL == tp) {
        return NULL;
    }
    memset(&tp->buf[0], 0, size * sizeof(jtp_t));
    tp->dup = NULL;
    tp->free = NULL;
    return NULL;
}

jtp_t 
tupleDup(jtp_t tp){
    jtuple* tuple = tupleCreate(_JTP(tp)->size);
    tuple->dup = _JTP(tp)->dup;
    tuple->free = _JTP(tp)->free;
    if (tuple->dup) {
        for (int i = 0; i < _JTP(tp)->size; i++) {
            tuple->buf[i] = tuple->dup(tp[i]);
        }
        return tuple->buf;
    }
    memcpy(&tuple->buf[0], tp, sizeof(tpnode)*tuple->size);
    return tuple->buf;
}

void 
tupleFree(jtp_t tp){
    jtuple* tup = _JTP(tp);
    if (tup->free) {
        for (size_t i = 0; i < tup->size; i++) {
            tup->free(tp[i]);
        }
    }
    jfree(tup);
}

size_t 
tupleSize(jtp_t tp){
    return _JTP(tp)->size;
}

void * 
tupleGet( jtp_t tp, size_t index){
    return tp[index];
}

void 
tupleSet(jtp_t tp, size_t index, void * value){
    if (_JTP(tp)->dup) {
        tp[index] = _JTP(tp)->dup(value);
    }
    else {
        tp[index] = value;
    }
}
