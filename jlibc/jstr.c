#include <string.h>
//#include <memory.h>
#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
//#include <vadefs.h>
#include "jmalloc.h"
#include "jstr.h"
//#include "snprintf.h"

#ifdef __GNUC__
#include <unistd.h>
#endif//__GNUC
#include <stdarg.h>

#ifdef _JSP
#undef _JSP
#else
#define _JSP(s) ((struct _j_str*)(&s[0]-sizeof(struct _j_str)))
#endif//_JSP


js_t 
jsinit(char c, int len){
    struct _j_str* s = jmalloc(sizeof(struct _j_str)+len+1);
    if (!s) return 0;
    memset(&s->str[0], c, len);
    s->str[len] = 0;
    s->len = len;
    s->free = 0;
    return &s->str[0];
}

js_t
jsinitcpy(const char* str){
    if (!str) return NULL;
    int len = strlen(str);
    struct _j_str* s = (struct _j_str*)jmalloc(sizeof(struct _j_str)+len+1);
    if (!s) return 0;
    memcpy(&s->str[0],str, len);
    s->str[len] = 0;
    s->len = len;
    s->free = 0;
    return &s->str[0];
}

js_t
jsinitcpyjs(const js_t js){
    if (!js) return NULL;
    struct _j_str* s = (struct _j_str*)jmalloc(jsmemsize(js));
    if (!s) return 0;
    memcpy(&s->str[0],js, jslen(js));
    s->str[jslen(js)] = 0;
    s->len = jslen(js);
    s->free = jsavil(js);
    return &s->str[0];
}

js_t
jscpyfmt(js_t js,const char* fmt, ...){
    int size = 512;
    int len = 0;
    va_list args;
    char* buffer = jmalloc(size);
    va_start(args, fmt);
    len = vsnprintf(buffer,size, fmt, args);
    va_end(args);
    if (len > size){
        while (size < len) size *= 2;
        buffer = jrealloc(buffer, size);
        va_start(args, fmt);
        vsnprintf(buffer, size, fmt, args);
        va_end(args);
    }
    size = len;
    if (!buffer) return js;
    js = jscpy(js, buffer );
    free(buffer);
    return js;
}

js_t 
jsmkempty(){
    struct _j_str* s = jmalloc(sizeof(struct _j_str) + 1);
    s->len = s->free = 0;
    s->str[s->len] = 0;
    return &s->str[0];
}

js_t jsrep(js_t js, const char* str , const char* _rep){
    if (!js || !str) return js;
    int slen = strlen(str), pos = 0,rlen = strlen(_rep);
    while (-1 != (pos = jsfind(js, str, pos))){
        if (!(js = jsmkroom(js, slen))) return js;
        if (memmove(&js[pos + rlen], &js[pos], jslen(js) - pos - slen)){
            return js;
        }
        if (memcpy(&js[pos], _rep, rlen)){
            return js;
        }
        _JSP(js)->len += rlen - slen;
        _JSP(js)->free -= rlen - slen;
        *jsend(js) = 0;
        pos += rlen;
    }
    return js;
}

js_t
jsrepjs(js_t js, const js_t str , const js_t rep){
    if (!js || !str) return js;
    int slen = jslen(str), pos = 0,rlen = jslen(rep);
    while (-1 != (pos = jsfind(js, str, pos))){
        if (!(js = jsmkroom(js, slen))) return js;
        if (memmove(&js[pos + rlen], &js[pos], jslen(js) - pos - slen)){
            return js;
        }
        if (memcpy(&js[pos], rep, rlen)){
            return js;
        }
        _JSP(js)->len += rlen - slen;
        _JSP(js)->free -= rlen - slen;
        *jsend(js) = 0;
        pos += rlen;
    }
    return js;
}

js_t 
jsinitfmt(const char* fmt, ...){
    int size = 512;
    int len = 0;
    va_list args;
    char* buffer = jmalloc(size);
    va_start(args, fmt);
    len = vsnprintf(buffer,size, fmt, args);
    va_end(args);
    if (len > size){
        while (size < len) size *= 2;
        buffer = jrealloc(buffer, size);
        va_start(args, fmt);
        vsnprintf(buffer, size, fmt, args);
        va_end(args);
    }
    size = len;
    //char* buffer = _js_va_buffer(&size, fmt, args);
    if (!buffer) return NULL;
    struct _j_str* s = (struct _j_str*)jmalloc(sizeof(struct _j_str) + size + 1);
    if (!s) {
        free(buffer);
        return NULL;
    }
    va_end(args);
    memcpy(&s->str[0], buffer, size);
    s->free = 0;
    s->len = size;
    s->str[size] = 0;
    free(buffer);
    return &s->str[0];
}

