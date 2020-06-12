#ifndef JLISP_CORE_JFUNC_HH
#define JLISP_CORE_JFUNC_HH

#include "jlibc/jstr.h"
typedef void*(*jlf_t)(void* tpArgs, void* restArgs, void* kvArgs);
typedef struct _j_lisp_func {
    js_t funcname;
    void* tpArgs;
    void* restArgs;
    void* kvArgs;
    jlf_t func;
}jlispFunc;



#endif//JLISP_CORE_JFUNC_HH
