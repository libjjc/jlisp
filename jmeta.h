#ifndef JLISP_CORE_JMETA_HH
#define JLISP_CORE_JMETA_HH
#include "jlibc/jdict.h"

typedef struct _j_context {
    struct jcontext* outer;
    dict_t dict;
}jcontext;

#define JL_TYPEID_WIDTH 0x6A
#define JL_TYPEIDX_WIDTH 0x06
typedef enum {
    JLI_NIL              ,
    JLI_NUMBER           ,
    JLI_REAL             ,
    JLI_RATIONAL         ,
    JLI_RATIO            ,
    JLI_INT              ,
    JLI_BIGNUM           ,
    JLI_FIXNUM           ,
    JLI_FLOAT            ,
    JLI_SHORT_FLOAT      ,
    JLI_SINGLE_FLOAT     ,
    JLI_DOUBLE_FLOAT     ,
    JLI_LONG_FLOAT       ,
    JLI_SYMBOL           ,
    JLI_STRING           ,
    JLI_LIST             ,
    JLI_ARRAY            ,
    JLI_DICT             ,
    JLI_ATOM             ,
    JLI_FUNCTION         ,
    JLI_T                ,
    JLI_SIZE
}JL_IDX;

typedef enum {
    JLT_UNKOWN           =   0x00,
    JLT_NIL              =   0x01<<0,
    JLT_NUMBER           =   0x01<<1,
    JLT_REAL             =   0x01<<2|JLT_NUMBER,
    JLT_RATIONAL         =   0x01<<3|JLT_REAL,
    JLT_RATIO            =   0x01<<4|JLT_RATIONAL,
    JLT_INT              =   0x01<<5|JLT_RATIONAL,
    JLT_BIGNUM           =   0x01<<6|JLT_INT,
    JLT_FIXNUM           =   0x01<<7|JLT_INT,
    JLT_FLOAT            =   0x01<<8|JLT_REAL,
    JLT_SHORT_FLOAT      =   0x01<<9|JLT_FLOAT,
    JLT_SINGLE_FLOAT     =   0x01<<10|JLT_FLOAT,
    JLT_DOUBLE_FLOAT     =   0x01<<11|JLT_FLOAT,
    JLT_LONG_FLOAT       =   0x01<<12|JLT_FLOAT,
    JLT_SYMBOL           =   0x01<<13,
    JLT_STRING           =   0x01<<14,
    JLT_LIST             =   0x01<<15,
    JLT_ARRAY            =   0x01<<16,
    JLT_DICT             =   0x01<<17,
    JLT_ATOM             =   0x01<<18,
    JLT_FUNCTION         =   0x01<<19,
    JLT_T                =   0x01<<20,
}JL_TYPEID;

typedef enum {
    JL_NIL              =   JLT_NIL|(JLI_NIL<<JL_TYPEID_WIDTH),
    JL_NUMBER           =   0x01<<1|(JLI_NUMBER<<JL_TYPEID_WIDTH),
    JL_REAL             =   0x01<<2|JLT_NUMBER|(JLI_REAL<<JL_TYPEID_WIDTH),
    JL_RATIONAL         =   0x01<<3|JLT_REAL|(JLI_RATIONAL<<JL_TYPEID_WIDTH),
    JL_RATIO            =   0x01<<4|JLT_RATIONAL|(JLI_RATIO<<JL_TYPEID_WIDTH),
    JL_INT              =   0x01<<5|JLT_RATIONAL|(JLI_INT<<JL_TYPEID_WIDTH),
    JL_BIGNUM           =   0x01<<6|JLT_INT|(JLI_BIGNUM<<JL_TYPEID_WIDTH),
    JL_FIXNUM           =   0x01<<7|JLT_INT|(JLI_FIXNUM<<JL_TYPEID_WIDTH),
    JL_FLOAT            =   0x01<<8|JLT_REAL|(JLI_FLOAT<<JL_TYPEID_WIDTH),
    JL_SHORT_FLOAT      =   0x01<<9|JLT_FLOAT|(JLI_SHORT_FLOAT<<JL_TYPEID_WIDTH),
    JL_SINGLE_FLOAT     =   0x01<<10|JLT_FLOAT|(JLI_SINGLE_FLOAT<<JL_TYPEID_WIDTH),
    JL_DOUBLE_FLOAT     =   0x01<<11|JLT_FLOAT|(JLI_DOUBLE_FLOAT<<JL_TYPEID_WIDTH),
    JL_LONG_FLOAT       =   0x01<<12|JLT_FLOAT|(JLI_LONG_FLOAT<<JL_TYPEID_WIDTH),
    JL_SYMBOL           =   0x01<<13|(JLI_SYMBOL<<JL_TYPEID_WIDTH),
    JL_STRING           =   0x01<<14|(JLI_STRING<<JL_TYPEID_WIDTH),
    JL_LIST             =   0x01<<15|(JLI_LIST<<JL_TYPEID_WIDTH),
    JL_ARRAY            =   0x01<<16|(JLI_ARRAY<<JL_TYPEID_WIDTH),
    JL_DICT             =   0x01<<17|(JLI_DICT<<JL_TYPEID_WIDTH),
    JL_ATOM             =   0x01<<18|(JLI_ATOM<<JL_TYPEID_WIDTH),
    JL_FUNCTION         =   0x01<<19|(JLI_FUNCTION<<JL_TYPEID_WIDTH),
    JL_T                =   0x01<<20|(JLI_T<<JL_TYPEID_WIDTH)
}JL_TYPE;

int jl_type_id[];

#define getJLTypeIndex(type) (0xFF&((type)>>TL_TYPEID_WIDTH))
#define getJLTypeID(type) (0xFFFFFFFF&((type)&0x03FFFFFF))

typedef struct _j_real {
    void* value;
}jreal;

typedef struct _j_ratio{
    int n;
    int d;
}jratio;

typedef struct _j_bignum {
    void* value;
}jbignum;

typedef struct _j_fixnum {
    int value;
}jfixnum;

typedef struct _j_shortfloat {
    void* value;
}jsfloat;

typedef struct _j_floatfloat {
    float value;
}jfloat;

typedef struct _j_doublefloat {
    double value;
}jdouble;

typedef struct _j_longfloat {
    long double value;
}jlfloat;

typedef struct _j_complex {
    jreal real;
    jreal imag;
}jcomplex;

typedef struct _j_meta {
    JL_TYPE type;
    void* meta;
}jmeta;
typedef void* jmetadata;
typedef unsigned long jmeta_t;
#define JMETA(obj) ((jmeta*)((char*)obj - ((unsigned long)(&(((jmeta*)0)->meta)))))
#define getMetaType(metaObj) JMETA(metaObj)->type

jmeta_t metaCreate();
jmeta_t metaCreateInt();
jmeta_t metaCreateFloat();
jmeta_t metaCreateDouble();
jmeta_t metaCreateList();
jmeta_t metaCreateArray();
jmeta_t metaCreateDict();
jmeta_t metaCreateString();
jmeta_t metaCreateAtom();
jmeta_t metaCreateFunc();
jmeta_t metaCreateNil();
jmeta_t metaCreateT();


#endif//JLISP_CORE_JMETA_HH

