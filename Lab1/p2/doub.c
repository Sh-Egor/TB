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

void
Cnm(int n, int m, char* to, char* sdef)
{
	char val[26] = {0};
	char val1[26] = {0};
	char val2[26] = {0};
	tosimple(n,val,sdef);
	tosimple(m,val1,sdef);
	tosimple(n-m,val2,sdef);
	add(val1,val2);
	sub(val,val1);
	add(to,val);
}

int
main(void)
{
	char sdef[26] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	printf("Введите номер задачи(2 или 5)\n");
	int num;
	scanf("%d",&num);
	int n,m,k;
	switch(num){
		case 2:
			printf("Имеется m операторов и n перенумерованных приборов,которые они могут обслуживать.\nКаждый оператор выбирает случайным образом и с одинаковой вероятностью любой прибор,\nно с условием, что ни один прибор не может обслуживаться больше, чем одним оператором.\nНайти вероятность того, что будут выбраны для обслуживания приборы с номерами 1, 2, …, m.\n");
			printf("Введите числа m и n(m,n <= 100)\n");
			printf("n = ");
			scanf("%d",&n);
			printf("m = ");
			scanf("%d",&m);
			printf("Решение:\n");
			if(n<=m){
				printf("Операторов не меньше, чем число приборов\nВероятность того, что все приборы будут заняты - 1");
			}else{
				if(n > 100 || m > 100){
					printf("Выход за допустимые границы\n");
					return 0;
				}
				printf("Воспользуемся формулой P(A) = P of m / A of n by m\n");
				char top[26] = {0};//парсим 1 число
				tosimple(m,top,sdef);
				char both1[26] = {0};//парсим числитель знаменателя
				tosimple(n,both1,sdef);
				char both2[26] = {0};//парсим знаменатель знаменателя
				tosimple(n-m,both2,sdef);
				add(top,both2);//умножаем числитель на знаменатель знаменателя
				sub(top,both1);
				char both[26] = {0};
				for(int i = 0; i < 26; i++){
					if(top[i] < 0){
						both[i] = -top[i];
						top[i] = 0;
					}
				}
				top[0] = 1;
				both[0] = 1;
				char res2[200] = {0};//создаём строку вывода знаменателя
				char res1[200] = {0};//создаём строку вывода числителя
				res1[0] = 1;
				res2[0] = 1;
				for(int i = 0; i < 26; i++){
					if(top[i]){
						for(int j = 0; j < top[i]; j++){
							char a[2];
							a[1] = sdef[i]/10;
							a[0] = sdef[i]%10;
							mult2(res1,a);
						}
					}
				}
				for(int i = 0; i < 26; i++){
					if(both[i]){
						for(int j = 0; j < both[i]; j++){
							char a[2];
							a[1] = sdef[i]/10;
							a[0] = sdef[i]%10;
							mult2(res2,a);
						}
					}
				}
				int k1=0;
				int k2=0;
				for(int i = 0; i < 200; i++)
					if(res1[i])
						k1 = i;
				for(int i = 0; i < 200; i++)
					if(res2[i])
						k2 = i;
				for(int i = k1; i >=0; i--){
					printf("%d",res1[i]);
				}
				printf("\n________________________________\n");
				for(int i = k2; i >=0; i--){
					printf("%d",res2[i]);
				}
				printf("\n");
			}					
		break;
		case 5:
			printf("В ящике имеется k ТЭЗ, из них k1 1-го типа,...,\nki элементов i-го типа,...,km элементов m-го типа\nСумма всех ki,i={1,..,m} = k\nИз ящика наугад выбирают n ТЭЗ. Найдите вероятность того,\nчто среди них будет n1 ТЭЗ 1-го типа,...,ni ТЭЗ i-го типа,\nnm ТЭЗ m-го типа\n");
			printf("Введите числа k, m и n(k <= 100, m <=k, n<=k)\n");
			printf("k = ");
			scanf("%d",&k);
			printf("m = ");
			scanf("%d",&m);
			printf("n = ");
			scanf("%d",&n);
			if(k > 100 || m > k || n > k){
				printf("Выход за границы\n");
				return 0;
			}
			int kmas;
			int nmas;
			int flg = 1;
			char top[26] = {0};
			for(int i = 0; i < m&&flg; i++){
				printf("Введите k%d и n%d\n",i,i);
				scanf("%d %d",&kmas,&nmas);
				if(kmas<nmas){
					flg = 0;
					printf("Вероятность равна 0 - из %d нельзя выбрать %d\n",kmas,nmas);
					return 0;
				}else{
					Cnm(kmas,nmas,top,sdef);
				}
			}
			printf("\n");
			char both1[26] = {0};
			Cnm(k,n,both1,sdef);
			sub(top,both1);
			char both[26] = {0};
				for(int i = 0; i < 26; i++){
					if(top[i] < 0){
						both[i] = -top[i];
						top[i] = 0;
					}
				}
			top[0] = 1;
			both[0] = 1;
			char res2[200] = {0};//создаём строку вывода знаменателя
			char res1[200] = {0};//создаём строку вывода числителя
			res1[0] = 1;
			res2[0] = 1;
			for(int i = 0; i < 26; i++){
				if(top[i]){
					for(int j = 0; j < top[i]; j++){
						char a[2];
						a[1] = sdef[i]/10;
						a[0] = sdef[i]%10;
						mult2(res1,a);
					}
				}
			}
			for(int i = 0; i < 26; i++){
				if(both[i]){
					for(int j = 0; j < both[i]; j++){
						char a[2];
						a[1] = sdef[i]/10;
						a[0] = sdef[i]%10;
						mult2(res2,a);
					}
				}
			}
			int k1=0;
			int k2=0;
			for(int i = 0; i < 200; i++)
				if(res1[i])
					k1 = i;
			for(int i = 0; i < 200; i++)
				if(res2[i])
					k2 = i;
			for(int i = k1; i >=0; i--){
				printf("%d",res1[i]);
			}
			printf("\n________________________________\n");
			for(int i = k2; i >=0; i--){
				printf("%d",res2[i]);
			}
			printf("\n");
		break;
		default:
		break;
	}
	return 0;
}