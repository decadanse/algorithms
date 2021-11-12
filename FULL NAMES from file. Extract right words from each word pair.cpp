/*Задан текст. Каждая строка текста имеет следующую структуру: 
Фамилия - <фамилия> Имя - <имя> Отчество - <отчество>. 
Выделить правые слова из каждой пары слов.*/

//файл открывается, текст считывается и обрабатывается

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <experimental/filesystem>
#include <regex>
#include <locale> 
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;
using namespace experimental::filesystem;

char* transform_str(char* s, int(*fp)(int)) {

	char* res = s;
	while (*s) {
		*s = fp(*s);
		++s;
	}
	return res;
}

void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int i = 0;
	string surname, name, patronymic;
newr:
	cout << "Укажите имя файла с расширением" << endl;
	string nazv;
	cout << "Введите адрес входного файла: " << endl;
	cin >> nazv;

	i = 0;

	ifstream file;
	file.open(nazv);

	file.open(nazv, ios::in | ios::binary);
	if (!is_regular_file(nazv)) {
		cout << "Ошибка! Файла не существует. Возможно вы ввели зарезервированное имя MS DOS. Повторите ввод." << endl;
		goto newr;
	}
	file.close();

	ofstream("vivod.txt", std::ofstream::out);

	file.open(nazv);
	if (file.is_open())
	{
	again:
		file >> surname >> name >> patronymic; //считывает через пробел
		if (file.eof())
		{
			cout << "Фамилия: ";
			SetColor(9, 0);
			cout << surname << " ";
			SetColor(7, 0);

			cout << "Имя: ";
			SetColor(9, 0);
			cout << name << " ";
			SetColor(7, 0);

			cout << "Отчество: ";
			SetColor(9, 0);
			cout << patronymic << endl;
			SetColor(7, 0);

			cout << endl;

			ofstream viot;
			viot.open("vivod.txt", ios::app); // открываем файл для вывода, запись в конец
			viot << "Фамилия - ";
			viot << surname << " "; // выводим сформированную строку
			viot << "Имя - ";
			viot << name << " ";
			viot << "Отчество - ";
			viot << patronymic << endl;
			viot.close();
			goto end;
			// достигли конца файла
		}
		if ('\n') {
			cout << "Фамилия: ";
			SetColor(9, 0);
			cout << surname << " ";
			SetColor(7, 0);

			cout << "Имя: ";
			SetColor(9, 0);
			cout << name << " ";
			SetColor(7, 0);

			cout << "Отчество: ";
			SetColor(9, 0);
			cout << patronymic << endl;
			SetColor(7, 0);

			ofstream viot;
			viot.open("vivod.txt", ios::app); // открываем файл для вывода
			viot << "Фамилия - ";
			viot << surname << " "; // выводим сформированную строку
			viot << "Имя - ";
			viot << name << " ";
			viot << "Отчество - ";
			viot << patronymic << endl;
			viot.close();
			goto again;
		}
	}
	else {
		cout << "Ошибка открытия файла. Такого файла не существует" << endl;
		system("pause");
		return 0;
	}
	file.close();
end:
	system("pause");
	return 0;
}