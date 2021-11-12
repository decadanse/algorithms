//#include "stdafx.h"
#include "pch.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <io.h> 
#include <vector>
#include <stdio.h> 
#include <time.h>
#include <iomanip>
#include <math.h> // для ceil

using namespace std;

//#define check
//#define check1
//#define under_matrix
//#define mech1

#define mech


using namespace std;

typedef unsigned long T;
typedef vector <T> VT; //vector_type

typedef vector<int> VI; //vector_int
typedef vector<vector<int>> Matrix;

vector <T> srav; //Сравнения
VT per;	//Перестановки

Matrix rand_m;	//random matrix-massiv
Matrix massiv;	//matrix-massiv

VI vector_;
VI rand_vector;
Matrix m_after_line;

#ifdef under_matrix
Matrix under_m;
#endif

#ifdef mech
VI vvtr;
VI vvtr_sav;
#endif

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

//ms_param - massive parametr

void Bubble_sort(VI& ms_param, T& srav, T& per) {
	int u, v;
	bool stop = 0;
	v = 0;
	while (!stop) {
		stop = 1;
		u = 0;
		v++;
		while (1) {
			if (u >= ms_param.size() - v) break;
			srav++;
			if (ms_param[u] > ms_param[u + 1]) {
				swap(ms_param[u], ms_param[u + 1]);
				per++;
				stop = 0;
			}
			u++;
		}
	}
}

void Insertion_sort(VI& ms_param, T& srav, T& per) {
	int u, v;
	for (u = 1; u < ms_param.size(); u++) {
		v = u;
		if (ms_param[v - 1] <= ms_param[v])
			srav++;
		while (v > 0 && ms_param[v - 1] > ms_param[v]) {
			srav++;
			swap(ms_param[v], ms_param[v - 1]);

			//per++;

#ifdef mech1 
			cout << endl;
			for (int n = 0; n < ms_param.size(); n++)
			{
				cout << ms_param[n] << " ";
			}
#endif

			if (((v - 1) == 0) || ((v > 1) && (ms_param[v - 2] <= ms_param[v - 1])))
				per++;

			v--;
			if ((v > 0) && (ms_param[v - 1] <= ms_param[v]))
				srav++;

		}
	}
}

void Select_sort(VI& ms_param, T& srav, T& per) {
	int u, maxPos;
	bool stop = 0;
	for (u = 0; u < ms_param.size() - 1; u++)
	{
		maxPos = u;
		for (int v = u + 1; v < ms_param.size(); v++)
		{
			srav++;
			if (ms_param[v] < ms_param[maxPos]) maxPos = v;
		}
		if (maxPos != u)
		{
			swap(ms_param[u], ms_param[maxPos]);
			per++;
		}
	}
}

void Quick_sort(VI& ms_param, T& srav, T& per, int a = 0, int b = -2) {
	if (b == -2) b = ms_param.size() - 1;
	if (b - a > 1) {
		int u = a, v = b, mid = ms_param[(a + b) / 2];
		do
		{
			if (ms_param[u] >= mid)srav++;
			while (ms_param[u] < mid) {
				srav++;
				++u;
			}
			if (ms_param[v] <= mid)srav++;
			while (ms_param[v] > mid) {
				srav++;
				--v;
			}
			if (u <= v)
			{
				if (u < v && ms_param[u] != ms_param[v]) {
					per++;
					swap(ms_param[u], ms_param[v]);
#ifdef mech 
					cout << endl;
					for (int n = 0; n < ms_param.size(); n++)
					{
						cout << ms_param[n] << " ";
					}
#endif
				}
				u++;
				v--;
			}
		} while (u < v);
		if (a < v) Quick_sort(ms_param, srav, per, a, v);
		if (u < b) Quick_sort(ms_param, srav, per, u, b);
	}
	else if (b - a == 1) {
		srav++;
		if (ms_param[a] > ms_param[b]) {
			per++;
			swap(ms_param[a], ms_param[b]);
		}
	}
}

void Shell_sort(VI& ms_param, T& srav, T& per) {
	if (ms_param.size() >= 4) {

		int stop = ms_param.size() / 2;

		while (stop > 0)
		{
			for (int u = 0; u < (ms_param.size() - stop); u++)
			{
				int v = u;

				//srav++;

				if (ms_param[v] <= ms_param[v + stop])
					srav++;

				while (v >= 0 && ms_param[v] > ms_param[v + stop])
				{
					srav++;
					per++;
					swap(ms_param[v], ms_param[v + stop]);
#ifdef mech 
					cout << endl;
					for (int n = 0; n < ms_param.size(); n++)
					{
						cout << ms_param[n] << " ";
					}
#endif
					v--;

				}

			}
			//stop /= 2;
			stop--;
		}
	}
	else Insertion_sort(ms_param, srav, per);
	//else Bubble_sort(ms_param, srav, per);
}

