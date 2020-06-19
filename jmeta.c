#include <stdlib.h>
#include "jmeta.h"

extern int jl_type_id[] = {
    JLT_NIL,
    JLT_NUMBER,
    JLT_REAL,
    JLT_RATIONAL,
    JLT_RATIO,
    JLT_INT,
    JLT_BIGNUM,
    JLT_FIXNUM,
    JLT_FLOAT,
    JLT_SHORT_FLOAT,
    JLT_SINGLE_FLOAT,
    JLT_DOUBLE_FLOAT,
    JLT_LONG_FLOAT,
    JLT_SYMBOL,
    JLT_STRING,
    JLT_LIST,
    JLT_ARRAY,
    JLT_DICT,
    JLT_ATOM,
    JLT_FUNCTION,
    JLT_T
};

jmeta_t 
metaCreate(){
    jmeta* meta = (jmeta*)malloc(sizeof(jmeta));
    if (NULL == meta) {
        return NULL;
    }
    meta->type = JLT_UNKOWN;
    meta->meta = NULL;
    return (jmeta_t)meta->meta;
}

jmeta_t 
metaCreateInt(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_INT;
    return meta;
}

jmeta_t 
metaCreateFloat(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_FLOAT;
    return meta;
}

jmeta_t 
metaCreateDouble(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_DOUBLE_FLOAT;
    return meta;
}

jmeta_t 
metaCreateList(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_LIST;
    return meta;
}

jmeta_t 
metaCreateArray(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_ARRAY;
    return meta;
}

jmeta_t metaCreateDict(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_DICT;
    return meta;
}

jmeta_t 
metaCreateString(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_STRING;
    return meta;
}

jmeta_t 
metaCreateAtom(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_ATOM;
    return meta;
}

jmeta_t 
metaCreateFunc(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_FUNCTION;
    return meta;
}

jmeta_t 
metaCreateNil(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_NIL;
    return meta;
}

jmeta_t 
metaCreateT(){
    jmeta_t meta = metaCreate();
    if (meta == 0) {
        return 0;
    }
    JMETA(meta)->type = JLT_T;
    return meta;
}
