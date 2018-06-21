#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum{ LEPT_NULL,LEPT_FALSE,LEPT_TRUE,LEPT_NUMBER,LEPT_STRING,LEPT_ARRAY,LEPT_OBJECT} lept_type;

typedef struct{
	union{
		struct { char* s; size_t len; }s;  //表示字符
		double n;					//表示数字     
	}
	lept_type type;
}lept_value;

enum{
	LEPT_PARSE_OK=0,           //
	LEPT_PARSE_EXPECT_VALUE,   // JSON中含有空白
	LEPT_PARSE_INVALID_VALUE,   // 在一个值过后，在空白之后还有字符
	LEPT_PARSE_ROOT_NOT_SINGULAR  //不是三种字面值
};
#define lept_init(v) do{ (v)->type=LEPT_NULL; }while (0)
int lept_parse(lept_value* v,const char* json);
lept_type lept_get_type(const lept_value* v);

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v,int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v,double n);

void lept_free(lept_value* v);

#define lept_set_null(v) lept_free(v)
const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);

void lept_set_string(lept_value* v,const char* s,size_t len);
#endif