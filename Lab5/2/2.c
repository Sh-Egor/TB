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
generateMas(struct dpoint* mas, char* name)
{
	int n=0;
	FILE* in = fopen(name,"r");
	n = 0;
	while(fscanf(in,"%lf %lf %d",&mas[n].a,&mas[n].b,&mas[n].n) != EOF){
		n++;
	}
	fclose(in);
	return n;
}

void
HandleInput(struct dpoint* mas, int n)
{
	for (int i = 0; i < n; i++){
		printf("(a,b),n [%d]:\n",i);
		scanf("%lf %lf %d",&mas[i].a,&mas[i].b,&mas[i].n);
	}
}

void
genGistDataAbs(struct dpoint* mas, int n)
{
	FILE* out = fopen("Abs.txt","w");
	for (int i = 0; i < n; i++){
			fprintf(out, "0 %.3lf\n",mas[i].a);
			fprintf(out, "%d %.3lf\n",mas[i].n,mas[i].a);
			fprintf(out, "%d %.3lf\n",mas[i].n,mas[i].b);
			fprintf(out, "0 %.3lf\n",mas[i].b);
		}	
	fclose(out);
}

void
genGistDataRel(struct dpoint* mas, int n)
{
	FILE* out = fopen("Rel.txt","w");
	for (int i = 0; i < n; i++){
			fprintf(out, "0 %.3lf\n",mas[i].a);
			fprintf(out, "%.3lf %.3lf\n",mas[i].f,mas[i].a);
			fprintf(out, "%.3lf %.3lf\n",mas[i].f,mas[i].b);
			fprintf(out, "0 %.3lf\n",mas[i].b);
		}	
	fclose(out);
}

void
genPolDataAbs(struct dpoint* mas, int n)
{
	FILE* out = fopen("Abs.txt","w");
	for (int i = 0; i < n; ++i){
		fprintf(out, "%d %.3lf\n",mas[i].n,mas[i].cent);
	}
	fclose(out);
}

void
genPolDataRel(struct dpoint* mas, int n)
{
	FILE* out = fopen("Rel.txt","w");
	for (int i = 0; i < n; ++i){
		fprintf(out, "%.3lf %.3lf\n",mas[i].f,mas[i].cent);
	}
	fclose(out);
}

void
genFDataInt(struct dpoint* mas, int n)
{
	FILE* out = fopen("FInt.txt","w");
	double sum = 0.0;
	fprintf(out, "0 %lf\n",-2*mas[0].a);
	fprintf(out, "0 %lf\n\n",mas[0].a);
	for (int i = 0; i < n; ++i){
		sum += mas[i].f;
		fprintf(out, "%.3lf %.3lf\n",sum,mas[i].a);
		fprintf(out, "%.3lf %.3lf\n\n",sum,mas[i].b);
	}
	fprintf(out, "1.000 %.3lf\n",mas[n-1].b);
	fprintf(out, "1.000 %.3lf\n",2*mas[n-1].b);
	fclose(out);
}

void
genFDataGroup(struct dpoint* mas, int n)
{
	FILE* out = fopen("FGroup.txt","w");
	double sum = 0.0;
	fprintf(out, "0 %lf\n",-2*mas[0].cent);
	fprintf(out, "0 %lf\n\n",mas[0].cent);
	for (int i = 0; i < n-1; ++i){
		sum += mas[i].f;
		fprintf(out, "%.3lf %.3lf\n",sum,mas[i].cent);
		fprintf(out, "%.3lf %.3lf\n\n",sum,mas[i+1].cent);
	}
	fprintf(out, "1.000 %.3lf\n",mas[n-1].cent);
	fprintf(out, "1.000 %.3lf\n",2*mas[n-1].cent);
	fclose(out);
}

void
genDigParam(struct dpoint* mas, int n)
{
	FILE* out = fopen("Dig.txt","w");
	double x = 0.0;
	double D = 0.0;
	double sig = 0.0;
	double S = 0.0;
	int sum = 0;
	for (int i = 0; i < n; ++i){
		x+= mas[i].cent*mas[i].n;
		D+= mas[i].cent*mas[i].n*mas[i].cent;
		sum += mas[i].n;
	}
	x /= sum;
	D /= sum;
	D -= x*x;
	sig = sqrt(D);
	S = D*(sum-1)/sum;
	fprintf(out, "X выборочное = %- -.6lf\n",x);
	fprintf(out, "D выб = %- -.6lf\n",D);
	fprintf(out, "среднее кв.отклонение = %- -.6lf\n",sig);
	fprintf(out, "S = %- -.6lf\n",S);
	fclose(out);
}

void
delData(int tmp)
{
	switch(tmp){
		case 1:
			system("rm Abs.png");
			system("rm Rel.png");
			system("rm Abs.txt");
			system("rm Rel.txt");
			break;
		case 2:
			system("rm Abs.png");
			system("rm Rel.png");
			system("rm Abs.txt");
			system("rm Rel.txt");
			break;
		case 3:
			system("rm FGroup.png");
			system("rm FGroup.txt");
			system("rm FInt.png");
			system("rm FInt.txt");
			break;
		case 4:
			system("rm Dig.txt");
			break;
		default:
			break;		
	}
}

int
main(void)
{
	struct dpoint mas[100];
	int n = 0;
	int tmp;
	printf("0 - ввод данных их файла\n");
	printf("1 - ручной ввод\n");
	scanf("%d",&tmp);
	if(tmp){
		printf("Число интервалов n\n");
		scanf("%d",&n);
		HandleInput(mas,n);
	}else{
		n = generateMas(mas,"data.txt");
	}
	int sum = 0;
	for (int i = 0; i < n; i++){
		sum += mas[i].n;
	}
	for (int i = 0; i < n; i++){
		mas[i].f = (double)mas[i].n/sum;
		mas[i].cent = (mas[i].a + mas[i].b)/2;
	}
	printf("1 - интервальный ряд частот и относительных частот(гистограммы)\n");
	printf("2 - группированный ряд частот и относительных частот(полигоны)\n");
	printf("3 - постоение F(x) \n");
	printf("4 - вычисление характеристик(Xв,Dв,sig,S\n");
	scanf("%d",&tmp);
	switch(tmp){
		case 1:
			genGistDataAbs(mas,n);
			genGistDataRel(mas,n);
			system("gnuplot scr_1_1.txt");
			system("gnuplot scr_1_2.txt");
			system("ristretto Abs.png");
			break;
		case 2:
			genPolDataAbs(mas,n);
			genPolDataRel(mas,n);
			system("gnuplot scr_1_1.txt");
			system("gnuplot scr_1_2.txt");
			system("ristretto Abs.png");
			break;
		case 3:
			genFDataInt(mas,n);
			genFDataGroup(mas,n);
			system("gnuplot scr_3_1.txt");
			system("gnuplot scr_3_2.txt");
			system("ristretto FInt.png");
			break;
		case 4:
			genDigParam(mas,n);
			system("subl Dig.txt");
			break;
		default:
			break;		
	}
	printf("Введите целое число для завершения\n");
	scanf("%d",&n);
	delData(tmp);
	return 0;
}
