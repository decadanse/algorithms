/*Программа нахождения наибольшего общего делителя для двух положительных целых чисел.  
	Алгоритм нахождения наименьшего общего кратного для двух положительных целых чисел.

Вычисление НОД и НОК для чисел a и b.
Вычисление среднего числа итераций алгоритма для a = 1..b, b = b(всего b внешних циклов в программе).
*/


#include <iostream>

using namespace std;

int counter = 0;

int evk(int a, int b) {
	counter++;
	return a ? evk(b % a, a) : b;
}

int main(){
	int a, b, i, nod;

	a = 119;
	b = 544;

	nod = evk(a, b);
	int nok = a * b / nod;

	int a2 = 1;
	counter=0;

	for (a2 = 1; a2 <= b; a2++) { //перебор-подсчет уже циклом от 1 до максимального
			evk(a2, b);
			counter++;  //подсчет итераций
	}
	int sred = counter / b;

	cout << "NOD = " << nod << endl;
	cout << "NOK = " << nok << endl;
	cout << "srednee chislo iteracii pri a [1 ; b] = " << sred << endl;

	system("pause");
	return 0;
}