void matrix2vector(const Matrix& matrix_, VI& vector_)
{
	for (size_t i = 0; i < matrix_.size(); ++i)
		for (size_t j = 0; j < matrix_[i].size(); ++j)
			vector_.push_back(matrix_[i][j]);
}

void vector2matrix(VI& vector_, Matrix& matrix_, VI& m_for_size)
{
	int rows = m_for_size.size();
	int cols = rows * 2 - 1;
	int i = 0;
	for (int j = 0; j < rows; j++)
		for (int k = 0; k < cols; k++)
			matrix_[j][k] = vector_[i++];
	vector_.clear();
}

void spir(Matrix mat, VI& vector, int s, int r)
{
	VI vector1lev = vector;

	cout << endl;
	int value = r * r;

	mat = m_after_line;

#ifdef check
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			mat[i][j] = 0;
			cout << setw(2) << mat[i][j];
		}
		cout << endl;
	}
#endif

	int cen = r / 2 + 1; //центр строк

#ifdef check
	cout << "vector = " << vector.size();
	cout << endl;
#endif

	//reverse(vector1lev.begin(), vector1lev.end());

	VI vector2prav;
	vector2prav.clear();

	int df = r * r;

#ifdef check
	cout << endl << "правый вектор" << endl;
#endif
	while (df != 0) {
		df--;
		vector2prav.push_back(vector1lev.back());
		vector1lev.pop_back();
#ifdef check
		cout << vector2prav.back() << ends;
#endif
	}

#ifdef check
	cout << "2prav = " << vector2prav.size() << endl;
	cout << endl << "левый (оставшийся) вектор" << endl;
	for (int i = 0; i < vector1lev.size(); ++i)
	{
		cout << vector1lev[i] << ends;
	}
	cout << endl << " 1lev = " << vector1lev.size() << endl;
	cout << endl << endl;
#endif

	int n = cen;
	int j = n - 1, i = 0;
	int plus = r + 1;

	int s_cen = mat.size() - cen + 1;
	//---------------------
	n = r;
	//----------------------
	int t = 1;
	i = 0;
	int v = 0;
	int s1 = 0;
	int r1 = 1;
	int l = 1, c = 0, d = 0;
	int f;
	f = n;
	while (t <= n * n)
	{
		//заполняем справа на лево
		for (j = s1; j < f; ++j)
		{
			mat[i][j + plus] = vector2prav.back();
			vector2prav.pop_back();
			++t;

		}v = j - 1;
		--j;
		//заполняем с верху вниз
		if (t <= n * n)
		{
			for (i = r1; i < f; ++i)
			{
				mat[i][j + plus] = vector2prav.back();
				vector2prav.pop_back();
				++t;
			}l = i - 1;
			--i;
		}
		//заполняем с лева на право
		if (t <= n * n)
		{
			for (j = v - 1; j >= c; --j)
			{
				mat[i][j + plus] = vector2prav.back();
				vector2prav.pop_back();
				++t;
			}
		}
		if (t <= n * n)
		{
			//заполняем с низу верх
			for (i = l - 1; i > d; --i)
			{
				mat[i][j + 1 + plus] = vector2prav.back();
				vector2prav.pop_back();
				++t;
			}
		}
		//уменьшаем параметры матрицы(что бы числа шли внутрь а не заполнялись поверх тех которы уже заполнены)
		--f;
		++s1;
		++r1;
		++c;
		++d;
		++i;
	}


	t = n * (n - 1);

	i = 0;
	v = 0;
	s1 = 0;
	r1 = 0;
	l = r;
	c = r;
	d = 0;
	f = n - 1;
	int f2 = f;
	t = 1;
	j = n;
	int x = 0;

	int for_propusk = 0;
	while (t <= n * (n + 1))
	{
		//заполняем с верху вниз  //нужно добавить один столбец - s = r*2 + 1, а не s = r*2-1
		if (t <= n * (n + 1))
		{
			for (i = s1; i < f + 1; ++i)
			{
				mat[i][j] = vector1lev.back();
				vector1lev.pop_back();
				++t;
			}l = i - 1;
			--i;
		}


		//заполняем справа на лево
		if (t <= n * (n + 1))
		{
			for (j = f2; j >= x; --j)
			{
				mat[i][j] = vector1lev.back();
				vector1lev.pop_back();
				++t;

			}
		}
		v = j + 1;
		++j;


#ifdef check
		cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << ends << "t=  " << t << endl;
		cout << "v.size = " << vector1lev.size() << endl;
#endif

		if (t <= n * (n + 1))
		{
			//заполняем с низу верх
			for (i = l - 1; i > r1; i--)
			{
#ifdef check
				//cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << endl;
#endif
				mat[i][j] = vector1lev.back();
				vector1lev.pop_back();
				++t;
			}
		}

		//заполняем с лева на право
		if (t <= n * (n + 1))
		{
			for (j = v; j < c; ++j)
			{
				mat[i][j] = vector1lev.back();
				vector1lev.pop_back();
				++t;
			}
		}

		//уменьшаем параметры матрицы
		--f;
		--f2;
		++x;
		--l;
		--j;
		++s1;
		++r1;
		--c;
		++d;
		++i;

#ifdef check
		cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << ends << "t=  " << t << endl;
		cout << "v.size = " << vector1lev.size() << endl;
#endif
	}

	for (int i = 0; i < mat.size(); i++) { //до последнего элемента
		for (int j = 0; j < mat[0].size(); j++) {
			printf("%2i ", mat[i][j]);
		}
		cout << endl;
	}
	cout << endl;

	//mat.clear();
}

