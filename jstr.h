#ifndef JLISP_CORE_JSTR_HH
#define JLISP_CORE_JSTR_HH


/**
 * @author j.j.c
 * @date 4/12/2017
 * @note
 *      1. logstr字符串是一个对C字符串进行简易包装的字符串处理函数集合。
 *      2. 每个logstr字符串都需要在使用结束后通过jsfree进行释放。
 *      3. 在处理函数的所有在传入第一个参数与返回类型参数均为js_t的函数时，
 *         参数可以解读为self，返回值也是self。但是传入的self与返回的self
 *         地址可能不一样。因此，使用时，最好（务必）使用如下形式进行调用。
 *         exp：   js_t s = jsfunc(s,param);
 */


typedef char* js_t;
struct _j_str{
    int len;
    int free;
    char str[];
};

/**
 * @brief
 *      用于初始化logstr，相当于创建一个logstr对象。
 * @param c
 *      用来填充logstr对象的内存空间。
 * @param len
 *      确定logstr的内存空间大小，即字符串所需的长度。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      s1 == "aaaaa";
 * @note
 *      每一个创建的logstr对象都需要通过jsfree来释放内存。
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t 
jsinit(char c, int len);


js_t
jsinitcpy(const char* str);


js_t
jsinitcpyjs(const js_t js);

js_t
jscpyfmt(js_t js,const char* fmt, ...);

js_t
jsrep(js_t js, const char* old,const char* _rep);

js_t
jsrepjs(js_t js, const js_t str,const js_t _rep);




/**
 * @brief
 *      创建一个空的logstr字符串。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t emy = js_mkempty();
 *      emy == "";
 * @note
 *      即便是空的字符串，也需要通过jsfree来释放。
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t
jsmkempty();


/**
 * @brief
 *      通过可变变量来初始化一个logstr对象。
 * @param fmt
 *      格式化字符串，与我们熟知的C函数printf格式一致。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t s1 = jsinitfmt("%d,%s",2017,"Welcome!");
 *      s1 == "2017,Welcome!";
 * @note
 *      每一个创建的logstr对象都需要通过jsfree来释放内存。
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t
jsinitfmt(const char* fmt, ...);


/**
 * @brief
 *      通过已有的数据来构造logstr对象。
 * @param str
 *      用于构造logstr对象的数据地址。
 * @param len
 *      已有数据的长度。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t s1 = jscreate('Hello World!',12);
 *      s1 == "Hello World!";
 * @note
 *      每一个创建的logstr对象都需要通过jsfree来释放内存。
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t 
jscreate(const void* str,int len);


/**
 * @brief
 *      为已有的logstr对象创建额外的备用空间。
 * @param js
 *      需要创建额外空间的字符串。
 * @param room
 *      额外需要的空间尺寸大小.
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      s1 == "aaaaa";
 *      jssize(s1) == 5;
 *      s1 = jsmkroom(s1,12);
 *      jssize(s1) == 17;
 *      jsavil(s1) == 12;
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t
jsmkroom(js_t js, int room);


/**
 * @brief
 *      释放logstr对象的内存空间。每一个logstr对象都需要在使用结束后进行释放。
 * @param js
 *      需要进行内存空间释放的字符串。
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      jsfree(s1);
 * @note
 *      每一个创建的logstr对象都需要通过jsfree来释放内存。
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
void 
jsfree(js_t js);


/**
 * @brief
 *      用于返回logstr字符串的长度，相当于C函数strlen。
 * @param js
 *      需要被返回长度的字符串。
 * @return
 *      js字符串的长度。
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      5 == jslen(s1);
 * @note
 *      参见struct _log_str定义
 * @see
 *      jsresize,jssize,jslen,jsavil,jsmemsize
 */
int 
jslen(const js_t js);


/**
 * @brief
 *      用于返回logstr字符串可用空间的长度.
 * @param js
 *      需要被返回可用空间长度的字符串。
 * @return
 *      js字符串的可用空间长度。
 * @exzample
 *      js_t s1 = jsint('a',5);
 *       s1 = jsmkroom(s1,3);
 *       3 == jsavil(s1);
 * @note
 *      参见struct _log_str定义
 * @see
 *      jsresize,jssize,jslen,jsavil,jsmemsize
 */
int
jsavil(const js_t js);


/**
 * @brief
 *      返回logstr字符串的首地址。
 * @exzample
 *      js_t s1 = jscreate("Hello World!",12);
 *      s1 == jsbegin(s1);
 * @see
 *      jsend
 */
char*
jsbegin(const js_t js);


/**
 * @brief
 *      返回logstr字符串的尾部地址。
 * @see
 *      jsbegin
 */
char*
jsend(const js_t js);


/**
 * @brief
 *      返回logstr字符串的空间尺寸，包括字符串长度与可用空间。
 * @exzample
 *      jslen(s)+jsavil(s) == jssize(s)
 * @note
 * @see
 *      jslen,jsavil
 */