js_t 
jscreate(const void* str, int len){
    struct _j_str* s;
    if (str){
        s = (struct _j_str*)jmalloc(sizeof(struct _j_str) + len + 1);
    }else{
        s = (struct _j_str*)jcalloc(sizeof(struct _j_str) + len + 1);
    }
    if (!s)return 0;
    if (str && len){
        memcpy(&s->str[0], str, len);
    }
    s->str[str ? len : 0] = 0;
    s->len = str ? len : 0;
    s->free = str ? 0 : len;
    return &s->str[0];
}

js_t 
jsmkroom(js_t js, int room){
    if (jsavil(js) >= room)return js;
    struct _j_str* s;
    s = (struct _j_str*)jrealloc(_JSP(js), jslen(js)+room+ 1);
    struct _j_str* os = _JSP(js);
    if (!s && os != s){
        free(os);
        return 0;
    }
    s->free += room;
    return &s->str[0];
}

void 
jsfree(js_t js){
    if (!js)return;
    struct _j_str* s = (struct _j_str*)(&js[0] - sizeof(struct _j_str));
    free(s);
}


int 
jslen(const js_t js){
    return _JSP(js)->len;
}

int 
jsavil(const js_t js){
    if (!js) return 0;
    return _JSP(js)->free;
}

char* 
jsbegin(const js_t js){
    return &_JSP(js)->str[0];
}

char* 
jsend(const js_t js){
    return &_JSP(js)->str[_JSP(js)->len];
}

int 
jssize(const js_t js){
    if (!js) return 0;
    return jslen(js) + jsavil(js);
}

int 
jsmemsize(const js_t js){
    return sizeof(struct _j_str) + jssize(js) + 1;
}

js_t 
jsresize(js_t js, char c, int size){
    struct _j_str* s = _JSP(js);
    if (jssize(js) < size || jssize(js) / 2 > size){
        s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str) + size);
        if (!s) return NULL;
    }
    memset(&s->str[0], c, size);
    return &s->str[0];
}

void 
jsclear(js_t js){
    //memset(jsbegin(js), 0, jssize(js));
    *jsbegin(js) = 0;
    _JSP(js)->free = jssize(js);
    _JSP(js)->len = 0;
}

js_t 
jscpy(js_t js, const char* str){
if (!js) return 0;
    int new_len = str ? strlen(str): 0;
    int size = jssize(js);
    struct _j_str* s = _JSP(js);
    if (size < new_len){
        s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str) + new_len + 1);
        size = new_len;
    }
    if (!s) return NULL;
    if (memcpy(&s->str[0], str, new_len)) return NULL;
    s->len = new_len;
    s->free = size < new_len? 0: size-new_len;
    s->str[new_len] = 0;
    return &s->str[0];
}

js_t 
jscpyjs(js_t js, const js_t str){
    if (!js) return 0;
    int new_len = str ? jslen(str) : 0;
    int size = jssize(js);
    struct _j_str* s = _JSP(js);
    if (size < new_len){
        s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str) + new_len + 1);
        size = new_len;
    }
    if (!s) return NULL;
    if (memcpy(&s->str[0], str, new_len)) return NULL;
    s->len = new_len;
    s->free = size < new_len? 0: size-new_len;
    s->str[new_len] = 0;
    return &s->str[0];
}

int
jsfind(js_t js, const char* str, int offset){
    if (!js || !str) return -1;
    if (offset >= jslen(js)) return -1;
    int slen = strlen(str);
   
    if (slen + offset > jslen(js)) return -1;
    
    for (int i = offset + slen; i < jslen(js); i++){
        int cur = slen;
        while (cur-- > 0){
            if (js[i + cur] != str[cur]) break;
        }
        if (-1 == cur) return i;
    }
    return -1;
}

