/*Программа для поиска по хэшам данных. В модуле поиска, предусмотрена реализация обработки случая, 
	при котором хэш-коды различных данных совпадают.*/ 
//Дан текст. Производится хэширование по блокам (в обратном порядке), содержащих в себе 5 элементов (символов).

#include <iostream>
#include <stdio.h>
#include <clocale>
#include <stdlib.h>
#include <string>
#include <fstream> 
#include <experimental/filesystem>
#include <io.h>
#include <vector>

using namespace std;
using namespace experimental::filesystem;

typedef unsigned long T;
typedef vector <T> VT; //vector_type


struct hesh {
	string str;
	int hasher;
};

typedef vector <hesh> VH;
VH arr;


int main()
{
	setlocale(LC_ALL, "Rus");

	int i, c, k, searched_hash = 0, counter = 0, j;
	char chr;
	string row, searched_row;
	ifstream file;
	string filename;

	ofstream out_file;
	string out_filename;

		cout << "Введите название файла с расширением: " << endl;
	cin >> filename;

	file.open(filename, ios::in | ios::binary);

	if (!is_regular_file(filename))
	{
		cout << "Ошибка! Неправильный ввод. " << endl;
		system("pause");
		return 1;
	}
	if (!file.is_open())
		cout << "Файл не открылся\n" << endl;

	while (file.get(chr))
	{
		row += chr;
	}
	cout << row << endl;
	int len = row.length();
	cout << endl;


	cout << row << endl << endl;

	cout << endl << "Cтрока в обратном порядке: " << endl << row << endl;
	reverse(row.begin(), row.end());

	int end = len / 5;
	hesh* stroka = new hesh[end];
	
	for (i = 0; i < end; i++)
	{
		stroka[i].hasher = 0;
	}

	cout << endl << endl << "Количество элементов = " << end << endl;
	k = 0; i = 0;

	
	while (i < end)
	{
		for (j = 0; j < 5; j++)
		{
			stroka[i].str += row[5 * (i)+j];
			stroka[i].hasher += (int)(row[5 * (i)+j]) * 19 * 137 % 403;
		}
		cout << stroka[i].str << " -> " << stroka[i].hasher << endl;
		i++;
	}

cout << endl << "Введите искомую строку. Будут считаны только первые пять символов: " << endl << endl;

	chr = getchar();
	for (i = 0; i < 5; i++)
	{
		chr = getchar();
		searched_row += chr;
	}

	string rew_row = searched_row;

	reverse(searched_row.begin(), searched_row.end());

	for (i = 0; i < searched_row.length(); i++)
	{
		searched_hash += searched_row[i] * 19 * 137 % 403;
	}

	cout << endl << "Hash искомой строки = " << searched_hash << endl;

	i = 0;
	counter = 0;
	cout << endl << "Cтроки с одинаковым искомым хешем: " << endl << endl;
	while (i < end)
	{
		if (stroka[i].hasher == searched_hash)
		{
			counter++;
			cout << stroka[i].hasher << " = " << stroka[i].str << endl;
		}
		i++;
	}

	if (counter = !0)
	{
		counter = 0;
		i = 0;
		while (i <= end)
		{
			if (stroka[i].hasher == searched_hash)
			{
				if (stroka[i].str == searched_row)
				{
					cout << endl << "Искомая строка: '" << rew_row << "' " << endl;
					counter++;
				}
			}
			i++;
		}
	}
	else
	{
		cout << "Строка не найдена" << endl;
	}
	if (counter == 0)
	{
		cout << "Строка не найдена" << endl;
	}
	else {
		cout << "Найденых строк: " << counter << endl;
	}


	system("pause");
	return 0;
}