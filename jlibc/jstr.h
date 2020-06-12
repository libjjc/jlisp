#ifndef JLISP_CORE_JSTR_HH
#define JLISP_CORE_JSTR_HH


/**
 * @author j.j.c
 * @date 4/12/2017
 * @note
 *      1. logstr�ַ�����һ����C�ַ������м��װ�װ���ַ������������ϡ�
 *      2. ÿ��logstr�ַ�������Ҫ��ʹ�ý�����ͨ��jsfree�����ͷš�
 *      3. �ڴ������������ڴ����һ�������뷵�����Ͳ�����Ϊjs_t�ĺ���ʱ��
 *         �������Խ��Ϊself������ֵҲ��self�����Ǵ����self�뷵�ص�self
 *         ��ַ���ܲ�һ������ˣ�ʹ��ʱ����ã���أ�ʹ��������ʽ���е��á�
 *         exp��   js_t s = jsfunc(s,param);
 */


typedef char* js_t;
struct _j_str{
    int len;
    int free;
    char str[];
};

/**
 * @brief
 *      ���ڳ�ʼ��logstr���൱�ڴ���һ��logstr����
 * @param c
 *      �������logstr������ڴ�ռ䡣
 * @param len
 *      ȷ��logstr���ڴ�ռ��С�����ַ�������ĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      s1 == "aaaaa";
 * @note
 *      ÿһ��������logstr������Ҫͨ��jsfree���ͷ��ڴ档
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
 *      ����һ���յ�logstr�ַ�����
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      js_t emy = js_mkempty();
 *      emy == "";
 * @note
 *      �����ǿյ��ַ�����Ҳ��Ҫͨ��jsfree���ͷš�
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t
jsmkempty();


/**
 * @brief
 *      ͨ���ɱ��������ʼ��һ��logstr����
 * @param fmt
 *      ��ʽ���ַ�������������֪��C����printf��ʽһ�¡�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      js_t s1 = jsinitfmt("%d,%s",2017,"Welcome!");
 *      s1 == "2017,Welcome!";
 * @note
 *      ÿһ��������logstr������Ҫͨ��jsfree���ͷ��ڴ档
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t
jsinitfmt(const char* fmt, ...);


/**
 * @brief
 *      ͨ�����е�����������logstr����
 * @param str
 *      ���ڹ���logstr��������ݵ�ַ��
 * @param len
 *      �������ݵĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      js_t s1 = jscreate('Hello World!',12);
 *      s1 == "Hello World!";
 * @note
 *      ÿһ��������logstr������Ҫͨ��jsfree���ͷ��ڴ档
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
js_t 
jscreate(const void* str,int len);


/**
 * @brief
 *      Ϊ���е�logstr���󴴽�����ı��ÿռ䡣
 * @param js
 *      ��Ҫ��������ռ���ַ�����
 * @param room
 *      ������Ҫ�Ŀռ�ߴ��С.
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
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
 *      �ͷ�logstr������ڴ�ռ䡣ÿһ��logstr������Ҫ��ʹ�ý���������ͷš�
 * @param js
 *      ��Ҫ�����ڴ�ռ��ͷŵ��ַ�����
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      jsfree(s1);
 * @note
 *      ÿһ��������logstr������Ҫͨ��jsfree���ͷ��ڴ档
 * @see
 *      jsinit,jsmkempty,jscreate,jsinitfmt,jsfree
 */
void 
jsfree(js_t js);


/**
 * @brief
 *      ���ڷ���logstr�ַ����ĳ��ȣ��൱��C����strlen��
 * @param js
 *      ��Ҫ�����س��ȵ��ַ�����
 * @return
 *      js�ַ����ĳ��ȡ�
 * @exzample
 *      js_t s1 = jsint('a',5);
 *      5 == jslen(s1);
 * @note
 *      �μ�struct _log_str����
 * @see
 *      jsresize,jssize,jslen,jsavil,jsmemsize
 */
int 
jslen(const js_t js);


/**
 * @brief
 *      ���ڷ���logstr�ַ������ÿռ�ĳ���.
 * @param js
 *      ��Ҫ�����ؿ��ÿռ䳤�ȵ��ַ�����
 * @return
 *      js�ַ����Ŀ��ÿռ䳤�ȡ�
 * @exzample
 *      js_t s1 = jsint('a',5);
 *       s1 = jsmkroom(s1,3);
 *       3 == jsavil(s1);
 * @note
 *      �μ�struct _log_str����
 * @see
 *      jsresize,jssize,jslen,jsavil,jsmemsize
 */
int
jsavil(const js_t js);