int 
jsfindjs(js_t js, const js_t str, int offset){
    if (!js || !str) return -1;
    if (offset >= jslen(js)) return -1;
    int slen = jslen(str);
    if (slen + offset > jslen(js)) return -1;
    for (int i = offset + slen; i < jslen(js); i++){
        while (slen-- >= 0){
            if (js[i + slen] != str[slen]) break;
            if (0 == slen) return i;
        }
    }
    return -1;
}

js_t
jssubjs(const js_t js, int begin, int end){
    if (-1 == end) end = jslen(js);
    if (end < begin){
        return NULL;
    }
    int s = begin > jslen(js) ? jslen(js) : begin;
    int e = end > jslen(js) ? jslen(js) : end;
    struct _j_str* str = jmalloc(sizeof(struct _j_str) + end - begin + 1);
    if (!str)return NULL;
    memcpy(&str->str[0], &js[s], e - s);
    str->len = e - s;
    str->free = 0;
    str->str[str->len] = 0;
    return &str->str[0];
}


js_t *
jssplit(const js_t js, const char* sep, js_t* jss, int* size){
    if (!jss){
        jss = jcalloc(sizeof(js_t*)*(*size));
    }
    const char* p = js;
    const char* s = js;
    if (!size) return NULL;
    int szjs = 0;
    while (*p){
        if (strchr(sep, *p)){
            //if (p != s /*&& p - s > 1*/){
                if (szjs >= *size){
                    *size = szjs * 2;
                    js_t* ss = NULL;
                    if (jss){
                        ss = (js_t*)jrealloc(jss, sizeof(js_t)*(*size));
                    } else{
                        ss = (js_t*)jmalloc(sizeof(js_t)*(*size));
                    }
                    if (!ss){
                        while (*size-- > 0) jsfree(jss[*size]);
                        free(jss);
                        return NULL;
                    }
                    jss = ss;
                }
                if (!(jss[szjs] = jscreate(s, p - s))){
                    while (*size-- > 0) jsfree(jss[*size]);
                    free(jss);
                    return NULL;
                }
                szjs++;
            //}
            s = p;
            s++;
        }
        p++;
    }
    if (!(jss[szjs] = jscreate(s, strlen(s)))){
        while (*size-- > 0) jsfree(jss[*size]);
        free(jss);
        return NULL;
    }

    *size = szjs+1;
    return jss;
}


int 
jscmp(const js_t left, const char* right){
    if (!left) return right ? -1 : 0;
    if (!right) return left ? 1 : 0;
    int ret,ml,ll = jslen(left), lr = strlen(right);
    ml = ll > lr ? lr : ll;
    ret = memcmp(left, right, ml);
    if (!ret) return ll - lr;
    return ret;
}

int 
jscmpjs(const js_t left, const js_t right){
    if (!left) return right ? -1 : 0;
    if (!right) return left ? 1 : 0;
    int ret, ml, ll = jslen(left), lr = jslen(right);
    ml = ll > lr ? lr : ll;
    ret = memcmp(left, right, ml);
    if (!ret) return ll - lr;
    return ret;
}

js_t 
jscat(js_t js, const char* str){
    if (!js) return NULL;
    if (!str) return jsbegin(js);
    int slen = strlen(str);
    if (jsavil(js) >= slen){
        if (memcpy(jsend(js), str, slen)) return NULL;
        _JSP(js)->len += slen;
        _JSP(js)->free -= slen;
        *jsend(js) = 0;
        return &_JSP(js)->str[0];
    }
    struct _j_str* s;
    s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str) + jssize(js) + slen + 1);
    if (!s) return NULL;
    if (memcpy(&s->str[s->len], str, slen)) return NULL;
    s->len += slen, s->free = 0;
    s->str[s->len] = 0;
    return &s->str[0];
}

js_t 
jscatjs(js_t js, const js_t str){
    if (!js) return NULL;
    if (!str) return jsbegin(js);
    int slen = jslen(str);
    if (jsavil(js) >= slen){
        if (memcpy(jsend(js), str, slen)) return NULL;
        _JSP(js)->len += slen;
        _JSP(js)->free -= slen;
        *jsend(js) = 0;
        return jsbegin(js);
    }
    struct _j_str* s;
    s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str)+jssize(js) + slen+1);
    if (!s) return NULL;
    if (memcpy(&s->str[s->len], str, slen)) return NULL;
    s->len += slen, s->free = 0;
    s->str[s->len] = 0;
    return s->str;
}

