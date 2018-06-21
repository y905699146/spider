#include<assert.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h>
#include<string.h>
#include"leptjson.h"


#define EXPECT(c,ch) do{ assert(*c->json==(ch)); c->json++; }while(0)
#define ISDIGIT(ch) ((ch)>='0'&&(ch)<='9')
#define ISDIGIT1TO9 ((ch)>='1'&&(ch)<='9')
#define PUTC(c,ch) do{ *(char*)lept_context_push(c,sizeof(char))==(ch); }while(0)
typedef struct{
	char* stack;
	size_t size,top;
	const char* json;
}lept_context;

static void* lept_context_push(lept_context* c,size_t size){
	void* ret;
	assert(size>0);
	if(c->top + size>=c->size)
	{
		if(c->size==0)
			c->size=LEPT_PARSE_STACK_INIT_SIZE;
		while(c->top+size>=c->size)
			c->size+=c->size>>1;
		c->stack=(char*)realloc(c->stack,c->size);
	}
	ret=c->stack+c->top;
	c->top +=size;
	return ret;
}
static void* lept_context_pop(lept_context* c,size_t size)
{
	assert(c->top >=size);
	return c->stack + (c->top -=size);
}
int lept_parse(lept_value* v,const char* json)
{
	lept_context c;
	assert(v !=NULL);
	c.json=json;
	v->type=LEPT_NULL;
	lept_parse_whitespace(&c);
	if ((ret = lept_parse_value(&c,v))==LEPT_PARSE_OK)
	{
		lept_parse_whitespace(&c);
		if(*c.json!='\0')
			ret=LEPT_PARSE_ROOT_NOT_SINGULAR;
	}
	return ret;
}
static int lept_parse_literal(lept_context* c,lept_value* v,const char* literal,lept_type type)
{
	size_t i;
	EXPECT(c,literal[0]);
	for(i=0;literal[i+1];i++)
		if (c->json[i]!=literal[i+1])
		{
			return LEPT_PARSE_INVALID_VALUE;
		}
	c->json +=i;
	v->type=type;
	return LEPT_PARSE_OK;
}

static int lept_parse_number(lept_context* c,lept_value* v)
{
	const char* p=c->json;
	if(*p=='-')   p++;
	if(*p=='0')   p++;
	else
	{
		if(!ISDIGIT1TO9(*p))   return LEPT_PARSE_INVALID_VALUE;
		for (p++;ISDIGIT(*p) ;p++ );
	}
	if(*p=='.')
	{
		p++;
		if(!ISDIGIT(*p))
			return LEPT_PARSE_INVALID_VALUE;
		for (p++;ISDIGIT(*p) ;p++ );
	}
	if(*p=='e'||*p=='E')
	{
		p++;
		if(*p=='+'||*p=='-')
			p++;
		if(!ISDIGIT(*p))       return LEPT_PARSE_INVALID_VALUE;
		for (p++;ISDIGIT(*p) ;p++ );
	}
	errno=0;
	v->n=strtod(c->json,NULL);
	if (errno == ERANGE && (v->n == HUGE_VAL || v->n == -HUGE_VAL))
        return LEPT_PARSE_NUMBER_TOO_BIG;
    v->type = LEPT_NUMBER;
    c->json = p;
    return LEPT_PARSE_OK;
} 

static int lept_parse_string(lept_context* c,lept_value* v)
{
	size_t head=c->top,len;
	const char* p;
	p=c->json;
	for(;;)
	{
		char ch=*p++;
		switch(ch)
		{
			case '\"':
		}
	}
}

static int lept_parse_value(lept_context* c,lept_value* v)
{
	switch(*c->json)
	{
		case 't':  return lept_parse_literal(c, v, "true", LEPT_TRUE);
        case 'f':  return lept_parse_literal(c, v, "false", LEPT_FALSE);
        case 'n':  return lept_parse_literal(c, v, "null", LEPT_NULL);
        default:   return lept_parse_number(c, v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
	}
}

static void lept_parse_whitespace(lept_context *c)
{
	const char *p=c->json;
	while(*p==' ' || *p=='\t' || *p=='\n' || *p=='\r')
		p++;
	c->json=p;
}

lept_type lept_get_type(const lept_value *v)
{
	assert(v!=NULL);
	return v->type;
}

double lept_get_number(const lept_value* v)
{
	assert(v!=NULL && v->type == LEPT_NUMBER);
	return v->n;
}