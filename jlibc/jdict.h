#ifndef JLISP_CORE_JDICT_HH
#define JLISP_CORE_JDICT_HH

typedef long long i64_t;
typedef unsigned long long u64_t;

typedef float f32_t;
typedef double f64_t;
typedef long double f128_t;

/**
 * dict �ڵ�
 * key ��ʾ�ڵ�ؼ���
 * val ��ʾ�ڵ�ֵ
 * next ��ʾ��һ���ڵ�
 */
struct _dict_entity {
    void* key;
    union _dict_val {
        void* ptv;
        i64_t i64;
        u64_t u64;
        f64_t f64;
    };
    union _dict_val val;
    struct _dict_entity* next;
};

/**
 * һ���ֵ�dict��ʵ�֣���������C++template class�е�typename T
 * hash ��һ��hash����ָ��
 * keycmp ��dict��key�ıȽϺ���
 * keydup ��dict��key�Ŀ�������
 * valdup ��dict��value�Ŀ�������
 * keyfree ��dict��key���ͷź���
 * valfree ��dict��value���ͷź���
 */
struct _dict_impl {
    int(*hash)(void*);
    int(*keycmp)(void*, void*);
    void*(*keydup)(void*);
    void*(*valdup)(void*);
    void(*keyfree)(void*);
    void(*valfree)(void*);
};

/**
 * ��ʾһ��dict
 * impl ��ʾһ��dict��ʵ��������C++�е�template<T>
 * size ��ʾdict�Ŀռ��С
 * used ��ʾ�Ѿ�ʹ�õĿռ��С��������Ѿ�ʹ�õĿռ��С��ʾ����dict�����нڵ�ĺ�
 * table ��ʾdict������
 */
struct _dict {
    struct _dict_impl* impl;
    unsigned long used;
    unsigned long size;
    struct _dict_entity** table;
};

/**
 * ��������dict�ĵ�������
 * d ��Ҫ���е�����dict
 * i ��ǰ�������Ƕ����еĵڼ�������
 * e ��ǰ������ʵ��
 * next ��һ����Ҫ������ʵ��
 */
struct _dict_iterator {
    struct _dict * d;
    unsigned long i;
    struct _dict_entity* e;
    struct _dict_entity* next;
};

typedef struct _dict_entity* dt_entity_t;
typedef struct _dict_impl* dt_impl_t;
typedef struct _dict* dict_t;
typedef struct _dict_iterator* dt_iterator_t;

typedef int(*callback_foreach)(dict_t dict, dt_entity_t);


/**
 * ����dict d �� e ��key Ϊ k
 */
#define dt_set_key(d,e,k)\
    do{if((d)->impl->keydup){(e)->key = (d)->impl->keydup(k);}else{(e)->key = (k);}}while(0)

/**
 * �ͷ�dict  d  �е�ʵ�� e
 */
#define dt_free_key(d,e)\
    do{ if((d)->impl->keyfree)(d)->impl->keyfree((e)->key);}while(0)

/**
 * ����dict d �е�ʵ�� e ��ֵΪ v
 */
#define dt_set_val(d,e,v)\
    do{if((d)->impl->valdup){(e)->val.ptv = (d)->impl->valdup(v);}else{(e)->val.ptv = (v);}}while(0)

/**
 *  �ͷ�dict�ڵ�e
 */
#define dt_free_val(d,e)\
    do{ if((d)->impl->valfree)(d)->impl->valfree((e)->val.ptv);}while(0)

/**
 * ���� �ͻ�ȡ int64 unsigned int64 double ��ֵ
 */
#define dt_set_val_i64(e,v)do{(e)->val.i64 = v;}while(0)
#define dt_set_val_u64(e,v)do{(e)->val.u64 = v;}while(0)
#define dt_set_val_f64(e,v)do{(e)->val.f64 = v;}while(0)

#define dt_get_val_i64(e) (e)->val.i64
#define dt_get_val_u64(e) (e)->val.u64
#define dt_get_val_f64(e) (e)->val.f64

/**
 * keyֵ�Ƚ�
 */
#define dt_key_cmp(d,k1,k2)\
    ((d)->impl->keycmp ? (d)->impl->keycmp((k1),(k2)) : (k1) == (k2))

/**
 * ����k��hash
 */
#define dt_hash_key(d,k)\
    ((d)->impl->hash(k))
    
/**
 * @brief
 *      ����һ��dict
 * @param impl
 *      ��Ҫ������dict��ʵ�����ͣ��൱��C++�е�template<typename T>
 * @return
 *      �ɹ��򷵻�һ��dict������NULL
 */
