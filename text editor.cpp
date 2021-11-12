/*
1.	Поиск в строке
2.	Вставка текста из файла
3.	Замена всех первых строчных букв слов прописными
*/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <windows.h>
#include <experimental/filesystem>
#include <ctype.h>
#include <regex>

using namespace std;
using namespace experimental::filesystem;

HANDLE hStdout;

void SetColor(int text, int background)
{
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, (WORD)((background << 4) | text));
}

string input, keys, path, line, chik;
int first, second, i, j, act, counter, position;

string upperer(string& input) { //, char c) {

	int position = 0;
	string new_inp = input;
	new_inp[position] = toupper(input[position]);
	
	while (input.find(' ', position) != -1)
	{
		position = input.find(' ', position) + 1;
		new_inp[position] = toupper(input[position]);			
	}
	
	cout << new_inp << endl << endl;
	
	return (new_inp);
}

void searCH1(string keys, string input) {

	j = 0;
	counter = 0;
	position = 0;
	int how_long = keys.length();
	int input_long = input.length();
	int ctr = 0, save_ctr = 0, ctr1;
	int finder;

	while (input.find(keys, position) != -1)
	{
		//cout << "Первое найденное начинается с позиции " << input.find(keys, position) << endl;
		finder = input.find(keys, position);
		while (input_long != 0) { 
			for (i = finder; i < finder + how_long; i++) {
							   
				if ((j >= finder) && (j < (finder + how_long))) {
					SetColor(14, 8);
				}				
				cout << input[j];
				SetColor(15, 0);

				j++;
				input_long--;
			}
		}

		position = input.find(keys, position) + 1;
		counter++;
	}
	/*}*/
	cout << endl << "Matches = " << counter << endl << endl;
}

void searCH(string keys, string input) {

	char key = keys[0];
	j = 0;
	counter = 0;
	position = 0;
	int input_long = input.length();

	for (i = 0; i < input_long; i++) {

		if (input[i] == key) {
			SetColor(14, 8);
			counter++;
		}
		cout << input[i];
		SetColor(15, 0);
	}

	cout << "\nWas founded  " << counter << " matches\n\n";

}

int main() {

	setlocale(LC_ALL, "Rus");

	string nazv;

again:
	cout << "Print 1 for insert text from file" << endl;
	cout << "Print 2 for search" << endl;
	cout << "Print 3 for perevoda pervyix bukv v upper case" << endl;//Замена всех первых строчных букв слов прописными
	cout << "Print 0 for exit" << endl;
	cin >> act;
	switch (act)
	{
	case 1:
	{
		cout << "Print finename with extension" << endl;
		cout << "Print filename: " << endl;

		cin >> nazv;

		nazv = nazv + ".txt";
		cout << nazv << endl;

		ifstream file;
		file.open(nazv);

		file.open(nazv, ios::in | ios::binary);
		if (!is_regular_file(nazv)) {
			cout << "Error! File does not exist. Try again." << endl;
			goto again;
		}
		file.close();

		file.open(nazv);
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		while (getline(file, line))//считывает строки из файла
		{
			input += line;
			input += ' ';
		}
		file.close();
		cout << "Text: " << input << endl << endl;
		break;

		break;
	}
	case 2:
	{
		//cout << "Введите искомое ";
		cout << "Register NOT ignored. Print searched symbol: ";
		cin >> keys;
		cout << endl;
		searCH(keys, input);
		break;
	}
	case 3:
	{
		input = upperer(input);
		break;
	}
	case 0:
	{
		system("pause");
		return 0;
	}
	default:
		cout << "This command does not exist. End of work.\n";
		return 0;
	}
	goto again;
	return 0;
}