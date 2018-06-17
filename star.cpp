#include<iostream>
namespace Home
{
	class Forever_Love
	{
		private:
			const double love=2;
			double y,x,z;
		public:
			void ML();
	};
}
using namespace Home;
int main()
{
	long long Ago=0;
	unsigned long Forever=2;
	Forever_Love YOU;
	do
	{
		YOU.ML();
		Ago++;
	}
	while(Ago<Forever);
	getchar();
	return 520;
}
void Forever_Love::ML()
{
	for(y=love;y>-love;y -=0.06*love)
	{
		for(x=-love;x<love;x+=0.03*love)
		{
			z=x*x+y*y-0.6*love;
			std::cout<<(z*z*z-x*x*y*y*y<=0.0?'*':' ');
		}
		std::cout<<std::endl;
	}
}
