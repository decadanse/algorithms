/*Программа для вычисления значения функции, заданной с помощью ряда. 
	Вычисление ряда проводить до условия минимизации значения разности двух соседних членов ряда 
	меньше заданного эпсилон. Вычислить значения невязки значений рядной и стандартной Windows ("math.h") 
	функций  , проанализировать динамику изменения значения невязки в зависимости от количества 
	слагаемых в ряде. Для остановки счета рядов необходимо использовать заданное условие.*/

#define _USE_MATH_DEFINES
//#include "pch.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace std;

int Foo(double epsilon) {
	int test = (int)epsilon;
	int n = 0;
	while (test != epsilon) {
		n++;
		epsilon *= 10;
		test = (int)epsilon;
	}

	int stepen_10 = 1;
	int i;
	for (i = 0; i < n; i++) {
		stepen_10 = stepen_10 * 10;
	}
	return stepen_10;
}

double lev(double epsilon, double x) {
	double s = 1 / (x - 1);
	int stepen_10 = Foo(epsilon);
	s = round(s * stepen_10) / stepen_10;
	return s;
}

double lev2( double x) {
	return (1 / (x - 1));
}

//Рекурентная формула, где sum - сумма, первый член равен 1  
double prav(double epsilon, double x) {
	int i, j;
	double xpow2 = 1;
	double xpowx = x;
	double fxn = x, sum = 0;
	int stepen_10 = Foo(epsilon);

	for (i = 1; fabs(fxn) >= epsilon; i++) {
		fxn = xpow2 / (xpowx + 1);
		sum += fxn;
		xpow2 = xpow2 * 2;
		for (j = (xpow2 + 1); j < (xpow2 * 2); j++) {
			xpowx = xpowx * x;
		}
	}

	if (sum / 1 == sum) { //проверка на существование ф-ии
		sum = round(sum * stepen_10) / stepen_10;
		return sum;
	}
	else {
		return 0;
	}
}

double prav2(double epsilon, double x) {
	int i=1, j;
	double xpow2 = 1;
	double xpowx = x;
	double fxn = x, sum = 0;

	//for (i = 1; fabs(fxn) >= epsilon; i++) {
	while(fabs(fxn) >= epsilon){
		//fxn = pow(2, (i - 1)) / (pow(x, (2 ^ (i - 1))) + 1);
	
		fxn = xpow2 / (xpowx + 1);
		sum += fxn;
		xpow2 = xpow2 * 2;
		for (j = (xpow2 + 1); j < (xpow2 * 2); j++) {
			xpowx = xpowx * x;
		}
		//i++;
	}

	if (sum / 1 == sum) { //проверка на существование ф-и
		return sum;
	}
	else {
		return 0;
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");

	double xstart, xend, shag, epsilon, xideal;
	int number = 1;

	cout << "Введите начальное значение x " << endl;
	cin >> xstart;

	if ((!cin) || (abs(xstart * xstart) <= 1)) { // не должно быть из ОДЗ |X^2| > 1
		cout << "Некорректный ввод. Нужен такой х, что: |x^2| > 1" << endl;
		system("pause");
		return 0;
	}

	cout << "Введите конечное значение x " << endl;
	cin >> xend;
	if ((!cin) || (xend <= xstart)) {
		cout << "Некорректный ввод" << endl;
		system("pause");
		return 0;
	}

	cout << "Введите шаг " << endl;
	cin >> shag;
	if ((!cin) || (shag <= 0)) {
		cout << "Некорректный ввод. Необходим положительный шаг" << endl;
		system("pause");
		return 0;
	}

	cout << "Введите epsilon " << endl;
	cin >> epsilon;
	if ((!cin) || epsilon <= 0 || epsilon > 0.1) {
		cout << "Некорректный ввод. Epsilon должно принадлежать интервалу [0;01)" << endl;
		system("pause");
		return 0;
	}

	char text[6] = { 'E','r','r','o','r' };

	double delta, x;
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("|   №  |         x         |       MyFuntion(x)      |        Function(x)      |           delta         |\n");
	printf("----------------------------------------------------------------------------------------------------------\n");
	x = xstart;
ag:
	while (x <= xend) {

		if (abs(x * x) <= 1) {
			number++;
			x += shag;
			x = x * 100000000;
			x = round(x);
			x = x / 100000000;
			goto ag;
		}

		delta = sqrt(fabs(prav(epsilon, x) * prav(epsilon, x) - lev(epsilon, x) * lev(epsilon, x)));

		if (prav(epsilon, x) == 0) {
			printf("|%-6i|%-19.8lf|%-25.8s|%-25.8lf|%-25.8s|\n", number, x, text, lev(epsilon, x), text);
		}
		else {
			printf("|%-6i|%-19.8lf|%-25.8lf|%-25.8lf|%-25.8lf|\n", number, x, prav(epsilon, x), lev(epsilon, x), delta);
		}

		number++;
		x += shag;
		x = x * 100000000;
		x = round(x);
		x = x / 100000000;
	}
	printf("----------------------------------------------------------------------------------------------------------\n");

	cout << "Введите Xideal " << endl;
	cin >> xideal;
	if ((!cin) || (xideal < xstart) || (xideal > xend)) {
		cout << endl << "Некорректный ввод" << endl;
		system("pause");
		return 0;
	}


	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("|   №  |      epsilon      |       MyFuntion(x)      |        Function(x)      |           delta         |\n");
	printf("----------------------------------------------------------------------------------------------------------\n");
	double epsilon2, delta2;
	int number2 = 1;

	for (epsilon2 = 0.1; epsilon2 >= 0.0000001; epsilon2 = epsilon2 / 10, number2++) {
		x = xideal;
		//эпсилон влияет только на остановку счета - не надо ничего округлять и не надо урезать функции здесь. Здесь функции выводятсЯя одинаковые в плане кол-ва цифр и пеолные
		delta2 = sqrt(fabs(prav2(epsilon2, x) * prav2(epsilon2, x) - lev2(x) * lev2(x)));
		printf("|%-6i|%-19.7lf|%-25.8lf|%-25.8lf|%-25.8lf|\n", number2, epsilon2, prav2(epsilon2, x), lev2(x), delta2);
	}
	printf("----------------------------------------------------------------------------------------------------------\n");

	system("pause");
	return 0;
}
//разница в 1-2 цифры при малых значениях возникает из-за графика/строения самой функции - ближе к ОДЗ она устремляется к + - бесконечности