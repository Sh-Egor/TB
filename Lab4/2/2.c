#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

struct dpoint
{
	double x;
	double p;
};

//generate data-file for F(x)
void 
generateF(struct dpoint* mas,int n)
{
	FILE* out = fopen("F.txt","w");
	double sum = 0;
	fprintf(out, "0.000 %lf\n",-2*abs(mas[0].x));
	for (int i = 0; i < n; ++i)
	{
		fprintf(out, "%lf %lf\n\n",sum,mas[i].x);
		sum+= mas[i].p;
		fprintf(out, "%lf %lf\n",sum,mas[i].x);
	}
	fprintf(out, "1.000 %lf\n",2*mas[n-1].x);
	fclose(out);
}

//generate data-file for polygon
void 
generateP(struct dpoint* mas,int n)
{
	FILE* out = fopen("P.txt","w");
	for (int i = 0; i < n; ++i)
	{
		fprintf(out,"%lf %lf\n",mas[i].p,mas[i].x);
	}
	fclose(out);
}

int
main(void)
{
	int n;
	double e;
	double p,q = 0.0;
	printf("Enter n and p\n");
	scanf("%d %lf",&n,&p);
	q = 1.0 - p;
	printf("Enter e\n");
	scanf("%lf",&e);
	struct dpoint mas[n];
	double sum = 0;
	double M,D,sig = 0.0;
	for (int i = 0; i < n-1; ++i)
	{
		mas[i].x = i+1;
		mas[i].p = p*pow(q,i);
		M += mas[i].x*mas[i].p;
		D += mas[i].x*mas[i].x*mas[i].p;
		sum += mas[i].p;
	}
	mas[n-1].x = n;
	mas[n-1].p = pow(q,n-1);
	M += mas[n-1].x*mas[n-1].p;
	D += mas[n-1].x*mas[n-1].x*mas[n-1].p;
	D-= M*M;
	sum += mas[n-1].p;
	sig = sqrt(D);
	printf("Sum of p is %lf\n",sum);
	if (abs(sum - 1) >= e)
	{
		printf("|%lf-1| >= %lf\n",sum,e);
		return 0;
	}
	for (int i = 0; i < n; ++i)
	{
		printf("%d:\n",i);
		printf("X = %lf p =%lf\n",mas[i].x,mas[i].p);
	}
	printf("M is %lf\n",M);
	printf("D is %lf\n",D);
	printf("sig is %lf\n",sig);
	generateF(mas,n);
	generateP(mas,n);
	system("gnuplot scF.txt");
	system("gnuplot scP.txt");
	system("ristretto F(x).png");
	system("ristretto polygon.png");
	return 0;
}
