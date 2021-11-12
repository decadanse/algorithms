#include <iostream>
#include <cmath>
#include <ctime>
/*Решить задачу Леонардо Фибоначчи :
"Сколько пар кроликов можно получить от одной пары кроликов в год,
если каждая пара ежемесячно дает еще одну пару приплода,
каждая новая пара становится способной к размножению в возрасте одного месяца и в течение года кролики не умирают."
Использовать два алгоритма : 1) с рекурсией 2) без рекурсии
Пользователь вводит : n = количество месяцев
	Вывести на экран для каждого шага :
номер месяца, количество пар кроликов, приближенное значение, значение Fn + 1 / Fn, приближенное значение номера числа Фибоначчи
	Сравнить с асимптотикой при больших n.
	Найти все n, для которых а) Fn = n б) Fn = n2 в) Fn - простое
	Найти НОД для двух чисел Фибоначчи с номерами m и n и показать, что НОД(Fn, Fm) = НОД(n, m)*/
using namespace std;

unsigned long long int f(int n)
{
	//cout << n <<endl;
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	return f(n - 1) + f(n - 2);
}

unsigned long long int fnoc(int n)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	return fnoc(n - 1) + fnoc(n - 2);
}

bool foo(long long int n, long long int i = 2) { //проверка простоты
	if (i > sqrt(n))return true;
	return n % i ? foo(n, ++i) : false;
}

int evk(int a, int b) {
	return a ? evk(b % a, a) : b;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	double nod1, nod2, priblizh, priblizh_Fiba, znachenie; 
	int n, m, rabbits;
	cout << "введите n" << endl;
	cin >> n;
	cout << "введите m" << endl;
	cin >> m;
	double A[100] = { 0 }, B[100] = { 0 }, C[100] = { 0 };
	int f1, f2;
	int i;

	//cout << "рекурсия для n:" << endl;
	f1 = f(n);
	//cout << "рекурсия для m:" << endl;
	f2 = f(m);
	nod1 = evk(n, m);
	nod2 = evk(f1, f2);
	int f3 = f(nod1);
	cout << "f(evk(n, m)) = " << f3 << endl;
	cout << "evk(f(n), f(m)) = " << nod2 << endl;

	cout << "рекурсией: " << endl;
	clock_t t0 = clock();
	//что-нить делаем
	printf("-----------------------------------\n");
	printf("|   N  |   F  |асимптотика|Fn+1/Fn|\n");
	printf("-----------------------------------\n");
	
	for (i = 1; i < n; i++) {
		f1 = f(i);
		znachenie = fnoc(i + 1) / fnoc(i);
		priblizh = pow(((1 + sqrt(5)) / 2), i) / sqrt(5);
		priblizh_Fiba = pow((1 + sqrt(5)), i) / (sqrt(5) * pow(2, i));

		printf("|%-6i|%-6i|%-11.8lf|%-7.4lf|\n", i, f1, priblizh, znachenie);
	/*	cout << "рекурсией: " << endl;
		cout << "месяц " << i << endl;
		cout << "значение Fn+1/Fn = " << znachenie << endl;
		cout << "ассимптотика = " << priblizh << endl;*/
	}
	printf("-----------------------------------\n");
	clock_t t1 = clock();
	cout << "time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
	//znachenie = fnoc(n + 1) / fnoc(n);
	//priblizh = pow(((1 + sqrt(5)) / 2), n) / sqrt(5);
	//priblizh_Fiba = pow((1 + sqrt(5)), n) / (sqrt(5) * pow(2, n));

	rabbits = f1 / 2;
	int pare_alive_rabbits = rabbits;
	int alive_rabbits = f1;
	if (n > 12) {
		pare_alive_rabbits = (f1 - fnoc(n - 12))/2; //удаляем мертвых, если надо
		alive_rabbits = f1 - fnoc(n - 12);
	}
	
	//cout << "рекурсией: "<< endl;
	//cout << "месяц " << n << endl;
	//cout << "значение Fn+1/Fn = " << znachenie << endl;
	//cout << "ассимптотика = " << priblizh << endl;
	cout << "приближенное значение номера числа Фибоначчи = " << priblizh_Fiba << endl;
	if (priblizh == priblizh_Fiba) {
		cout << "приближенное значение номера числа Фибоначчи = ассимптотикe" << endl;
	}
	cout << "кролики = " << f1 << endl;
	cout << "количество пар кроликов = " << rabbits << endl;
	cout << "количество кроликов, если кролики умирают = " << alive_rabbits << endl;
	cout << "количество пар, если кролики умирают = " << pare_alive_rabbits << endl << endl;


	cout << "циклом: " << endl;
	t0 = clock();
	printf("-----------------------------------\n");
	printf("|   N  |   F  |асимптотика|Fn/Fn-1|\n");
	printf("-----------------------------------\n");
	int M[100] = { 0 };
	M[0] = 1;
	M[1] = 1;
	priblizh = pow(((1 + sqrt(5)) / 2), 1) / sqrt(5);
	printf("|%-6i|%-6i|%-11.8lf|%-7.4lf|\n", 1, 1, priblizh, 1.0);
	for (i = 2; i < n; i++)
	{
		M[i] = M[i - 1] + M[i - 2];
		if (i == 2) {
			M[i] = 1;
		}
		znachenie = M[i] / M[i - 1];
		priblizh = pow(((1 + sqrt(5)) / 2), i) / sqrt(5);
		priblizh_Fiba = pow((1 + sqrt(5)), i) / (sqrt(5) * pow(2, i));
		printf("|%-6i|%-6i|%-11.8lf|%-7.4lf|\n", i, M[i], priblizh, znachenie);
	}
	printf("-----------------------------------\n");
	t1 = clock();
	cout << "time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
	cout << "месяц " << n << endl;
	cout << "количество кроликов = " << M[i - 1] << endl;

	//Найти все n, для которых а) Fn = n б) Fn = n^2 в) Fn - простое
	int ft, st = 1;
	for (i = 1; i < n; i++) {
		ft = fnoc(i);
		if (ft == i) {
			if (foo(i)) {
				C[i] = i;
			}
			A[i] = i;
		}
		if (ft == (i*i)) { 
			B[i] = i;
		}
	}

	for (i = 1; i < 100; i++) {
		if (A[i] != 0) {
			cout << "f от " << i << " = " << A[i] << endl;
		}
	}
	for (i = 1; i < 100; i++) {
		if (B[i] != 0) {
			cout << "f от " << i << " (n^2) = " << B[i] << endl;
		}
	}
	for (i = 1; i < 100; i++) {
		if (C[i] != 0) {
			cout << "f от " << i << " , где n = " << C[i] << " - простое число" << endl;
		}
	}
	cout << endl<<endl;

	system("pause");
	return 0;
}