#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <gsl/gsl_sf_gamma.h>

double
f(double x, double k)
{
	double res = exp(-x*x/2);
	res *= pow(x,k/2-1);
	res *= pow(0.5,k/2);
	return res;
}
int
main(void)
{	
	double x,k;
	scanf("%lf %lf",&x,&k);
	printf("%lf\n",f(x,k)/tgamma(k/2));
	return 0; 
}