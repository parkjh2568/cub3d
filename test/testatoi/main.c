#include <stdio.h>

extern int ft_atoi(const char *str);

int main()
{
	char a[10] = "1942  1988";
	int d;

	d = ft_atoi(a);
	printf("%d",d);
}
