struct F{
	int f;
	void func(){
		f=3;
		auto x=[&](){
			if(--f==0)
				d();
		};
	a(x);
	b(x);
	c(x);
	}
}func_obj;
///////////////////////
struct Context{
	  ///
};
struct F:public Context{
	int  f;
	void (*caller_next_func)(context*);
	Context* caller_pointer;
	void func(){
		f=3;
		auto x=[&](){
			if(--f==0){
				d();
				caller_next_func(caller_pointer);
			}
		};
		a(x);
		b(x);
		c(x);
	}
}func_obj;