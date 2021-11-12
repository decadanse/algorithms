#include <iostream>
#include <iomanip> 
#include <cmath>
/*Написать программу приближенного вычисления значения А=lg(x) 
с заданной точностью k, используя алгоритм (Д.Э. Кнут "Исскусство программирования" стр. 45). 
Перевести из двоичной системы счисления в десятичную. Вычислитьабсолютную погрешность А-lg(x) и 
относительную погрешность asb((А-lg(x))/A) значения x в таблице для каждого варианта

Построить графики A, lg(x), A-lg(x),в Excel*/

using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");

	int k, b, n = 0, i, j;
	double A[10] = {}, tr, drob = 0, y[10], x[10] = { 3, 6.5, 16, 250.3, 384, 1400.2, 20341.1, 579334, 7831236, 9877332.2 };
	/*for (i = 0; i < 10; i++) {
		cout << "Введите элемент массива ";
		cin >> x[i];
	}
	cout << endl;*/
	double pogresht[10] = { 0 };
	double otnospogresht[10] = { 0 };
	
	for (i = 0; i < 10; i++) {
		y[i] = log10(x[i]);
	}

	cout << "Введите точность (количество знаков после запятой): ";
	cin >> k;

	for (i = 0; i < 10; i++) {
		tr = trunc(x[i]); //берется то, что до запятой
		if (tr >= 10) {
		again:
			//or just while(tr >= 10)
			tr = tr / 10;
			n++; // значение Целой части log

			if (tr >= 10) {
				goto again;
			}
		}

		for (j = 1; j <= k; j++) {
			tr = tr * tr;
			if (tr >= 1 && tr < 10) {
				b = 0;	
			}
			else {
				tr = tr / 10;
				b = 1;
			}

			drob = drob + b / pow(2, j);
		}
		A[i] = n + drob;
		pogresht[i] = abs(A[i] - y[i]);
		otnospogresht[i] = abs((A[i] - y[i]) / A[i]);
		cout << setprecision(k) << fixed;
		cout << " x= " << x[i] << " i= " << i << " A= " << A[i] << " y= " << y[i] << " погрешность= " << pogresht[i] << " относительная погрешность= " << otnospogresht[i] << endl;
		n = 0;
		drob = 0;
	}
	
	system("pause");
	return 0;
}