int 
jssize(const js_t js);


/**
 * @brief
 *      返回logstr字符串所占用的内存空间尺寸。包括字符串尺寸以及结构本身的内存。
 * @exzample
 *      jsmemsize(s) == jssize(s)+sizeof(struct _log_str)+1
 * @see
 *      jslen,jsavil,jssize
 */
int 
jsmemsize(const js_t js);


/**
 * @brief
 *      重新申请空间并填充。
 * @param c
 *      用来填充logstr对象的内存空间。
 * @param size
 *      确定logstr的内存空间大小，即字符串所需的长度。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      js_t s = jsmkempty();
 *      s = jsresize(s,0,5);
 *      5 == jssize(5);
 * @note
 *      ...
 */
js_t
jsresize(js_t js,char c, int size);


/**
 * @brief
 *      清楚logstr字符串，这里仅仅是清空字符串，并不影响其内存空间的变动。
 */
void
jsclear(js_t js);

/**
 * @brief
 *      拷贝字符串，将str字符串中内容拷贝到js中。
 * @note
 *      拷贝字符串可能会影响到原有logstr字符串的内存空间，当新字符串长度远远小于现有
 *      logstr字符串的空间时，logstr字符串空间会进行紧缩操作。
 * @see
 *      jscpyjs
 */
js_t 
jscpy(js_t js,const char* str);


/**
 * @brief
 *      拷贝字符串，将str字符串中内容拷贝到js中。
 * @note
 *      1.拷贝字符串可能会影响到原有logstr字符串的内存空间，当新字符串长度远远小于现有
 *      logstr字符串的空间时，logstr字符串空间会进行紧缩操作。
 *      2.余jscpy不同的是jscpyjs表示用来拷贝的源数据也是一个logstr
 * @see
 *      jscpyjs
 */
js_t
jscpyjs(js_t js, const js_t str);


int
jsfind(js_t js, const char* str ,int offset);


int
jsfindjs(js_t js, const js_t str, int offset);


js_t
jssubjs(const js_t js, int begin, int end);


js_t*
jssplit(const js_t js, const char* sep, js_t* jss, int *size);


/**
 * @brief
 *      用来比较两个字符串，当相同时返回0，与C 函数strcmp，memcmp相似。
 */
int 
jscmp(const js_t left, const char* right);


/**
 * @brief
 *      用来比较两个字符串，当相同时返回0，与C 函数strcmp，memcmp相似。
 * @note
 *      与jscmp不同的是jscmpjs表示用来拷贝的源数据也是一个logstr
 */
int 
jscmpjs(const js_t left, const js_t right);


/**
 * @brief
 *      将str字符串连接到js字符串尾部并返回。
 */
js_t 
jscat(js_t js,const char* str);


/**
 * @brief
 *      将str字符串连接到js字符串尾部并返回。
 * @note
 *      与jscat不同的是jscatjs表示用来拷贝的源数据也是一个logstr
 */
js_t
jscatjs(js_t js, const js_t str);

/**
 * @brief
 *      将str字符串连接到js字符串尾部并返回。
 * @note
 *      与jscat不同的是jscatjs表示用来拷贝的源数据的一定长度，而并非全部。
 */
js_t
jscatlen(js_t js, const char* str, int len);


/**
 * @brief
 *      将js字符串全部转换为小写字母，并返回
 */
js_t
jslower(js_t js);


/**
 * @brief
 *      将js字符串全部转换为大写字母，并返回
 */
js_t
jsupper(js_t js);


/**
 * @brief
 *      消除js字符串的收尾空字符，并返回
 */
js_t
jstrim(js_t js);

js_t
jstrimstr(js_t js, const char* str);

/**
 * @brief
 *      通过可变变量来连接一个字符串。
 * @param fmt
 *      格式化字符串，与我们熟知的C函数printf格式一致。
 * @return
 *      返回logstr对象的数据（字符串）空间地址。
 * @exzample
 *      s1 == "Here we come";
 *      js_t s1 = jscatfmt(s1 ,"%d,%s",2017,"Welcome!");
 *      s1 == "Here we come2017,Welcome!";
 * @note
 *      
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t 
jscatfmt(js_t js, char* fmt, ...);


/**
 * @brief
 *      将js字符串重新进行格式化。
 * @exzample
 * @note
 */
js_t 
jsformat(js_t js,char* fmt, ...);


/**
 * @brief
 *      字符串的可视化处理，由snprintf.c实现。
 * @param size
 *      必须传入一个参数，且不能为NULL，当传入一个size之后，首先会由该size进行试探性的格式化，
 *      如果空间不够，则将size进行翻倍。如果足够，则返回申请的指针地址。
 * @return
 *      返回格式化之后的字符串的地址
 */
char*
_js_va_buffer( int* size,char* fmt, char* args);



#endif//JLISP_CORE_JSTR_HH
