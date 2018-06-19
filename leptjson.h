#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum{ LEPT_NULL,LEPT_FALSE,LEPT_TRUE,LEPT_NUMBER,LEPT_STRING,LEPT_ARRAY,LEPT_OBJECT} lept_type;

typedef struct{
	char *s;       //表示字符
	size_t len;
	double n;     //用n去表示数字
	lept_type type;
}lept_value;

enum{
	LEPT_PARSE_OK=0,           //
	LEPT_PARSE_EXPECT_VALUE,   // JSON中含有空白
	LEPT_PARSE_INVALID_VALUE,   // 在一个值过后，在空白之后还有字符
	LEPT_PARSE_ROOT_NOT_SINGULAR  //不是三种字面值
};
int lept_parse(lept_value* v,const char* json);
lept_type lept_get_type(const lept_value* v);

double lept_get_number(const lept_value* v);

#endif