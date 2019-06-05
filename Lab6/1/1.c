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

double
F0(double a)
{
	double res = erf(a/sqrt(2))/2;
	return res;
}

int
isA(double a)
{
	if(a == 0.995)
		return 0;
	if(a == 0.99)
		return 1;
	if(a == 0.975)
		return 2;
	if(a == 0.95)
		return 3;
	if(a == 0.9)
		return 4;
	if(a == 0.75)
		return 5;
	if(a == 0.5)
		return 6;
	if(a == 0.25)
		return 7;
	if(a == 0.1)
		return 8;
	if(a == 0.05)
		return 9;
	if(a == 0.025)
		return 10;
	if(a == 0.01)
		return 11;
	if(a == 0.005)
		return 12;
	return -1;
}

double
GetXiSq(double a, int k)
{
	FILE* in = fopen("xi2Table.txt","r");
	int key = 0;
	double xi[13];
	while(key != k){
		fscanf(in,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&key,&xi[0],&xi[1],&xi[2],&xi[3],&xi[4],&xi[5],&xi[6],&xi[7],&xi[8],&xi[9],&xi[10],&xi[11],&xi[12]);
	}
	int num = isA(a);
	fclose(in);
	return (num == -1)?-1:xi[num];
}

void
genPolDataAbs(struct dpoint* mas, int n)
{
	FILE* out = fopen("Abskr.txt","w");
	for (int i = 0; i < n; ++i){
		fprintf(out, "%d %.3lf\n",mas[i].n,mas[i].cent);
	}
	fclose(out);
}

void
genScr(double a, double b, int y)
{
	FILE* scr = fopen("scr_1.txt","w");
	fprintf(scr, "set terminal png\n");
	fprintf(scr, "set output 'Abs.png'\n");
	fprintf(scr, "set xrange [%lf:%lf]\n",a,b);
	fprintf(scr, "set yrange [0:%ld]\n",y);
	fprintf(scr, "set multiplot\n");
	fprintf(scr, "plot \"Abs.txt\" u 2:1 w l lw 4\n");
	fprintf(scr, "plot \"Abskr.txt\" u 2:1 w l lw 4 lt rgb 'red'\n");
	fclose(scr);
}

void
genScrN(double a, double sig)
{
	FILE* scr = fopen("scr_2.txt","w");
	fprintf(scr, "set terminal png\n");
	fprintf(scr, "set output 'Abs1.png'\n");
	fprintf(scr, "plot 1/(sqrt(2*pi)*%lf)*exp(-(x-%lf)**2/(2*%lf**2)) lw 4 lt rgb 'red'",sig,a,sig);
	fclose(scr);
}

void
CheckNorm(struct dpoint* mas, int n, double a, int tmp2)
{
	double p[n];
	double np[n];
	double row[n];
	double x = 0.0;
	double D = 0.0;
	double sig = 0.0;
	double S2 = 0.0;
	double s = 0.0;
	int sum = 0;
	int mx = 0;
	for(int i = 0; i < n; i++){
		x += mas[i].cent * mas[i].n;
		D += mas[i].cent * mas[i].n * mas[i].cent;
		sum += mas[i].n;
		if(mas[i].n > mx){
			mx = mas[i].n;
		}
	}
	x /= sum;
	D /= sum;
	D -= x*x;
	sig = sqrt(D);
	S2 = D*sum/(sum-1);
	s = sqrt(S2);
	printf("x is %.3lf\n",x);
	printf("s is %.3lf\n",s);
	if(tmp2){
		p[0] = F0((mas[0].b-x)/sig) + 0.5;
		for(int i = 1; i < n-1; i++){
			p[i] = F0((mas[i].b-x)/sig) - F0((mas[i].a-x)/sig);
		}
		p[n-1] = 0.5 - F0((mas[n-1].a-x)/sig);
	}else{
		p[0] = F0((mas[1].cent - x)/sig) + 0.5;
		for(int i = 1; i < n-1; i++){
			p[i] = F0((mas[i+1].cent - x)/sig) - F0((mas[i].cent - x)/sig);
		}
		p[n-1] = 0.5 - F0((mas[n-1].cent - x)/sig);
	}
	double X2 = 0;
	for(int i = 0; i < n; i++){
		np[i] = p[i]*sum;
		row[i] = (mas[i].n-np[i])*(mas[i].n-np[i])/np[i];
		X2 += row[i];
	}
	printf("X2: %.5lf\n",X2);
	double sr = GetXiSq(a,n-3);
	printf("xi(table) %.5lf\n",sr);
	genGistDataAbs(mas,n);
	genPolDataAbs(mas,n);
	genScr(mas[0].a,mas[n-1].b,mx);
	genScrN(x,sig);
	system("gnuplot scr_1.txt");
	system("gnuplot scr_2.txt");
	if(sr > 0){
		if(X2 <= sr){
			printf("Гипотеза подтверждена\n");
		}else{
			printf("Гипотеза опровергнута\n");
		}
	}else{
		printf("а не найдена в таблице или количество интервалов меньше 4\n");
	}
	system("ristretto Abs.png");
}

int
main(void)
{
	struct dpoint mas[100];
	printf("0 - ввод из файла\n");
	printf("1 - ручной ввод\n");
	int tmp;
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
	printf("N is %d\n",n);
	printf("Проверка гипотезы о виде распределения по критерию Пирсона\n");
	printf("0 - о нормальном распределении\n");
	printf("1 - о биномиальном распределении\n");
	scanf("%d",&tmp);
	printf("Введите a:\n");
	double a;
	scanf("%lf",&a);
	if (tmp){
		// CheckBin(mas,n,a);
	}else{
		CheckNorm(mas,n,a,tmp2);
	}
	printf("Введите целое число для завершения\n");
	scanf("%d",&n);
	// delData(tmp);
	return 0;
}
