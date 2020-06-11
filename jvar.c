#include <assert.h>
#include "jmalloc.h"
#include "jstr.h"
#include "jvar.h"


jvar * 
varCreate(){
    jvar* var = (jvar*)malloc(sizeof(struct _j_var));
    if (NULL == var) {
        return NULL;
    }
    var->type = TYPE_UNKOWN;
    return var;
}

void
varFree(jvar* var) {
    if (var->type == TYPE_OBJECT && var->value.obj.free) {
        var->value.obj.free(var->value.obj.value);
    }
    if (var->type == TYPE_STRING) {
        jsfree(var->value.str);
    }
    jfree(var);
}

int 
varType(jvar* var) {
    return (int)var->type;
}

jvar * 
varFromChar(char c){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.c = c;
    var->type = TYPE_CHAR;
    return var;
}

jvar * 
varFromUChar(char uc){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.uc = uc;
    var->type = TYPE_UCHAR;
    return var;
}

jvar * 
varFromShort(short s){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.s = s;
    var->type = TYPE_SHORT;
    return var;
}

jvar * 
varFromUShort(unsigned short us){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.us = us;
    var->type = TYPE_USHORT;
    return var;
}

jvar * 
varFromInt(int i){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.i = i;
    var->type = TYPE_INT;
    return var;
}

jvar * 
varFromUInt(unsigned int ui){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.ui = ui;
    var->type = TYPE_UINT;
    return var;
}

jvar * 
varFromLong(long l){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.l = l;
    var->type = TYPE_LONG;
    return var;
}

jvar * 
varFromULong(unsigned long ul){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.ul = ul;
    var->type = TYPE_ULONG;
    return var;
}

jvar * 
varFromLLong(long long ll){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.ll = ll;
    var->type = TYPE_LLONG;
    return var;
}

jvar * 
varFromULLong(unsigned long long ull){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.ull = ull;
    var->type = TYPE_ULLONG;
    return var;
}

jvar * 
varFromFloat(float f){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.f = f;
    var->type = TYPE_FLOAT;
    return var;
}

jvar * 
varFromDouble(double lf){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.lf = lf;
    var->type = TYPE_DOUBLE;
    return var;
}

jvar * 
varFromPoint(void * ptr){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.ptr = ptr;
    var->type = TYPE_POINT;
    return var;
}

jvar * 
varFromString(const char * str){
    jvar*var = NULL;
    if (NULL == (var = varCreate())) {
        return NULL;
    }
    var->value.str = jsinitcpy(str);
    var->type = TYPE_STRING;
    return var;

}

void
varSetChar(jvar * var, char c){
    var->value.c = c;
    var->type = TYPE_CHAR;
}

void
varSetUChar(jvar * var, char uc){
    var->value.uc = uc;
    var->type = TYPE_UCHAR;
}

void
varSetShort(jvar * var, short s){
    var->value.s = s;
    var->type = TYPE_SHORT;
}

void
varSetUShort(jvar * var, unsigned short us){
    var->value.us = us;
    var->type = TYPE_USHORT;
}

void
varSetInt(jvar * var, int i){
    var->value.i = i;
    var->type = TYPE_INT;
}

void
varSetUInt(jvar * var, unsigned int ui){
    var->value.ui = ui;
    var->type = TYPE_UINT;
}

void
varSetLong(jvar * var, long l){
    var->value.l = l;
    var->type = TYPE_LONG;
}

void
varSetULong(jvar * var, unsigned long ul){
    var->value.ul;
    var->type = TYPE_ULONG;
}

void
varSetLLong(jvar * var, long long ll){
    var->value.ll = ll;
    var->type = TYPE_LLONG;
}

void
varSetULLong(jvar * var, unsigned long long ull){
    var->value.ull = ull;
    var->type = TYPE_ULLONG;
}

void
varSetFloat(jvar * var, float f){
    var->value.f = f;
    var->type = TYPE_FLOAT;
}

void
varSetDouble(jvar * var, double lf){
    var->value.lf = lf;
    var->type = TYPE_DOUBLE;
}

void
varSetPoint(jvar * var, void * ptr){
    var->value.ptr = ptr;
    var->type = TYPE_POINT;
}

void
varSetString(jvar* var,const char * str){
    if (var->value.str) {
        jsfree(var->value.str);
    }
    var->value.str = jsinitcpy(str);
    var->type = TYPE_STRING;
}

char 
varGetChar(jvar * var){
    assert(var->type == TYPE_CHAR);
    return var->value.c;
}

unsigned char 
varGetUChar(jvar * var){
    assert(var->type == TYPE_UCHAR);
    return var->value.uc;
}

short 
varGetShort(jvar * var){
    assert(var->type == TYPE_SHORT);
    return var->value.s;
}

unsigned short 
varGetUShort(jvar * var){
    assert(var->type == TYPE_USHORT);
    return var->value.us;
}

