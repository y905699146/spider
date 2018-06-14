#ifndef LEPTJSON_H__
#define LEPTJSON_H__

typedef enum{ LEPT_NULL,LEPT_FALSE,LEPT_TRUE,LEPT_NUMBER,LEPT_STRING,LEPT_ARRAY,LEPT_OBJECT} lept_type;

typedef struct{
	double n;     //��nȥ��ʾ����
	lept_type type;
}lept_value;

enum{
	LEPT_PARSE_OK=0,           //
	LEPT_PARSE_EXPECT_VALUE,   // JSON�к��пհ�
	LEPT_PARSE_INVALID_VALUE,   // ��һ��ֵ�����ڿհ�֮�����ַ�
	LEPT_PARSE_ROOT_NOT_SINGULAR  //������������ֵ
};
int lept_parse(lept_value* v,const char* json);
lept_type lept_get_type(const lept_value* v);

double lept_get_number(const lept_value* v);

#endif