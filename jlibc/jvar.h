#ifndef _JLISP_CORE_JVAR_HH
#define _JLISP_CORE_JVAR_HH

typedef struct _j_var {
    union {
        char c;
        unsigned char uc;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long l;
        unsigned long ul;
        long long ll;
        unsigned long long ull;
        float f;
        double lf;
        void* ptr;
        char* str;
        struct {
            void*(*dup)(void*);
            void(*free)(void*);
            void* value;
        }obj;
    }value;
    enum {
        TYPE_UNKOWN,
        TYPE_CHAR,
        TYPE_UCHAR,
        TYPE_SHORT,
        TYPE_USHORT,
        TYPE_INT,
        TYPE_UINT,
        TYPE_LONG,
        TYPE_ULONG,
        TYPE_LLONG,
        TYPE_ULLONG,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_POINT,
        TYPE_STRING,
        TYPE_OBJECT
    }type;
}jvar;

jvar* varCreate();
void varFree(jvar* var);
int varType(jvar* var);

jvar* varFromChar(char c);
jvar* varFromUChar(char uc);
jvar* varFromShort(short s);
jvar* varFromUShort(unsigned short us);
jvar* varFromInt(int i);
jvar* varFromUInt(unsigned int ui);
jvar* varFromLong(long l);
jvar* varFromULong(unsigned long ul);
jvar* varFromLLong(long long ll );
jvar* varFromULLong(unsigned long long ull);
jvar* varFromFloat(float f);
jvar* varFromDouble(double lf);
jvar* varFromPoint(void* ptr);
jvar* varFromString(const char* str);

void varSetChar(jvar* var,char c);
void varSetUChar(jvar* var,char uc);
void varSetShort(jvar* var,short s);
void varSetUShort(jvar* var,unsigned short us);
void varSetInt(jvar* var,int i);
void varSetUInt(jvar* var,unsigned int ui);
void varSetLong(jvar* var,long l);
void varSetULong(jvar* var,unsigned long ul);
void varSetLLong(jvar* var,long long ll );
void varSetULLong(jvar* var,unsigned long long ull);
void varSetFloat(jvar* var,float f);
void varSetDouble(jvar* var,double lf);
void varSetPoint(jvar* var,void* ptr);
void varSetString(jvar* var,const char* str);

char varGetChar(jvar* var);
unsigned char varGetUChar(jvar* var);
short varGetShort(jvar* var);
unsigned short varGetUShort(jvar* var);
int varGetInt(jvar* var);
unsigned int varGetUInt(jvar* var);
long varGetLong(jvar* var);
unsigned long  varGetULong(jvar* var);
long long varGetLLong(jvar* var);
unsigned long long varGetULLong(jvar* var);
float varGetFloat(jvar* var);
double varGetDouble(jvar* var);
void* varGetPoint(jvar* var);
char* varGetString(jvar* var);

//char varAsChar(jvar* var);
//unsigned char varAsUChar(jvar* var);
//short varAsShort(jvar* var);
//unsigned short varAsUShort(jvar* var);
//int varAsInt(jvar* var);
//unsigned int varAsUInt(jvar* var);
//long varAsLong(jvar* var);
//unsigned long  varAsULong(jvar* var);
//long long varAsLLong(jvar* var);
//unsigned long long varAsULLong(jvar* var);
//float varAsFloat(jvar* var);
//double varAsDouble(jvar* var);
//void* varAsPoint(jvar* var);
//char* varAsString(jvar* var);

#endif//_JLISP_CORE_JVAR_HH
