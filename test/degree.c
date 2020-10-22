#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897
double get_rad(int num)
{
	return ( num * (PI/180));
}

int main()
{
	printf("%lf",sin(get_rad(60)));
}
