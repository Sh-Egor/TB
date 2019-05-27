#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double
fx0(int m, int n, double p)
{
	double res;
	res = ((double)m - p*n)/sqrt(p*n*(1-p));
	return res;
}

double
fi(double x)
{
	double res;
	res = exp(-x*x/2);
	res /= sqrt(2*M_PI);
	return res;
}

int
main(void)
{
	int m,n;
	double p;
	printf("Введите m,n:\n");
	scanf("%d %d",&m,&n);
	printf("Введите вероятность:\n");
	scanf("%lf",&p);
	double x0 = fx0(m,n,p);
	printf("x0 = (%d - %d*%.5lf)/sqrt(%d*%.5lf*%.5lf) = %.5lf\n",m,n,p,n,p,1-p,x0);
	double res = fi(x0);
	printf("fi(x0) = 1/sqrt(2*pi) * exp(-%.5lf^2/2) = %.5lf\n",x0,res);
	res /= sqrt(p*n*(1-p));
	printf("P%d(%d) = fi(%.5lf)/sqrt(%d*%d*%.5lf) = \n%.10lf\n",n,m,x0,n,m,1-p,res);
	return 0;
}