/* Программа для поиска в массиве данных последовательным и бинарным (по возможности) методами. 
	В случае невозможности (из условий индивидуального задания) поиска бинарным методом, 
    проводится поиск бинарным методом одной буквы (цифры). */
//Дана матрица чисел. Найти все простые числа (до 50).

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

typedef unsigned long T;
typedef vector <T> VT; //vector_type

typedef vector<int> VI; //vector_int
typedef vector<vector<int>> Matrix;

Matrix rand_m;
Matrix massiv;

VI vector_;
VI rand_vector;
VT counter;

const int easy[15] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 }; //простые числа до 50

//последовательный поиск
void posled_poisk(Matrix& ms_param) {
	printf("-------------------------------------------\n");
	int n = ms_param.size();
	int m = ms_param[0].size();
	int i, j, u, v;
	int counter = 0;

	for (u = 0; u < n; u++) {
		for (v = 0; v < m; v++) {
			for (i = 0; i < 15; i++) {
				if (ms_param[u][v] == easy[i]) {
					printf("|Строка = %3i |Столбец = %3i |Число = %3i |\n", u + 1, v + 1, ms_param[u][v]);
					counter++;
				}
			}
		}
	}
	printf("-------------------------------------------\n");
	cout << endl << "Количество найденных простых чисел в последовательном поиске = " << counter << endl;
}

//бинарный поиск
void binar_poisk(VI vector_) {
	VI vect;
	int i, j, middle;
	int counter = 0;
	int rez = -1;
	for (i = 0; i < vector_.size(); i++) {
		vect.push_back(vector_[i]);
	}
	printf("--------------\n");
	for (i = 0; i < 15; i++) {
		int left = 0; int right = vector_.size() - 1;
		while (left <= right) {
			middle = left + (right - left) / 2;
			if (easy[i] == vector_[middle]) {
				auto const u = lower_bound(vect.begin(), vect.end(), easy[i]);
				auto const v = upper_bound(vect.begin(), vect.end(), easy[i]);

				for (auto j = u; j != v; ++j)
				{
					printf("|Число = %3i |\n", easy[i]);
					counter++;
				}

				break;
			}
			if (easy[i] < vector_[middle]) {
				right = middle - 1;
			}
			else
			{
				left = middle + 1;
			}
		}
	}
	printf("--------------\n");
	cout << endl << "Количество найденных простых чисел в бинарном поиске = " << counter << endl;
}

void output(Matrix massiv) {
	for (int i = 0; i < massiv.size(); i++)
	{
		for (int j = 0; j < massiv[0].size(); j++)
		{
			printf("%2i ", massiv[i][j]);
		}
		cout << endl;
	}
}

void Bubble_sort(VI& ms_param) {
	int u, v;
	bool stop = 0;
	v = 0;
	while (!stop) {
		stop = 1;
		u = 0;
		v++;
		while (1) {
			if (u >= ms_param.size() - v) break;
			if (ms_param[u] > ms_param[u + 1]) {
				swap(ms_param[u], ms_param[u + 1]);
				stop = 0;
			}
			u++;
		}
	}
}

void matrix2vector(const Matrix& matrix_, VI& vector_)
{
	for (size_t i = 0; i < matrix_.size(); ++i)
		for (size_t j = 0; j < matrix_[i].size(); ++j)
			vector_.push_back(matrix_[i][j]);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	massiv.clear();

	int k;
	int s, r;
	double vvod1, vvod2;

	cout << "Введите количество строк" << endl;
	cin >> vvod1;
	if (!cin || vvod1 < 0 || vvod1 == 0 || int(vvod1) != vvod1) {
		cout << "Неправильный ввод.\n";
		goto end;
	}
	r = vvod1;

	cout << "Введите количество столбцов" << endl;
	cin >> vvod2;
	if (!cin || vvod2 < 0 || vvod2 == 0 || int(vvod2) != vvod2) {
		cout << "Неправильный ввод.\n";
		goto end;
	}
	s = vvod2;
	cout << endl;

	rand_m.resize(r);

	for (int i = 0; i < rand_m.size(); i++) {
		rand_m[i].resize(s);
	}

	for (int i = 0; i < rand_m.size(); i++) {
		for (int j = 0; j < rand_m[0].size(); j++) {
			rand_m[i][j] = rand() % 50;
		}
	}
	cout << "Массив";
	cout << endl;
	output(rand_m);

	massiv = rand_m;

	cout << endl;
	cout << "Последовательный поиск" << endl;
	posled_poisk(massiv);



	matrix2vector(rand_m, vector_);
	rand_vector = vector_;

	cout << endl << endl;

	vector_ = rand_vector;
	Bubble_sort(vector_);

	cout << "Отсортированный массив" << endl;

	k = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < s; j++) {
			printf("%2i ", vector_[k]);
			k++;
		}
		cout << endl;
	}
	cout << endl;

	cout << "Бинарный поиск" << endl;
	binar_poisk(vector_);

	cout << endl;

end:
	system("pause");
	return 0;
}