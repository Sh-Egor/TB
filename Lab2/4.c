#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(void)
{
	int n;
	double fullgroup = 0;
	double fullprobability = 0;
	double lh1;
	double lah1;
	printf("Введите число событий,образующих полную группу\n");
	printf("n = ");
	scanf("%d",&n);
	double mas[n];
	for (int i = 0; i < n; i++)
	{
		printf("p(H%d) = ",i);
		scanf("%lf",&lh1);
		if (lh1>1 || lh1 < 0)
		{
			printf("Некорректная вероятность гипотезы\n");
			return 0;
		}else{
			fullgroup += lh1;
		}
		printf("p(A|H%d) = ",i);
		scanf("%lf",&lah1);
		if (lah1>1 || lah1<0)
		{
			printf("Некорректная вероятность A при условии H%d\n",i);
			return 0;
		}else{
			mas[i] = lh1*lah1;
			fullprobability += mas[i];
		}
	}
	if (abs(fullgroup -1) < 0.0000000001)
	{
		printf("\nФормула полной вероятности:\n");
		printf("\np(A) = p(H0)*p(A|H0) + ");
		for (int i = 1; i < n-1; i++)
		{
			printf("p(H%d)*p(A|H%d) +",i,i);
		}
		printf("p(H%d)*p(A|H%d) =",n-1,n-1);
		printf(" %- -.3lf\n\n",fullprobability);
		printf("Условные вероятности:\n\n");
		for (int i = 0; i < n; ++i)
		{
			printf("             p(H%d)*p(A|H%d)\n",i,i);
			printf("p(H%d|A) =   -----------------  = %- -.3lf\n",i,mas[i]/fullprobability );
			printf("                  p(A)\n\n");
		}
	}else{
		printf("События не образуют полную группу( %lf )\n",fullgroup);
	}
	return 0;
}