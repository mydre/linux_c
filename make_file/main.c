#include "fun.h"

int main(void)
{
	int a,b;
	printf("Please enter the number a and b\n");
	scanf("%d%d",&a,&b);
	int max=0;
	max = max_fun(a,b);
	printf("Themax number is %d\n",max);
	return 0;
}
