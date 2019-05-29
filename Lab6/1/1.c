#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

struct dpoint{
	double a;
	double b;
	double cent;
	int n;
	double f;
};	

int
generateMas(struct dpoint* mas, char* name, int flg)
{
	int n=0;
	FILE* in = fopen(name,"r");
	n = 0;
	double tmp;
	if(flg){
		int sum = 0;
		while(fscanf(in,"%lf %lf %d",&mas[n].a,&mas[n].b,&mas[n].n) != EOF){
		n++;
		}
		for(int i = 0; i < n; i++){
			mas[i].cent = (mas[i].a + mas[i].b)/2;
			sum += mas[i].n;
		}
		for(int i = 0; i < n; i++){
			mas[i].f = (double)mas[i].n/sum;
		}
	}else{
		fscanf(in,"%lf",&tmp);
		mas[0].cent = tmp;
		mas[0].n = 1;
		n = 1;
		while(fscanf(in,"%lf",&tmp) != EOF){
			int flg = 1;
			for(int i = 0; i < n; i++){
				if(tmp == mas[i].cent){
					mas[i].n++;
					flg = 0;
					break;
				}
			}
			if(flg){	
				mas[n].cent = tmp;
				mas[n].n = 1;
				n++;
			}
		}
		int sum = 0;
		for (int i = 0; i < n; ++i){
			sum += mas[i].n;
		}
		for (int i = 0; i < n; ++i){
			mas[i].f = (double)mas[i].n/sum;
		}
	}
	fclose(in);
	return n;
}

int
HandleInput(struct dpoint* mas, int n, int flg)
{
	int sum = 0;
	int size = 1;
	if(flg){
		for (int i = 0; i < n; i++){
			printf("(a,b),n [%d]:\n",i);
			scanf("%lf %lf %d",&mas[i].a,&mas[i].b,&mas[i].n);
		}	
		for(int i = 0; i < n; i++){
			mas[i].cent = (mas[i].a + mas[i].b)/2;
			sum += mas[i].n;
		}
		for(int i = 0; i < n; i++){
			mas[i].f = (double)mas[i].n/sum;
		}
	}else{
		printf("Mas of data is:\n");
		double tmp;
		scanf("%lf",&mas[0].cent);
		mas[0].n = 1;
		for(int i = 1; i < n; i++){
			scanf("%lf",&tmp);
			int flg1 = 1;
			for(int j = 0; j < size; j++){
				if(tmp == mas[j].cent){
					mas[j].n++;
					flg1 = 0;
					break;
				}
			}
			if(flg1){	
				mas[size].cent = tmp;
				mas[size].n = 1;
				size++;
			}
		}
		for(int i = 0; i < size; i++){
			sum += mas[i].n;
		}
		for(int i = 0; i < size; i++){
			mas[i].f = (double)mas[i].n/sum;
		}
	}
	return (flg)?n:size;
}

void
genDigParam(struct dpoint* mas, int n)
{
	double x = 0.0;
	double D = 0.0;
	double sig = 0.0;
	int sum = 0;
	for(int i = 0; i < n; i++){
		x += mas[i].cent * mas[i].n;
		D += mas[i].cent * mas[i].n * mas[i].cent;
		sum += mas[i].n;
	}
	x /= sum;
	D /= sum;
	D -= x*x;
	sig = sqrt(D);
}

int
main(void)
{
	struct dpoint mas[100];
	printf("0 - ввод из файла\n");
	printf("1 - ручной ввод\n");
	int tmp1;
	int tmp2;
	int n = 0;
	scanf("%d",&tmp1);
	printf("0 - массив данных\n");
	printf("1 - интервальный ряд\n");
	scanf("%d",&tmp2);
	if(tmp1){
		if(tmp2){
			printf("Введите количество интервалов\n");
		}else{
			printf("Введите количество чисел\n");
		}
		scanf("%d",&n);
		n = HandleInput(mas,n,tmp2);
	}else{
		n = generateMas(mas,"data.txt",tmp2);
	}
	genDigParam(mas,n);

	printf("N is %d\n",n);
	printf("Введите целое число для завершения\n");
	scanf("%d",&n);
	// delData(tmp);
	return 0;
}
