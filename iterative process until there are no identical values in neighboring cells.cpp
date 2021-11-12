//Программа итерационного процесса до случая отсутствия одинаковых значений в соседних ячейках.
/*
У пользователя запрашивается ввести размер матрицы M x N. 
Программа заполняет случайным образом массив значениями от 0 до 9. 
При вычислении на каждой итерации сначала находятся одинаковые значения в соседних 
ячейках по строкам и производится замена левого числа на его удвоенное значение, 
правого числа на случайное (от 0 до 9), а затем выполняется аналогичное действия для столбцов. 
В случае получения значений ячейки после удвоения больше 9, значение уменьшается на 10. 
Ячейки, подверженные изменению на каждой итерации требуется выделить цветом. 
Цвета для изменений строк и столбцов различные. 
Вывод на экран модифицированного массива проводить после каждой итерации. 
Продолжение вычислений производить после подтверждения пользователя. 
Требуется продолжать итерационный процесс до случая отсутствия одинаковых значений в соседних ячейках.
*/

#include <iostream>
#include "windows.h"
#include "locale"
#include <ctime> //для генерации разных чисел

using namespace std;
HANDLE hConsoleHandle;

int main()
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	GetConsoleScreenBufferInfo(hConsoleHandle, &start_attribute);
	setlocale(LC_ALL, "Rus");
	srand(time(NULL)); //для генерации разных чисел

	int row, col;//строки колонки вместо i j 
	char c;

ag1:
	cout << "Введите количество строк:";
	cin >> row;
	if (!cin || row < 0 || row == 1 || row == 0) {
		cout << "Неправильный ввод. Или введено слишком большое значение.\n";
		system("pause");
		return 0;
	}

	cout << "Введите количество столбцов:";
	cin >> col;
	if (!cin || col < 0 || col == 1 || col == 0) {
		cout << "Неправильный ввод. Или введено слишком большое значение. \n";
		system("pause");
		return 0;
	}

	cout << "Исходный  массив:\n";

	int** array = new int* [col];
	for (int count = 0; count < col; count++)
		array[count] = new int[row];


	for (int count_row = 0; count_row < row; count_row++) {
		for (int count_col = 0; count_col < col; count_col++) {
			array[count_row][count_col] = rand() % 9;
			cout << array[count_row][count_col];
		}
		cout << endl;
	}

	int** array2 = new int* [col];
	for (int count = 0; count < col; count++)
		array2[count] = new int[row];

	int count_col;
	int count_row;


povtor:

	cout << "Преобразованный массив: " << endl;

	for (count_row = 0; count_row < row; count_row++) { // <row-1
		for (count_col = 0; count_col < col-1; count_col++) { // <col-1
			if (array[count_row][count_col] == array[count_row][count_col + 1]) {
				array[count_row][count_col] = (int)array[count_row][count_col] * 2 % 10;
				array[count_row][count_col + 1] = rand() % 9;

				array2[count_row][count_col] = 1;
				array2[count_row][count_col + 1] = 1;

				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			}
			SetConsoleTextAttribute(hConsoleHandle, start_attribute.wAttributes);
		}
	}

	for (count_row = 0; count_row < row-1; count_row++) { 
		for (count_col = 0; count_col < col; count_col++) { 

			if (array[count_row][count_col] == array[count_row + 1][count_col]) {
				array[count_row][count_col] = (int)array[count_row][count_col] * 2 % 10;
				array[count_row + 1][count_col] = rand() % 9;

				array2[count_row][count_col] = 2;
				array2[count_row + 1][count_col] = 2;

				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}
			SetConsoleTextAttribute(hConsoleHandle, start_attribute.wAttributes);
		}
	}

	for (count_row = 0; count_row < row; count_row++) {
		for (count_col = 0; count_col < col; count_col++) {
			if (array2[count_row][count_col] == 1) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			}
			else if (array2[count_row][count_col] == 2) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}
			cout << array[count_row][count_col];
			SetConsoleTextAttribute(hConsoleHandle, start_attribute.wAttributes);
		}
		cout << endl;
	}

	char ch;
	for (count_row = 0; count_row < row; count_row++) {
		for (count_col = 0; count_col < col; count_col++) {
			if(array2[count_row][count_col] != 0){

				for (count_row = 0; count_row < row; count_row++) {
					for (count_col = 0; count_col < col; count_col++) {
						array2[count_row][count_col] = 0;
					}
				}
				cout << "Нажмите 1 чтобы повторить итерацию или нажмите 0 чтобы завершить программу" << endl;
				cin >> ch;
				if (ch == '1') {
					goto povtor;
				}
				else if (ch == '0') {
					goto end;
				}
			}
		}
	}
	end:
	SetConsoleTextAttribute(hConsoleHandle, start_attribute.wAttributes);
	system("pause");
	return 0;
}