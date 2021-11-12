#include <iostream>
#include <cmath>

using namespace std;
/*Вывести на экран
1) количество шагов и максимальное количество шагов для данного N
2) для каждого шага: номер шага и номер этажа, с которого производится бросок на данном шаге
3) номер этажа, на котором первый шар разбился
4) номер этажа, на котором второй шар разбился (или не разбился вообще)*/
int main()
{
	setlocale(LC_ALL, "Rus");
	int N, k, balls = 2, count = 0;
	int p;
	double n;
	int identifikator_not_povtor = 0;
	cout << "введите количество этажей" << endl;
	cin >> N;
	cout << "введите этаж на котором шар разобьется" << endl;
a:
	cin >> k;
	if (k <= 0) {
		cout << "error повторите ввод" << endl;
		goto a;
	}
	n = ceil((-1 + sqrt(1 + 8 * N)) / 2);
	p = n;
	int forshag = n;
	int max_not_broken = 0;

		next:
		if (k > p) {

			if (max_not_broken < p) {
				max_not_broken = p;
			}

			if (balls == 2) {
				count++;
				cout << p << " - этаж. Первый шар не разбился" << endl;
				forshag--;
				if (p > N) {
					cout << "шары не разобьются" << endl;
					goto end;
				}
				
				if ((p + forshag) > N) {
					if ((p + 1) > N) {
						cout << "шары не разобьются" << endl;
						goto end;
					}
					p++;
					goto next;
				}
				p = p + forshag;

				goto next;
			}
			else {
				count++;
				cout << p << " - этаж. Второй шар не разбился" << endl;
				p++;

				if (p == identifikator_not_povtor) { //именно после p++
					max_not_broken = identifikator_not_povtor;
					goto output;
				}

				goto next;
			}
		}
		else {
			if (balls == 2) {
				count++;

				identifikator_not_povtor = p;//чтобы избежать повторное сбрасывание с одного и того же этажа

				if (p > N) {
					max_not_broken = N;
					goto output;
				}

				cout << p << " - этаж. Первый шар разбился" << endl;
				balls--;
				/*if (p > N) {
					max_not_broken = N;
					goto output;
				}*/
				
				p = max_not_broken + 1;
				if (max_not_broken == 0) {
					p = 1;
				}
				goto next;
			}
			else {
				count++;
				cout << p << " - этаж. Второй шар разбился" << endl;
				max_not_broken = p;
				balls--;
				goto output;
			}
		}
		output:
		cout << "шары разбиваются на " << max_not_broken << " этаже" << endl;
		cout << "максимальное количество бросков = " << n << endl; 
		cout << "фактическое количество бросков = " << count << endl;
	
	end:
	system("pause");
	return 0;
}