//Перевод систем счисления

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <math.h> 
#include <locale> 
#include <cctype>
#include <sstream>
#define PROV

#define SSTR( x ) static_cast< std::ostringstream & >( \  ( std::ostringstream() << std::dec << x ) ).str()
/*int i = 42;
std::string s = SSTR("i is: " << i);
puts(SSTR(i).c_str());

Foo x(42);
throw std::runtime_error(SSTR("Foo is '" << x << "', i is " << i));*/
using namespace std;

//idea2 берется 2 char-a: до и после точки. обрабатываются отдельно. До - сделано белее-менее. После - сделать по новой.
template <typename T>
std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char out[] = { '0','1','2','3','4','5','6','7','8','9',
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X','Y','Z' };

	char ch[100] = { 0 };
	int i, l;
	double nch;
	int newch1 = 0;
	double newch2 = 0;
	int a, z;
	double n; //a - cистема cчисления, n - вводимое число
	cout << "startovaya cc" << endl;
	cin >> a;

	cout << "chislo" << endl;
	cin >> ch;
	int simv = strlen(ch);//сделать подсчет букв и присвоить i это значение

	cout << "konechnaya cc" << endl;
	cin >> z;

#ifdef PROV
	cout << "N znakov " << simv << endl;
#endif
	double cc = 0;//с попытка версия 2.0
	int f = 0;
	double c;
	int tochka = 0;
	c = atof(ch); //число введенное
	for (i = 1; i < simv; i++) {
		if (ch[i] == '.') {
			f = i; //знаки до точки
			tochka = i;
		}
	}

	int countdrobey;
	double ccobshee;
	double ccdrob;
	if (f != 0) {
		int csave = (int)c; //сохранить целую часть с
		int st;
		int f1 = simv - f - 1;//колнво знаков справа   -1 тк точку не включаем (дробные)
		int f2 = f; //кол-во знаков слева (целые)
		countdrobey = 0;
		ccdrob = 0;

		for (i = 0; i < simv; i++) {

			for (l = 0; l < 36; l++) {

				if (ch[i] == out[l]) {
					if (i < tochka) {

						cc = cc + l * pow(a, (f - i - 1));
#ifdef PROV
						cout << "cc " << cc << endl;
						cout << "l " << l << endl;
						cout << "f - i " << f - i << endl<<endl;
#endif
					}
					else if (i > tochka) {
						countdrobey++;
						//cc = cc + l * pow(a, (-countdrobey)); //good для 1й цифры
						ccdrob = ccdrob + pow(a, (-countdrobey))* l;
#ifdef PROV
						cout << "ccdrob " << ccdrob << endl;
						cout << "l " << l << endl;
						cout << "-countdrobey " << -countdrobey << endl;
						cout << " pow(a, (-countdrobey)) " << pow(a, (-countdrobey))*l << endl;
#endif
					}
				}
			}
		}
		ccobshee = cc + ccdrob;
		
#ifdef PROV
		cout << "ccdrob " << ccdrob << endl; //correct
		cout << "ccobshee" << ccobshee << endl;
#endif

		
	}
	else {
		int newch = 0;
		int csave = (int)c; //сохранить целую часть с
		int st;
		int w;
		int k; //для цикла нахождения 1й цифры чтобы не повредсть значение с
		//int N = simv;

		for (i = 0; i < simv; i++) {

			for (l = 0; l < 36; l++) {

				if (ch[i] == out[l]) {
#ifdef PROV
					cout << "l " << l << endl;
#endif
					cc = cc + l * pow(a, (simv - i - 1));
				}
			}
		}
#ifdef PROV
		cout << "cc " << cc << endl;
#endif

	}



		//cc - целое
		//ccdrob - дробь

		//z - конечная сс
		//ПЕРЕВОД ИЗ 10й В ЛЮБУЮ

	string alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string cc1, ccdrob1;
	cc1 = to_string((int)cc);
	ccdrob1 = to_string(ccdrob);
	cc1 == cc1 + "A";
	cout << "cc1 " << cc1 << endl;
	cout << "ccdrob1 " << ccdrob1 << endl<<endl;

	string csifra = "";
	string onechast = "";
	do
	{
		csifra = to_string((int)cc % z);
		csifra = alpha[(int)cc % z];
		onechast = csifra + onechast;
		cc = int(cc / z);

	} while (cc != 0);

#ifdef PROV
	cout << "csifra " << csifra << endl;
	cout << "onechast " << onechast << endl << endl; // РАБОТАЕТ!!!
#endif

	csifra = "";
	string twochast = "";
	do
	{
		csifra = to_string(int(ccdrob * z));
		csifra = alpha[(int)(ccdrob * z)];
		twochast = twochast + csifra;
		ccdrob = ccdrob * z - int(ccdrob * z);
	} while (ccdrob - int(ccdrob) != 0);

#ifdef PROV
	cout << "csifra " << csifra << endl;
	cout << "twochast " << twochast << endl << endl;  // РАБОТАЕТ!!!
#endif

	string itog = "";
	itog = onechast + "." + twochast;
	cout << "Переведено в систему СС "<< z << "itog " << itog << endl << endl;

/*

	string from10_to16(string a)
	{
		string c;//chelaya chast
		string chisloc, b, chislo, chislob, part;//drobn chast
		c = "";
		b = "";
		int stc, stb, nol, int_c;
		stb = -1;
		stc = 0;
		double double_b;
		chisloc = "";
		chislob = "";
		part = "";
		nol = 1;
		for (int i = 0; i < a.size(); i++)
		{
			if ((a[i] != ',') && (a[i] != '.'))
			{
				c = c + a[i];
			}
			else
			{
				break;
			}
		}
		int_c = atoi(c.c_str());
		for (int i = 0; i < a.size(); i++)
		{
			if ((a[i] == ',') || (a[i] == '.'))
			{
				for (int j = i + 1; j < a.size(); j++)
					b = b + a[j];
			}
		}
		do
		{
			part = to_string(int_c % 16);
			if (part == "10")
			{
				part = "A";
			}
			if (part == "11")
			{
				part = "B";
			}
			if (part == "12")
			{
				part = "C";
			}
			if (part == "13")
			{
				part = "D";
			}
			if (part == "14")
			{
				part = "E";
			}
			if (part == "15")
			{
				part = "F";
			}
			chisloc = part + chisloc;
			int_c = int(int_c / 16);
		} while (int_c != 0);

		b = "0." + b;
		double_b = atof(b.c_str());
		do
		{
			part = to_string(int(double_b * 16));
			if (part == "10")
			{
				part = "A";
			}
			if (part == "11")
			{
				part = "B";
			}
			if (part == "12")
			{
				part = "C";
			}
			if (part == "13")
			{
				part = "D";
			}
			if (part == "14")
			{
				part = "E";
			}
			if (part == "15")
			{
				part = "F";
			}
			chislob = chislob + part;
			double_b = double_b * 16 - int(double_b * 16);
		} while (double_b - int(double_b) != 0);

		chislo = chisloc + "." + chislob;
		return (chislo);
	}


*/

	/*	//целые
		countdrobey = 0;
		tochka = 0;
		char nt[100];
		sprintf_s(nt, "%lf", cc);//перевод double в char
		int newsimv = strlen(nt);
		for (i = 0; i < newsimv; i++) {
			cout << "nt[i] " << nt[i] << endl;
			if (nt[i] == '.') {
				tochka = i;
			}
		}
#ifdef PROV
		cout << "nt[i] " << nt << endl;
		cout << "newsimv " << newsimv << endl;
		cout << "tochka " << tochka << endl << endl;
#endif
		int first = 0;
		int s = 0;
		for (i = 0; i < tochka; i++) { //перевели число в int из char
			s = pow(10, (tochka - i - 1));
			first = first + s * nt[i];  //не считает корректно
#ifdef PROV
			cout << "nt[i] " << nt[i] << endl;
			cout << "s " << s << endl;
			cout << "tochka - i " << tochka - i << endl;
#endif
		}
#ifdef PROV
		cout << "first " << first << endl;
#endif
		int firstdlyacount = first;
		int count = 0;
		//first - Целая часть
		while (firstdlyacount > 0) { //кол-во цифр
			count++;
			firstdlyacount /= 10;
		}
#ifdef PROV
		cout << "count " << count << endl << endl;
#endif
		char v1[100] = { }; //часть 1  огранизовать вывод с конца
		int chast1 = 0;
		int promeg; //промежуточное
		int promegbukvi;
		for (i = 0; i < count; i++) { //перевод //доделать для букв
			promeg = first % z;


			for (l = 0; l < 36; l++) {
				if (promeg == l) {
					//promegbukvi = out[l];
					v1[i] = out[l];
				}
			}

			chast1 = chast1 + promeg * pow(10, i);
			first = (first - promeg) / z;
		}
#ifdef PROV
		cout << "chast1 " << chast1 << endl;
#endif
		cout << "v1 ";
		for (i = (count - 1); i >= 0; i--) { //вывод правильного! в правильном порядке целой части числа
			cout << v1[i];
		}





		double end = chast1;//перевести в значение больше нуля  (умножить на 10 в степени кол-ва цифр) и делать
		//почти как с целыми (только степени не от 0, а от 1цы. и в правильном для проги порядке)
		
		count = 0;

		string strokadrobi;
		//ccdrob - дробь тип double

		double ccdroabforcount = ccdrob;
		while ((ccdroabforcount / 1) != ccdroabforcount) {
			count++; //сколько цифр
			ccdroabforcount *= 10;
		}
		//stringstream strokadrobi;
	
		
		//strokadrobi = ccdroabforcount;
#ifdef PROV
		cout << "ccdroabforcount " << ccdroabforcount << endl;
		//cout << "strokadrobi " << strokadrobi << endl;
#endif
		//char* itoa(int value, char* str, int base);
		string itoa(int ccdroabforcount, string* str, int z);
		string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int cheloye = 0;
		string drobnoye = "";
		
		



		stringstream ss;
		string str = "";

		//int number = 0;
		//cout << "Vvedite chislo" << endl;
		//cin >> number;

		ss << ccdrob;
		ss >> str;
		//system("cls");
		cout << "Chislo: " << ccdrob << " prevratilos v stroky: " << str<<endl;
		cout << "ccdrob " << ccdrob << endl;

		//drobnoye = to_string(cheloye);
		//string cc1, ccdrob1; инициал-но выше
		//cc1 = to_string(cc);
		string ifra = "";
		string h = "";


	
	
		for (i = 0; i < count; i++) { //обычный перевод как с целыми(на 17.10 целые не готовы) взять у Сеида
			cheloye = ccdrob * z;
			ccdrob = ccdrob * z - cheloye;
			//myStr.ifra(count, cheloye);
			ifra = to_string(cheloye);
			
			h = to_string(out[cheloye]);
			//a.insert(0, 1, 'a'); // вставим 1 СИМВОЛ 'a', в позицию 0
			ifra.insert(i, 1, 'h'); //получаем букву/цифру в нужной сс из h и добавляем в строку. 
			//организовать посимвольное добавление в drobnoye
			cout << "ifra " << ifra << endl;
			drobnoye = drobnoye + alphabet[cheloye];
			i++;
		}
#ifdef PROV
		cout << "alphabet " << alphabet[10] << endl;
		cout << "h " << h << endl;
		printf("%s \n", ifra.c_str());
		//getline(cin, h);
		cout << "drobnoye " << drobnoye << endl;
#endif
		char v2[100] = { }; //часть 2  огранизовать вывод с конца
		if (f != 0) {
			double chast2 = 0;
			cout << endl << endl;
			// перевод дробной части
			newch2 = cc - (int)cc;
			nch = newch2; // отделен  //nch - дробная часть числа
			int y;
			double ogran = (int)newch2;//ограничение
			
#ifdef PROV
			cout << "nch " << nch << endl << endl;
#endif
			double znamen;
			s = 0;
			while (nch != ogran) {//проверить проверку
				s++;//good
				nch = nch * z;
#ifdef PROV
				cout << "nch do " << nch << endl;
#endif
				y = (int)nch;

				for (l = 0; l < 36; l++) {
					if (y == l) {

						v2[i] = out[l];
					}
				}

				nch = nch - y;

				for (l = 0; l < 36; l++) {
					if (y == l) {
						y = out[l];
					}
				}

				znamen = (double)y / pow(10, s);// fine
				chast2 = chast2 + znamen; //fine
				//ogran = y; //потом просто заменить огран в вайл на у

#ifdef PROV
				cout << "znamen " << znamen << endl;
				cout << "nch posle " << nch << endl;
				cout << "y " << y << endl;
				cout << "chast2 " << chast2 << endl << endl;
#endif
			}
			end = chast1 + chast2;

			cout << "v2 ";
			for (i = (count - 1); i >= 0; i--) { //вывод правильного! в правильном порядке целой части числа
				cout << v2[i];
			}
			cout << endl;
		}
		//cout << "v1 v2 ";
		//for (i = (count - 1); i >= 0; i--) { //вывод правильного! в правильном порядке целой части числа
		//	cout << v1[i];
		//}
		//cout << ".";
		//for (i = (count - 1); i >= 0; i--) { //вывод правильного! в правильном порядке целой части числа
		//	cout << v2[i];
		//}
		cout << endl << endl;
		cout << "itоgivoe chislo = " << end << endl << endl; //еще нет */

		system("PAUSE");
		return 0;
	
}