/**
 * @brief
 *      ����logstr�ַ������׵�ַ��
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
 *      ����logstr�ַ�����β����ַ��
 * @see
 *      jsbegin
 */
char*
jsend(const js_t js);


/**
 * @brief
 *      ����logstr�ַ����Ŀռ�ߴ磬�����ַ�����������ÿռ䡣
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
 *      ����logstr�ַ�����ռ�õ��ڴ�ռ�ߴ硣�����ַ����ߴ��Լ��ṹ������ڴ档
 * @exzample
 *      jsmemsize(s) == jssize(s)+sizeof(struct _log_str)+1
 * @see
 *      jslen,jsavil,jssize
 */
int 
jsmemsize(const js_t js);


/**
 * @brief
 *      ��������ռ䲢��䡣
 * @param c
 *      �������logstr������ڴ�ռ䡣
 * @param size
 *      ȷ��logstr���ڴ�ռ��С�����ַ�������ĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
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
 *      ���logstr�ַ������������������ַ���������Ӱ�����ڴ�ռ�ı䶯��
 */
void
jsclear(js_t js);

/**
 * @brief
 *      �����ַ�������str�ַ��������ݿ�����js�С�
 * @note
 *      �����ַ������ܻ�Ӱ�쵽ԭ��logstr�ַ������ڴ�ռ䣬�����ַ�������ԶԶС������
 *      logstr�ַ����Ŀռ�ʱ��logstr�ַ����ռ����н���������
 * @see
 *      jscpyjs
 */
js_t 
jscpy(js_t js,const char* str);


/**
 * @brief
 *      �����ַ�������str�ַ��������ݿ�����js�С�
 * @note
 *      1.�����ַ������ܻ�Ӱ�쵽ԭ��logstr�ַ������ڴ�ռ䣬�����ַ�������ԶԶС������
 *      logstr�ַ����Ŀռ�ʱ��logstr�ַ����ռ����н���������
 *      2.��jscpy��ͬ����jscpyjs��ʾ����������Դ����Ҳ��һ��logstr
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
 *      �����Ƚ������ַ���������ͬʱ����0����C ����strcmp��memcmp���ơ�
 */
int 
jscmp(const js_t left, const char* right);


/**
 * @brief
 *      �����Ƚ������ַ���������ͬʱ����0����C ����strcmp��memcmp���ơ�
 * @note
 *      ��jscmp��ͬ����jscmpjs��ʾ����������Դ����Ҳ��һ��logstr
 */
int 
jscmpjs(const js_t left, const js_t right);


/**
 * @brief
 *      ��str�ַ������ӵ�js�ַ���β�������ء�
 */
js_t 
jscat(js_t js,const char* str);


/**
 * @brief
 *      ��str�ַ������ӵ�js�ַ���β�������ء�
 * @note
 *      ��jscat��ͬ����jscatjs��ʾ����������Դ����Ҳ��һ��logstr
 */
js_t
jscatjs(js_t js, const js_t str);

/**
 * @brief
 *      ��str�ַ������ӵ�js�ַ���β�������ء�
 * @note
 *      ��jscat��ͬ����jscatjs��ʾ����������Դ���ݵ�һ�����ȣ�������ȫ����
 */
js_t
jscatlen(js_t js, const char* str, int len);


/**
 * @brief
 *      ��js�ַ���ȫ��ת��ΪСд��ĸ��������
 */
js_t
jslower(js_t js);


/**
 * @brief
 *      ��js�ַ���ȫ��ת��Ϊ��д��ĸ��������
 */
js_t
jsupper(js_t js);


/**
 * @brief
 *      ����js�ַ�������β���ַ���������
 */
js_t
jstrim(js_t js);

js_t
jstrimstr(js_t js, const char* str);

/**
 * @brief
 *      ͨ���ɱ����������һ���ַ�����
 * @param fmt
 *      ��ʽ���ַ�������������֪��C����printf��ʽһ�¡�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
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
 *      ��js�ַ������½��и�ʽ����
 * @exzample
 * @note
 */
js_t 
jsformat(js_t js,char* fmt, ...);


/**
 * @brief
 *      �ַ����Ŀ��ӻ�������snprintf.cʵ�֡�
 * @param size
 *      ���봫��һ���������Ҳ���ΪNULL��������һ��size֮�����Ȼ��ɸ�size������̽�Եĸ�ʽ����
 *      ����ռ䲻������size���з���������㹻���򷵻������ָ���ַ��
 * @return
 *      ���ظ�ʽ��֮����ַ����ĵ�ַ
 */
char*
_js_va_buffer( int* size,char* fmt, char* args);



#endif//JLISP_CORE_JSTR_HH