dict_t
dtcreate(dt_impl_t impl);

/**
 * @brief
 *      ����һ��dict����dtcreate��ͬ�������ｫ��ʼ��һ����С��
 * @param impl
 *      ��Ҫ������dict��ʵ�����ͣ��൱��C++�е�template<typename T>
 * @param size
 *      dict �ĳ�ʼ��С
 * @return
 *      �ɹ��򷵻�һ��dict������NULL
 */
dict_t
dtinit(dt_impl_t impl, unsigned long size);

/**
 * @brief
 *      �ͷ�dict�Ŀռ�
 * @param dict
 *      ��Ҫ�ͷŵ�dict�ռ�
 */
void
dtfree(dict_t dict);

/**
 * @brief
 *      ������������һ��keyΪkey����valueΪval�Ľڵ�
 * @param dict
 *      ��Ҫ�����������õ�dict
 * @param key
 *      ��Ҫ�����������õĽڵ��key
 * @param val
 *      ��Ҫ�����������õĽڵ��value
 * @return
 *      �ɹ��򷵻�0������-1
 */
int
dtset(dict_t dict, void* key, void* val);

/**
 * @brief
 *      ������������һ��dict��keyΪkey�Ľڵ㣬�����ظýڵ�
 * @param dict
 *      ��Ҫ�����������ýڵ��dict
 * @param key
 *      ��Ҫ�����������ýڵ��key
 * @return
 *      ���ش���������Ҫ�������õĽڵ㣬����ֱ�ӽ���д����Ӧ���͵�ֵ��
 */
dt_entity_t
dtsetraw(dict_t dict, void* key);

/**
 * @brief
 *      ʵ�����൱�����ǳ�������set***��������ʱ���key�������򲻻ᴴ����������-1.
 * @return
 *      ���óɹ��򷵻�0�����򷵻�-1
 */
int
dtreplace(dict_t dict, void* key, void* val);

/**
 * @brief �൱��set������Ӧ��setraw����
 */
dt_entity_t
dtrepraw(dict_t dict, void* key);

/**
 * @brief
 *      ɾ��dict��keyΪkey�Ľڵ�
 */
int
dtdelete(dict_t dict, void* key);

/**
 * @brief
 *      ����dict��Ϊkey�Ľڵ㲢���ظýڵ�
 * @return
 *      ������ҵ��򷵻ظýڵ㣬���򷵻�NULL
 */
dt_entity_t
dtfind(dict_t dict, void* key);

/**
 * @brief
 *      ���¼�������dict��hash
 * @param dict
 *      ��Ҫ���¼����dict
 * @return
 *      ������ɺ�Ϊһ��ȫ�µ�dict
 */
dict_t
dtrehash(dict_t dict);
/**
 * ����dict
 * @param foreach
 *      dict �ı�������
 * @return
 *      �ɹ��򷵻�0������-1
 */
int
dtforeach(dict_t dict, callback_foreach foreach);

/**
 * @brief
 *      dict�ĵ�������
 * @param dict
 *      ��Ҫ������dict
 * @return
 *      ����dict�ĵ�һ���ڵ�
 */
dt_iterator_t
dtiterator(dict_t dict);

/**
 * @brief
 *      ������һ���ڵ㣬���������ܺ󷵻�NULL
 */
dt_entity_t
dtnext(dict_t dict, dt_iterator_t entity);

/**
 * @brief
 *      �ͷ�dict�ĵ�����
 */
void
dtfreeitr(dt_iterator_t itr);

/**
 * @brief
 *      ����dict��size
 */
unsigned long
dtsize(dict_t dict);

/**
 * @brief
 *      ����dict�е�ʵ��ռ��
 */
unsigned long
dtused(dict_t dict);

/**
 * @brief
 *      ����dict�е����нڵ���
 * @param dict
 * @return
 */
unsigned long
dtcount(dict_t dict);

/**
 * @brief
 *      ����������keyֵhashһ�µĽڵ�����
 */
unsigned long
dtcountkey(dict_t dict, void* key);

/**
 * okovstrimp
 *      short for "owner key owner value string implement"
 *      ˽�е�key˽�е�value���ַ���Ϊkey��ʵ�ַ�ʽ
 * oksvstrimpl
 *      short for "owner key share value string implement"
 *      ˽�е�key�����value���ַ���Ϊkey��ʵ�ַ�ʽ
 *
 * �൱��template<typename T> �е�T
 * ����ֱ��dtcreate(&okovstrimpl)������һ���µ�dict
 */
extern struct _dict_impl okovstrimpl;
extern struct _dict_impl oksvstrimpl;

#endif//JLISP_CORE_JDICT_HH