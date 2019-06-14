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
		}
	}
	mas[0] = 1;
}

void
mult1(char* mas, char value)
{
	char carry = 0;
	for (int i = 0; i < 200; i++)
	{
		mas[i] = mas[i] * value + carry;
		if(mas[i]/10){
			carry = mas[i]/10;
		}else{
			carry = 0;
		}
		mas[i] %= 10;
	}
}

void
mult2(char* res, char* a)
{
	char cur1[200];
	char cur2[200];
	for(int i = 0; i < 200; i++){
		cur1[i] = res[i];
		cur2[i] = res[i];
	}
	mult1(cur1,a[0]);
	mult1(cur2,a[1]);
	int carry = 0;
	res[0] = cur1[0] + carry;
	if(res[0]/10){
			carry = res[0]/10;
		}else{
			carry = 0;
		}
	res[0] %= 10;
	for(int i = 1; i < 200; i++){
		res[i] = cur1[i] + cur2[i-1] + carry;
		if(res[i]/10){
			carry = res[i]/10;
		}else{
			carry = 0;
		}
		res[i] %= 10;
	}
}



int
main(void)
{
	int m,n;
	char sdef[26] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	char s1[26] = {0};
	char s2[26] = {0};
	char s3[26] = {0};
	printf("Write n and m for C of n by m:\n");
	printf("n = ");
	scanf("%d",&n);
	printf("m = ");
	scanf("%d",&m);
	if(m <= n && n ){
		tosimple(n,s1,sdef);
		tosimple(m,s2,sdef);
		tosimple(n-m,s3,sdef);
		add(s2,s3);
		sub(s1,s2);
		char res[200] = {0};
		res[0] = 1;
		printf("%d!/(%d!*%d!) = \n",n,m,n-m);
		for(int i = 0; i < 26; i++){
			if(s1[i]){
				for(int j = 0; j < s1[i]; j++){
					char a[2];
					a[1] = sdef[i]/10;
					a[0] = sdef[i]%10;
					int k = 1;
					if(a[i])
						k = 2;
					mult2(res,a);
					printf(" %d *",sdef[i]);
				}
			}
		}
		printf("\n");
		int k = 0;
		for(int i = 0; i < 200; i++)
			if(res[i])
				k = i;
		for (int i = k; i >= 0; i--){
			printf("%d",res[i]);
		}
		printf("\n");
	}else{
		printf("Incorrect input data!\n");
	}
	
	return 0;
}