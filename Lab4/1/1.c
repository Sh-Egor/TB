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
		fprintf(out, "%.3lf %.3lf\n\n",sum,mas[i].x);
		sum+= mas[i].p;
		fprintf(out, "%.3lf %.3lf\n",sum,mas[i].x);
	}
	fprintf(out, "1.000 %.3lf\n",2*mas[n-1].x);
	fclose(out);
}

//generate data-file for polygon
void 
generateP(struct dpoint* mas,int n)
{
	FILE* out = fopen("P.txt","w");
	for (int i = 0; i < n; ++i)
	{
		fprintf(out,"%.3lf %.3lf\n",mas[i].p,mas[i].x);
	}
	fclose(out);
}

int
main(void)
{
	int n;
	printf("Введите количество точек\n");
	scanf("%d",&n);
	struct dpoint mas[n];
	double sum = 0;
	double M,D,sig = 0.0;
	for (int i = 0; i < n; ++i)
	{
		printf("Enter x[%d] and p[%d]\n",i,i);
		scanf("%lf %lf",&mas[i].x,&mas[i].p);
		sum += mas[i].p;
		M+= mas[i].x*mas[i].p;
		D+= mas[i].x*mas[i].x*mas[i].p;
	}
	D-= M*M;
	sig = sqrt(D);
	if(sum != 1.0){
		printf("Error in data\n");
		printf("Sum of pi is %.3lf\n",sum);
		return 0;
	}
	generateF(mas,n);
	generateP(mas,n);
	printf("M is %.3lf\n",M);
	printf("D is %.3lf\n",D);
	printf("sig is %.3lf\n",sig);
	system("gnuplot scF.txt");
	system("gnuplot scP.txt");
	system("ristretto F(x).png");
	system("ristretto polygon.png");
	return 0;
}
