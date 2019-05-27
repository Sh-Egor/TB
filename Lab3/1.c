#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void
add(char* to, char* from)
{
	for(int i = 0; i < 26; i++){
		to[i] += from[i];
	}
}

void
sub(char* to, char* from)
{
	for(int i = 0; i < 26; i++){
		to[i] -= from[i];
	}
}

void
tosimple(int b, char* mas, char* sdef)
{
	int a = b;
	if(a > 1){
		for(int i = 2; i <= a;i++){
			int c = i;
			while(c != 1){
				for(int j = 1; j < 26; j++){
					if(c % sdef[j] == 0){
						c /= sdef[j];
						mas[j]++;
						break;
					}
				}
			}
		}
	}
	mas[0] = 1;
}


int
bigC(int n, int m)
{
	char sdef[26] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	char s1[26] = {0};
	char s2[26] = {0};
	char s3[26] = {0};
	tosimple(n,s1,sdef);
	tosimple(m,s2,sdef);
	tosimple(n-m,s3,sdef);
	add(s2,s3);
	sub(s1,s2);
	int res = 1;
	s1[0] = 1;
	for (int i = 0; i < 26; i++)
	{
		while(s1[i]){
			res *= sdef[i];
			s1[i]--;
		}
	}
	return res;
}

double
bigP(int n, int m, double p)
{
	double res = 1;
	for(int i = 0; i < m; i++){
		res *= p;
	}
	for (int i = 0; i < n-m; ++i)
	{
		res *= (1-p);
	}
	res *= bigC(n,m);
	printf("C_from(%d)_by(%d)*%lf^%d*%lf^%d\n",n,m,p,m,1-p,n-m);
	return res;
}


int
main(void)
{
	int n,m,m1,m2;
	double p;
	printf("Введите через пробел n,m,m1,m2\n");
	scanf("%d %d %d %d",&n,&m,&m1,&m2);
	if(n < m){
		printf("Некорретные n и m\n");
		return 0;
	}
	if(m1 > n || m2 > n){
		printf("Некорретные m1 и m2\n");
		return 0;
	}
	if(m2 < m1){
		printf("m1 и m2 поменялись местами\n");
		int tmp = m1;
		m1 = m2;
		m2 = tmp;
	}
	printf("Введите p\n");
	scanf("%lf",&p);
	if(p > 1 || p < 0){
		printf("Некорретная вероятность p\n");
		return 0;
	}
	int num;
	printf("Выберите вариант:\n");
	printf("1 - P%d(k = %d)\n",n,m);
	printf("2 - P%d(k < %d)\n",n,m);
	printf("3 - P%d(k >= %d)\n",n,m);
	printf("4 - P%d( %d <= k <= %d)\n",n,m1,m2);
	printf("Любой другой - все варианты\n");
	scanf("%d",&num);
	double res;
	int flg = 1;
	switch(num){
		default:
		flg = 0;
		case 1:
			printf("________________________________\n");
			printf("P%d(k = %d) =\n",n,m);
			res = bigP(n,m,p);
			printf(" =%- -.5lf\n",res);
		if(flg)
			break;
		case 2:
			printf("________________________________\n");
			printf("P%d(k < %d) =\n",n,m);
			res = 0;
			for(int i = 0; i < m; i++){
				res += bigP(n,i,p);
				if(i != m-1)
					printf(" + \n");
			}
			printf(" = %- -.5lf\n",res);
		if(flg)
			break;
		case 3:
			printf("________________________________\n");
			printf("P%d(k >= %d)\n",n,m);
			res = 0;
			for (int i = m; i <= n ; i++){
				res += bigP(n,i,p);
				if(i != n)
					printf(" + \n");
			}
			printf(" = %- -.5lf\n",res);
		if(flg)
			break;
		case 4:
			printf("________________________________\n");
			printf("P%d( %d <= k <= %d)\n",n,m1,m2);
			res = 0;
			for (int i = m1; i <= m2 ; i++){
				res += bigP(n,i,p);
				if(i != m2)
					printf(" + \n");
			}
			printf(" = %- -.5lf\n",res);
		break;
	}
	return 0;
}