void output_vector(VI& vector, Matrix& rand_m, Matrix& m_after_line)
{
	int r = rand_m.size();
	int s = r * 2 + 1;
	for (int i = 0; i < rand_m.size(); i++)
		rand_m[i].resize(s);

	int k = vector.size() - 1;

	//reverse(vector.begin(), vector.end());

	m_after_line = rand_m;

	//сортировка спиралью
	spir(m_after_line, vector, s, r);

	/*  //обычная сортировка массива по убыванию
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < s; j++) {
			m_after_line[i][j] = vector[k];
			vector.pop_back(); //удаление последнего
			k = vector.size() - 1;
			printf("%2i ", m_after_line[i][j]);
		}
		cout << endl;
	}*/

	vector.clear();

	//cout << endl << endl;
}

void to_vector(Matrix mat, VI& vector, int s, int r)
{
	VI vector1lev;
	vector1lev.clear();

	cout << endl;
	int value = r * r;

	//mat = m_after_line;

#ifdef check
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			mat[i][j] = 0;
			cout << setw(2) << mat[i][j];
		}
		cout << endl;
	}
#endif

	int cen = r / 2 + 1; //центр строк


	//reverse(vector1lev.begin(), vector1lev.end());

	VI vector2prav;
	vector2prav.clear();

	int df = r * r;

	int n = cen;
	int j = n - 1, i = 0;
	int plus = r + 1;

	int s_cen = mat.size() - cen + 1;
	//---------------------
	n = r;
	//----------------------
	int t = 1;
	i = 0;
	int v = 0;
	int s1 = 0;
	int r1 = 1;
	int l = 1, c = 0, d = 0;
	int f;
	f = n;
	while (t <= n * n)
	{
		//заполняем справа на лево
		for (j = s1; j < f; ++j)
		{
			vector2prav.push_back(mat[i][j + plus]); //после этой точки возникает превышение раз0мера вектоора. в этом цикле
			++t;

		}v = j - 1;
		--j;
		//заполняем с верху вниз
		if (t <= n * n)
		{
			for (i = r1; i < f; ++i)
			{
				vector2prav.push_back(mat[i][j + plus]);
				++t;
			}l = i - 1;
			--i;
		}
		//заполняем с лева на право
		if (t <= n * n)
		{
			for (j = v - 1; j >= c; --j)
			{
				vector2prav.push_back(mat[i][j + plus]);
				++t;
			}
		}
		if (t <= n * n)
		{
			//заполняем с низу верх
			for (i = l - 1; i > d; --i)
			{
				vector2prav.push_back(mat[i][j + 1 + plus]);
				++t;
			}
		}
		//уменьшаем параметры матрицы(что бы числа шли внутрь а не заполнялись поверх тех которы уже заполнены)
		--f;
		++s1;
		++r1;
		++c;
		++d;
		++i;
	}


	t = n * (n - 1);

	i = 0;
	v = 0;
	s1 = 0;
	r1 = 0;
	l = r;
	c = r;
	d = 0;
	f = n - 1;
	int f2 = f;
	t = 1;
	j = n;
	int x = 0;

	int for_propusk = 0;
	while (t <= n * (n + 1))
	{
		//заполняем с верху вниз  //нужно добавить один столбец - s = r*2 + 1, а не s = r*2-1
		if (t <= n * (n + 1))
		{
			for (i = s1; i < f + 1; ++i)
			{
				vector1lev.push_back(mat[i][j]);
				++t;
			}l = i - 1;
			--i;
		}


		//заполняем справа на лево
		if (t <= n * (n + 1))
		{
			for (j = f2; j >= x; --j)
			{
				vector1lev.push_back(mat[i][j]);
				++t;

			}
		}
		v = j + 1;
		++j;


#ifdef check1
		cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << ends << "t=  " << t << endl;
		cout << "v.size = " << vector1lev.size() << endl;
#endif

		if (t <= n * (n + 1))
		{
			//заполняем с низу верх
			for (i = l - 1; i > r1; i--)
			{
#ifdef check1
				//cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << endl;
#endif
				vector1lev.push_back(mat[i][j]);
				++t;
			}
		}

		//заполняем с лева на право
		if (t <= n * (n + 1))
		{
			for (j = v; j < c; ++j)
			{
				vector1lev.push_back(mat[i][j]);
				++t;
			}
		}

		//уменьшаем параметры матрицы
		--f;
		--f2;
		++x;
		--l;
		--j;
		++s1;
		++r1;
		--c;
		++d;
		++i;

#ifdef check1
		cout << "i=  " << i << ends << "j= " << j << ends << "l= " << l << ends << "t=  " << t << endl;
		cout << "v.size = " << vector1lev.size() << endl;
#endif
	}