js_t
jscatlen(js_t js, const char* str, int len){
    if (!js) return NULL;
    if (!str) return jsbegin(js);
    int slen = len;
    if (jsavil(js) >= slen){
        if (memcpy(jsend(js), str, slen)) return NULL;
        _JSP(js)->len += slen;
        _JSP(js)->free -= slen;
        *jsend(js) = 0;
        return jsbegin(js);
    }
    struct _j_str* s;
    s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str)+jssize(js) + slen+1);
    if (!s) return NULL;
    if (memcpy(&s->str[s->len], str, slen)) return NULL;
    s->len += slen, s->free = 0;
    s->str[s->len] = 0;
    return s->str;
}

js_t 
jslower(js_t js){
    char* p = jsbegin(js), *q = jsend(js);
    for (; p != q; p++)
        *p = tolower(*p);
    return js;
}

js_t 
jsupper(js_t js){
    char* p = jsbegin(js), *q = jsend(js);
    for (; p != q; p++)
        *p = toupper(*p);
    return js;
}

js_t 
jstrim(js_t js){
    char* p = jsbegin(js);
    char* q = jsend(js)-1;
    for (; p <= q ;){
        if (*p != ' ' && *q != ' ') break;
        if (*p == ' ') p++;
        if (*q == ' '&&p != q) q--;
    }
    int len = p > q ? 0 : q - p + 1;
    memmove(jsbegin(js), p, len);
    _JSP(js)->free += jssize(js) - len;
    _JSP(js)->len = len;
    *jsend(js) = 0;
    return jsbegin(js);
}

js_t 
jstrimstr(js_t js,const char* str){
    char* p = jsbegin(js);
    char* q = jsend(js)-1;
    for (; p <= q ;){
        if (!strchr(str, *p) && !strchr(str, *q)) break;
        if (strchr(str,*p)) p++;
        if (strchr(str,*q)) q--;
    }
    int len = p > q ? 0 : q - p + 1;
    memmove(jsbegin(js), p, len);
    _JSP(js)->free += jssize(js) - len;
    _JSP(js)->len = len;
    *jsend(js) = 0;
    return jsbegin(js);
}

js_t 
jscatfmt(js_t js, char* fmt, ...){
    int size = 512;
    int len = 0;
    va_list args;
    char* buffer = jmalloc(size);
    va_start(args, fmt);
    len = vsnprintf(buffer,size, fmt, args);
    va_end(args);
    if (len > size){
        while (size < len) size *= 2;
        buffer = jrealloc(buffer, size);
        va_start(args, fmt);
        vsnprintf(buffer, size, fmt, args);
        va_end(args);
    }
    //struct _j_str* s = _JSP(js);
    size = len;
    js = jscat(js, buffer);
    free(buffer);
    //s->len += size;
    //s->str[s->len] = 0;
    return js;
}
       

js_t 
jsformat(js_t js,char* fmt, ...){
    if (!js)return NULL;
    int size = 0;
    va_list args;
    va_start(args, fmt);
    char* buffer = _js_va_buffer(&size, fmt, args);
    if (!buffer)return NULL;
    struct _j_str* s = _JSP(js);
    if (jslen(js) + jsavil(js) < size){
        struct _j_str* s;
        if (NULL == (s = (struct _j_str*)jrealloc(_JSP(js), sizeof(struct _j_str)+size))){
            free(buffer);
            return NULL;
        }
    }
    if (memcpy(&s->str[0], buffer, size)){
        free(buffer);
        return NULL;
    }
    s->free = jslen(js) + jsavil(js) - size;
    s->len = size;
    return &s->str[0];
}

char* 
_js_va_buffer(int* size, char* fmt, char* args){
    if (!fmt||!size) return NULL;
    *size = *size ? *size : 512;
    char* buf = (char*)jmalloc(sizeof(char)*(*size));

    while (1) {
        va_list args_copy;

#if defined(_MSC_VER) || defined(__BORLANDC__)
        args_copy = args;
#else
        va_copy(args_copy, args);
#endif

        int n = vsnprintf(buf, *size, fmt, args_copy);

        va_end(args_copy);

        if ((n > -1) && (n < *size)) {
            *size = n;
            break;
        }

        *size = (n > -1) ? n + 1 : *size * 2;

        free(buf);
        buf = (js_t)jmalloc(sizeof(char)*(*size));
    }
    return buf;
}

