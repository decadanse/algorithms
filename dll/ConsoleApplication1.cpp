#define _USE_MATH_DEFINES
//#include "pch.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "ATLComTime.h"
#include <Windows.h>
#include <stdio.h>

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

int text = 1;
int bg = 0;
double *SetColor()
{	
	if (text == 15) text = 1;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));	
	text++;
	return 0;
}

//void CallBack(int d, void(*func)(int))
//{
//	func(d);
//}

int main()
{
	setlocale(LC_ALL, "Rus");

	string dll_name = "Dll1";

	//cout << "Введите название подключаемой dll: " << endl;
	//cin >> dll_name;
	if (!(LoadLibraryExA(dll_name.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE)))
	{
		cout << "Ошибка загрузки." << endl;
		system("pause"); 
		exit(0);
	}
	
	typedef double(*myf_1b)(double, double, double, double(*));//prav
	typedef double(*myf_math)(double, double);//lev
	typedef const char* (*FName)();
	HINSTANCE mydll = LoadLibraryA(dll_name.c_str());
	myf_1b MyFunction_prav = (myf_1b)GetProcAddress(mydll, "myf_1b");
	myf_math function_lev = (myf_math)GetProcAddress(mydll, "myf_math");
	FName Name = (FName)GetProcAddress(mydll, "FName");
	
	typedef const char* (*FName)();
	FName name = (FName)GetProcAddress(mydll, "FName");
	if (!(mydll && MyFunction_prav && function_lev && Name))
	{
		cout << "Функции не найдены.";
		system("pause");
		exit(0);
	}
	
	
	double xstart=1, xend=2, shag=0.1, epsilon=0.1, xideal;
	int number = 1;
	cout << "Введите начальное значение x " << endl;
	//cin >> xstart;

	if ((!cin) || ((xstart) < -1)) { //  ОДЗ 
		cout << "Некорректный ввод. x должен быть >= -1" << endl;
		system("pause");
		return 0;
	}
	
	cout << "Введите конечное значение x " << endl;
	//cin >> xend;
	if ((!cin) || (xend <= xstart)) {
		cout << "Некорректный ввод" << endl;
		system("pause");
		return 0;
	}

	cout << "Введите шаг " << endl;
	//cin >> shag;
	if ((!cin) || (shag <= 0)) {
		cout << "Некорректный ввод. Необходим положительный шаг" << endl;
		system("pause");
		return 0;
	}

	cout << "Введите epsilon " << endl;
	//cin >> epsilon;
	if ((!cin) || epsilon <= 0 || epsilon > 0.1) {
		cout << "Некорректный ввод. Epsilon должно принадлежать интервалу [0;01]" << endl;
		system("pause");
		return 0;
	}

	char text[6] = { 'E','r','r','o','r' };

	double delta, x;
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("|   №  |         x         |       MyFuntion(x)      |        Function(x)      |           delta         |\n");
	printf("----------------------------------------------------------------------------------------------------------\n");
	x = xstart;

	while (x <= xend) {

		delta = sqrt(fabs(MyFunction_prav(x, 0, epsilon, NULL) * MyFunction_prav(x, 0, epsilon, NULL) - function_lev(x, 0) * function_lev(x, 0)));
		//delta = sqrt(fabs(prav(epsilon, x) * prav(epsilon, x) - lev(epsilon, x) * lev(epsilon, x)));

		if (MyFunction_prav(x, 0, epsilon, SetColor()) == 0) {
			printf("|%-6i|%-19.8lf|%-25.8s|%-25.8lf|%-25.8s|\n", number, x, text, function_lev(x, 0), text);
		}
		else {
			//printf("|%-6i|%-19.8lf|%-25.8lf|%-25.8lf|%-25.8lf|\n", number, x, prav(epsilon, x), lev(epsilon, x), delta);
			printf("|%-6i|%-19.8lf|%-25.8lf|%-25.8lf|%-25.8lf|\n", number, x, MyFunction_prav(x, 0, epsilon, SetColor()), function_lev(x, 0), delta);
		}

		number++;
		x += shag;
		x = x * 100000000;
		x = round(x);
		x = x / 100000000;
	}
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
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
		delta2 = sqrt(fabs(MyFunction_prav(x, 0, epsilon2, SetColor()) * MyFunction_prav(x, 0, epsilon2, SetColor()) - function_lev(x, 0) * function_lev(x, 0)));
		printf("|%-6i|%-19.7lf|%-25.8lf|%-25.8lf|%-25.8lf|", number2, epsilon2, MyFunction_prav(x, 0, epsilon2, SetColor()), function_lev(x, 0), delta2);
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 15));
		cout << endl;
	}
	printf("----------------------------------------------------------------------------------------------------------\n");
	
	system("pause");
	return 0;
}
