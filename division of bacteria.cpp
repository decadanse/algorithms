#include <iostream>
#include"windows.h"
#include "locale"
#include <ctime>
using namespace std;
HANDLE hConsoleHandle;

int main(){
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	GetConsoleScreenBufferInfo(hConsoleHandle, &start_attribute);
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int row, col;//строки колонки вместо i j 
	int P;
	int row_0, col_0;
	cout << "Введите пороговую вероятность:";
	cin >> P;

	cout << "Введите стартовую строку:";
	cin >> row_0;

	cout << "Введите стартовый столбец:";
	cin >> col_0;


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

	int** array = new int* [col];
	int** array2 = new int* [col];
	int** array_prom = new int* [col];
	for (int count = 0; count < col; count++) {
		array[count] = new int[row];
		array2[count] = new int[row];
		array_prom[count] = new int[row];
	}

	for (int count_row = 0; count_row < row; count_row++) {
		for (int count_col = 0; count_col < col; count_col++) {
			array[count_row][count_col] = rand() % 100;
			array2[count_row][count_col] = 4;
			array_prom[count_row][count_col] = 4;
			cout << array[count_row][count_col]<< " ";
		}
		cout << endl;
	}

	int count_col;
	int count_row;

	int id, counter_id1 = 0, counter_id2 = 0;
	int N = 0;

	array2[row_0-1][col_0-1] = 1;

	for (int count_row = 0; count_row < row; count_row++) {
		for (int count_col = 0; count_col < col; count_col++) {
			array_prom[count_row][count_col] = array2[count_row][count_col];
		}
	}

	array[row_0-1][col_0-1] = 0;
	int yes = 0;

povtor: //условие повтора на существование хотя бы одной 4-ки
	N++;
	cout << "Преобразованный массив: " << endl;

	for (count_row = 0; count_row < row; count_row++) {
		for (count_col = 0; count_col < col; count_col++) {
			if (yes == 1){ //если остались белые пятна, но нет крайних 1-ц
				if (count_row < (row - 1)) {
					if (array[count_row + 1][count_col] > P) { //проверка вероятности
						array_prom[count_row + 1][count_col] = 0;
					}
					else {
						array_prom[count_row + 1][count_col] = 1;
					}
				}
				if (count_col < (col - 1)) {
					if (array[count_row][count_col + 1] > P) { //проверка вероятности
						array_prom[count_row][count_col + 1] = 0;
					}
					else {
						array_prom[count_row][count_col + 1] = 1;
					}
				}
				if (count_row > 0) {
					if (array[count_row - 1][count_col] > P) { //проверка вероятности
						array_prom[count_row - 1][count_col] = 0;
					}
					else {
						array_prom[count_row - 1][count_col] = 1;
					}
				}
				if (count_col > 0) {
					if (array[count_row][count_col - 1] > P) { //проверка вероятности
						array_prom[count_row][count_col - 1] = 0;
					}
					else {
						array_prom[count_row][count_col - 1] = 1;
					}
				}
				if (count_row > 0 && count_col > 0) {
					if (array[count_row - 1][count_col - 1] > P) { //проверка вероятности
						array_prom[count_row - 1][count_col - 1] = 0;
					}
					else {
						array_prom[count_row - 1][count_col - 1] = 1;
					}
				}
				if (count_col > 0 && count_row < (row - 1)) {
					if (array[count_row + 1][count_col - 1] > P) { //проверка вероятности
						array_prom[count_row + 1][count_col - 1] = 0;
					}
					else {
						array_prom[count_row + 1][count_col - 1] = 1;
					}
				}
				if (count_row < (row - 1) && count_col < (col - 1)) {
					if (array[count_row + 1][count_col + 1] > P) { //проверка вероятности
						array_prom[count_row + 1][count_col + 1] = 0;
					}
					else {
						array_prom[count_row + 1][count_col + 1] = 1;
					}
				}
				if (count_row > 0 && count_col < (col - 1)) {
					if (array[count_row - 1][count_col + 1] > P) { //проверка вероятности
						array_prom[count_row - 1][count_col + 1] = 0;
					}
					else {
						array_prom[count_row - 1][count_col + 1] = 1;
					}
				}
			}
			else {
				if (array2[count_row][count_col] == 1) {
					//if (count_row > 0 && count_col > 0 && count_row 
					if (count_row < (row - 1)) {
						if (array[count_row + 1][count_col] > P) { //проверка вероятности
							array_prom[count_row + 1][count_col] = 0;
						}
						else {
							array_prom[count_row + 1][count_col] = 1;
						}
					}
					if (count_col < (col - 1)) {
						if (array[count_row][count_col + 1] > P) { //проверка вероятности
							array_prom[count_row][count_col + 1] = 0;
						}
						else {
							array_prom[count_row][count_col + 1] = 1;
						}
					}
					if (count_row > 0) {
						if (array[count_row - 1][count_col] > P) { //проверка вероятности
							array_prom[count_row - 1][count_col] = 0;
						}
						else {
							array_prom[count_row - 1][count_col] = 1;
						}
					}
					if (count_col > 0) {
						if (array[count_row][count_col - 1] > P) { //проверка вероятности
							array_prom[count_row][count_col - 1] = 0;
						}
						else {
							array_prom[count_row][count_col - 1] = 1;
						}
					}
					if (count_row > 0 && count_col > 0) {
						if (array[count_row - 1][count_col - 1] > P) { //проверка вероятности
							array_prom[count_row - 1][count_col - 1] = 0;
						}
						else {
							array_prom[count_row - 1][count_col - 1] = 1;
						}
					}
					if (count_col > 0 && count_row < (row - 1)) {
						if (array[count_row + 1][count_col - 1] > P) { //проверка вероятности
							array_prom[count_row + 1][count_col - 1] = 0;
						}
						else {
							array_prom[count_row + 1][count_col - 1] = 1;
						}
					}
					if (count_row < (row - 1) && count_col < (col - 1)) {
						if (array[count_row + 1][count_col + 1] > P) { //проверка вероятности
							array_prom[count_row + 1][count_col + 1] = 0;
						}
						else {
							array_prom[count_row + 1][count_col + 1] = 1;
						}
					}
					if (count_row > 0 && count_col < (col - 1)) {
						if (array[count_row - 1][count_col + 1] > P) { //проверка вероятности
							array_prom[count_row - 1][count_col + 1] = 0;
						}
						else {
							array_prom[count_row - 1][count_col + 1] = 1;
						}
					}
				}
			}
		}
	}

	for (int count_row = 0; count_row < row; count_row++) {
		for (int count_col = 0; count_col < col; count_col++) {
			if (array_prom[count_row][count_col] != 4) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			}
			/*if (array_prom[count_row][count_col] == 1) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			}
			else if (array_prom[count_row][count_col] == 0) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}*/
			cout << array_prom[count_row][count_col] << " ";
			SetConsoleTextAttribute(hConsoleHandle, start_attribute.wAttributes);
		}
		cout << endl;
	}

	id = 0;
	counter_id2 = counter_id1;
	counter_id1 = 0;
	for (count_row = 0; count_row < row; count_row++) {
		for (count_col = 0; count_col < col; count_col++) {
			array2[count_row][count_col] = array_prom[count_row][count_col];

			if (array2[count_row][count_col] == 4) {
				id = 1;
				counter_id1++; //проверка на разнику количества 4-к в прошлом и этом цикле
			}
		}
	}
	if (counter_id1 <= 4) {
		if (array2[0][0] == 4) {
			if (array2[0][0] > P)
				array_prom[0][0] = 0;
			else
				array_prom[0][0] = 1;
		}
		if (array2[row - 1][col - 1] == 4) {
			if (array2[row - 1][col - 1] > P)
				array_prom[row - 1][col - 1] = 0;
			else
				array_prom[row - 1][col - 1] = 1;
		}
		if (array2[row - 1][0] == 4) {
			if (array2[row - 1][0] > P)
				array_prom[row - 1][0] = 0;
			else
				array_prom[0][0] = 1;
		}
		if (array2[0][col - 1] == 4) {
			if (array2[0][col - 1] > P)
				array_prom[0][col - 1] = 0;
			else
				array_prom[0][col - 1] = 1;
		}
	}

	if (counter_id1 == counter_id2) {
		yes = 1;
	}

	if (id == 1) {
		goto povtor;
	}


	cout << "N итераций = " << N << endl;
	system("pause");
	return 0;
}