int 
varGetInt(jvar * var){
    assert(var->type == TYPE_INT);
    return var->value.i;
}

unsigned int 
varGetUInt(jvar * var){
    assert(var->type == TYPE_UINT);
    return var->value.ui;
}

long 
varGetLong(jvar * var){
    assert(var->type == TYPE_LONG);
    return var->value.l;
}

unsigned long 
varGetULong(jvar * var){
    assert(var->type == TYPE_ULONG);
    return var->value.ul;
}

long long 
varGetLLong(jvar * var){
    assert(var->type == TYPE_LLONG);
    return var->value.ll;
}

unsigned long long 
varGetULLong(jvar * var){
    assert(var->type == TYPE_ULLONG);
    return var->value.ull;
}

float 
varGetFloat(jvar * var){
    assert(var->type == TYPE_FLOAT);
    return var->value.f;
}

double 
varGetDouble(jvar * var){
    assert(var->type == TYPE_DOUBLE);
    return var->value.lf;
}

void * 
varGetPoint(jvar * var){
    assert(var->type == TYPE_POINT);
    return var->value.ptr;
}

char * 
varGetString(jvar * var){
    assert(var->type == TYPE_STRING);
    return var->value.str;
}

//char 
//varAsChar(jvar * var){
//    assert(var->type == TYPE_CHAR || var->type == TYPE_UCHAR);
//    return var->value.c;
//}

//unsigned char 
//varAsUChar(jvar * var){
//    assert(var->type == TYPE_CHAR || var->type == TYPE_UCHAR);
//    return var->value.uc;
//}

//short 
//varAsShort(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (short)var->value.c;
//    case TYPE_UCHAR:
//        return (short)var->value.uc;
//    case TYPE_SHORT:
//        return var->value.s;
//    case TYPE_USHORT:
//        return var->value.s;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//unsigned short 
//varAsUShort(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (unsigned short)var->value.c;
//    case TYPE_UCHAR:
//        return (unsigned short)var->value.uc;
//    case TYPE_SHORT:
//        return var->value.us;
//    case TYPE_USHORT:
//        return var->value.us;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//int 
//varAsInt(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (int)var->value.c;
//    case TYPE_UCHAR:
//        return (int)var->value.uc;
//    case TYPE_SHORT:
//        return (int)var->value.s;
//    case TYPE_USHORT:
//        return (int)var->value.us;
//    case TYPE_INT:
//    case TYPE_UINT:
//        return var->value.i;
//    case TYPE_FLOAT:
//        return (int)var->value.f;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//unsigned int 
//varAsUInt(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (unsigned int)var->value.c;
//    case TYPE_UCHAR:
//        return (unsigned int)var->value.uc;
//    case TYPE_SHORT:
//        return (unsigned int)var->value.s;
//    case TYPE_USHORT:
//        return (unsigned int)var->value.us;
//    case TYPE_INT:
//    case TYPE_UINT:
//    case TYPE_LONG:
//    case TYPE_ULONG:
//        return var->value.ui;
//    case TYPE_FLOAT:
//        return (unsigned int)var->value.f;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//long varAsLong(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (long)var->value.c;
//    case TYPE_UCHAR:
//        return (long)var->value.uc;
//    case TYPE_SHORT:
//        return (long)var->value.s;
//    case TYPE_USHORT:
//        return (long)var->value.us;
//    case TYPE_INT:
//    case TYPE_UINT:
//    case TYPE_LONG:
//    case TYPE_ULONG:
//        return var->value.l;
//    case TYPE_FLOAT:
//        return (long)var->value.f;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//unsigned long 
//varAsULong(jvar * var){
//    switch (var->type) {
//    case TYPE_CHAR:
//        return (unsigned long)var->value.c;
//    case TYPE_UCHAR:
//        return (unsigned long)var->value.uc;
//    case TYPE_SHORT:
//        return (unsigned long)var->value.s;
//    case TYPE_USHORT:
//        return (unsigned long)var->value.us;
//    case TYPE_INT:
//    case TYPE_UINT:
//    case TYPE_LONG:
//    case TYPE_ULONG:
//        return var->value.l;
//    case TYPE_FLOAT:
//        return (unsigned long)var->value.f;
//    default:
//        assert(0); break;
//    }
//    return 0;
//}

//long long 
//varAsLLong(jvar * var){
//    return 0;
//}

//unsigned long long 
//varAsULLong(jvar * var){
//    return 0;
//}

//float 
//varAsFloat(jvar * var){
//    return 0.0f;
//}

//double 
//varAsDouble(jvar * var){

//}

//void * 
//varAsPoint(jvar * var){
//    assert(var->type == TYPE_POINT);
//    return var->value.ptr;
//}

//char * 
//varAsString(jvar * var){
//    assert(var->type == TYPE_STRING);
//    return var->value.str;
//}
