#include <stdio.h>
#include <stdlib.h>

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
			mas[0] = 1;
		}
	}
	if(a == 0 || a == 1){
		mas[0] = 1;
	}
}

long long int
bigPofk(int n, int k, int* m)
{
	char sdef[26] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	char s1[26] = {0};
	char s2[26] = {0};
	tosimple(n,s1,sdef);
	for (int i = 0; i < k; ++i){
		for(int j = 0; j < 26; j++)
			s2[j] = 0;
		tosimple(m[i],s2,sdef);
		sub(s1,s2);
	}
	long long int res = 1;
	s1[0] = 1;
	for (int i = 0; i < 26; i++){
		while(s1[i]){
			res *= sdef[i];
			s1[i]--;
		}
	}
	return res;
}

int
main(void)
{
	int n,k;
	printf("Введите n,k,mi(i=1,k)\n");
	scanf("%d %d",&n,&k);
	int m[k];
	for (int i = 0; i < k; i++){
		printf("m[%d] = ",i);
		scanf("%d",&m[i]);
	}
	double p[k];
	for (int i = 0; i < k; i++){
		printf("p[%d] = ",i);
		scanf("%lf",&p[i]);
	}
	printf("                     %d!\n",n);
	printf("P%d(",k);
	for (int i = 0; i < k-1; ++i){
		printf("%d,",m[i]);
	}
	printf("%d) =      ---------",m[k-1]);
	for (int i = 0; i < k; ++i){
		printf(" * %.3lf^%d",p[i],m[i]);
	}
	double res = 1;
	res *= bigPofk(n,k,m);
	for (int i = 0; i < k; i++){
		int z = m[i];
		while(z){
			res *= p[i];
			z--;
		}
	}
	printf(" = \n%.10f\n",res);
	printf("                   ");
	for (int i = 0; i < k; ++i){
		printf("%d!",m[i]);
	}
	printf("\n");
	return 0;
}