#ifdef check1
	cout << "2prav = " << vector2prav.size() << endl;
	cout << endl << "левый (оставшийся) вектор" << endl;
	for (int i = 0; i < vector1lev.size(); ++i)
	{
		//vector.push_back(vector1lev[i]);
		cout << vector1lev[i] << ends;
	}
	cout << endl << "1lev = " << vector1lev.size() << endl;
#endif
	//нужен реверс правого. только правого. 
	reverse(vector2prav.begin(), vector2prav.end());
	// прибавляем вначале правый реверснутый, потом обычный простой левый
#ifdef check1
	cout << endl << "правый вектор" << endl;
	for (int i = 0; i < vector2prav.size(); ++i)
	{
		//vector.push_back(vector2prav[i]);
		cout << vector2prav[i] << ends;
	}
	cout << endl << "2prav = " << vector2prav.size() << endl;
	cout << endl;
#endif

	vector = vector2prav;
	for (int i = 0; i < vector1lev.size(); i++) { //до последнего элемента //тут error!!!! ошибка с back()

		vector.push_back(vector1lev[i]);
	}

	reverse(vector.begin(), vector.end());

#ifdef check1
	cout << endl << "size = " << vector.size() << endl; //что-то не то с добавлением в Vector

		//сложиить и вывести
	//need это :  vector = vector1lev + vector2prav;
	for (int i = 0; i < vector.size(); i++) {

		printf("%2i ", vector[i]);
	}
	cout << endl;
#endif
	vector1lev.clear();
	vector2prav.clear();
}
void Sort(int n) {

	switch (n) {
	case 0:
		cout << "Сортировка пузырьком" << endl;
		Bubble_sort(vector_, srav[n], per[n]); //работает		
		break;
	case 1:
		cout << "Сортировка вставками" << endl;
		Insertion_sort(vector_, srav[n], per[n]);
		break;
	case 2:
		cout << "Сортировка отбором" << endl;
		Select_sort(vector_, srav[n], per[n]);
		break;
	case 3:
		cout << "Быстрая сортировка" << endl;
		Quick_sort(vector_, srav[n], per[n]);
		break;
	case 4:
		cout << "Сортировка Шелла" << endl;
		Shell_sort(vector_, srav[n], per[n]);
		break;
	}

	output_vector(vector_, rand_m, m_after_line); // спираль
	//output((massiv));
}

//забор значений в массив-линию из массива для сортировки должен также осуществляться по спилрали (как и вывод)

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	massiv.clear();
	int s, r;
	double vvod;

	srav.assign(5, 0); //создание векторного контейнера-счетчика
#ifdef check
	cout << "Контейнеры-счетчики: ";
	for (int itr : srav)
		cout << itr << " ";
	cout << endl;
	//for (int i = 0; i < srav.size(); i++)
		//cout << srav[i] << " ";
