/*В наборе монет и банкнот есть следующие номиналы: монеты – 1, 2, 5, 10 рублей, 
банкноты – 50, 100, 500, 1000, 5000 рублей. Пользователь вводит стоимость товара. 
Рассчет минимального набора банкнот и монет необходимого для покупки товара. */

#include"pch.h"
#include <iostream>
#include "Math.h"
#include "conio.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	int s;
	double sd;
	int n1 = 0, n5 = 0, n2 = 0, n10 = 0, n50 = 0, n100 = 0, n500 = 0, n1000 = 0, n5000 = 0;

necorr:
	if (cin.fail()) 
	{
		cin.clear(); 
		cin.ignore(32767, '\n');
	}
	cout << "Введите целочисленную стоимость через точку" << endl;
	cin >> sd;
	s = sd;

	if (!cin) {
		cout << "Некорректный ввод" << endl;
		goto necorr;
	}
	else {
		if (s == sd) {
			cout << abs(s) << endl;
		}
		else {
			cout << "Введено не целое число, значения после точки будут отброшены" << endl;
			cout << abs(s) << endl;
		}
	}

	if (s < 0) {
		s = abs(s);

	schet:

		n5000 = s / 5000;
		s = s % 5000;
		n1000 = s / 1000;
		s = s % 1000;
		n500 = s / 500;
		s = s % 500;
		n100 = s / 100;
		s = s % 100;
		n50 = s / 50;
		s = s % 50;
		n10 = s / 10;
		s = s % 10;
		n5 = s / 5;
		s = s % 5;
		n2 = s / 2;
		s = s % 2;
		n1 = s;

		printf("n5000 = %i \n", n5000);
		printf("n1000 = %i \n", n1000);
		printf("n500  = %i \n", n500);
		printf("n100  = %i \n", n100);
		printf("n50   = %i \n", n50);
		printf("n10   = %i \n", n10);
		printf("n5    = %i \n", n5);
		printf("n2    = %i \n", n2);
		printf("n1    = %i \n", n1);
	}
	else {
		goto schet;
	}
	system("pause");
	return 0;
}