#endif
	per.assign(5, 0);

	cout << "Введите количество строк (больше 1-й)" << endl;
	cin >> vvod;
	if (!cin || vvod < 0 || vvod == 0 || vvod == 1 || int(vvod) != vvod) {
		cout << "Неправильный ввод.\n";
		goto end;
	}
	r = vvod;
	if (r % 2 == 0) {
		r = r + 1;
	}
	s = r * 2 + 1;

	cout << endl;

	rand_m.resize(r);
#ifdef under_matrix
	under_m.resize(r);
#endif
	for (int i = 0; i < rand_m.size(); i++) {
		rand_m[i].resize(s);
#ifdef under_matrix
		under_m[i].resize(s);
#endif
	}

	for (int i = 0; i < rand_m.size(); i++) { //до последнего элемента
		for (int j = 0; j < rand_m[0].size(); j++) {
			rand_m[i][j] = rand() % 100;
			//rand_m[i][j] = 0;// rand() % 100;
			//rand_m[1][5] = 1;
			//rand_m[0][0]=1;

#ifdef under_matrix
			if (j < rand_m[0].size() / 2) { //s
				under_m[i][j] = 1;
			}
			else if (j >= ceil(rand_m[0].size() / 2)) {
				under_m[i][j] = 3;
			}
			else {
				under_m[i][j] = 2;
			}
#endif
		}
	}

	cout << "Исходный массив";
	cout << endl;

	output(rand_m);

#ifdef check
	output(under_m);
#endif

	//matrix2vector(rand_m, vector_);
	to_vector(rand_m, vector_, s, r);
	//reverse(vector_.begin(), vector_.end());
	rand_vector = vector_;

	cout << endl << endl;
	for (int n = 0; n < 5; n++)
	{
		//massiv = rand_m;
		vector_ = rand_vector;
		Sort(n);
	}

	printf("\n\nВид        Сравнения    Перестановки\n");
	cout << endl;
	//lu - usigned long 
	printf("Пузырьком %8lu   %10lu      \n", srav[0], per[0]);
	printf("Вставками %8lu   %10lu      \n", srav[1], per[1]);
	printf("Отбором   %8lu   %10lu      \n", srav[2], per[2]);
	printf("Быстрая   %8lu   %10lu      \n", srav[3], per[3]);
	printf("Шелла     %8lu   %10lu      \n", srav[4], per[4]);


#ifdef mech 
	cout << endl;
	vvtr.resize(7);
	vvtr_sav.resize(7);
	vvtr = { 0, 3, 5 ,1, 3 ,3 ,4 };
	//vvtr = { 4,0,5 ,1, 9,6 };
	//vvtr = { 9, 2, 4 ,6, 1 ,0 ,2 ,4,2,7,5,5,2,1 };
	//vvtr = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	vvtr_sav = { 0, 3, 5 ,1, 3 ,3 ,4 };

	for (int n = 0; n < 5; n++) {
		srav[n] = 0;
		per[n] = 0;
	}
	for (int n = 0; n < vvtr.size(); n++)
	{
		//vvtr[n] = rand() % 10;
		cout << vvtr[n] << " ";
	}
	cout << endl;


	for (int n = 0; n < 5; n++)
	{
		vvtr = vvtr_sav;

		switch (n) {
		case 0:
			cout << "bubble сортировка" << endl;
			Bubble_sort(vvtr, srav[n], per[n]); //работает		
			break;
		case 1:
			cout << "Сортировка вставками" << endl;
			Insertion_sort(vvtr, srav[n], per[n]);
			break;
		case 2:
			cout << "Сортировка отбором" << endl;
			Select_sort(vvtr, srav[n], per[n]);
			break;
		case 3:
			cout << "Быстрая сортировка" << endl;
			Quick_sort(vvtr, srav[n], per[n]);
			break;
		case 4:
			cout << "Сортировка Шелла" << endl;
			Shell_sort(vvtr, srav[n], per[n]);

		}
	}

	printf("\n\nВид        Сравнения    Перестановки\n");
	cout << endl;
	//lu - usigned long 
	printf("Пузырьком %8lu   %10lu      \n", srav[0], per[0]);
	printf("Вставками %8lu   %10lu      \n", srav[1], per[1]);
	printf("Отбором   %8lu   %10lu      \n", srav[2], per[2]);
	printf("Быстрая   %8lu   %10lu      \n", srav[3], per[3]);
	printf("Шелла     %8lu   %10lu      \n", srav[4], per[4]);
#endif

end:
	system("pause");
	return 0;
}