#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	double x1, x2, y1, y2, r1, r2, x3, y3;
	cout << "Введите x1 " << endl;
	cin >> x1;
	cout << "Введите y1 " << endl;
	cin >> y1;
	cout << "Введите r1 " << endl;
	cin >> r1;
	cout << "Введите x2 " << endl;
	cin >> x2;
	cout << "Введите y2 " << endl;
	cin >> y2;
	cout << "Введите r2 " << endl;
	cin >> r2;
	cout << "Введите x3 " << endl;
	cin >> x3;
	cout << "Введите y3 " << endl;
	cin >> y3;

	double delx, dely, delc, R, rpok;
	delx = abs(x1 - x2);
	dely = abs(y1 - y2);
	delc = sqrt(delx * delx + dely * dely);
	R = abs(r1) + abs(r2);
	rpok = abs(r1 - r2);
	double sector = 0, sec1, sec2, f1, f2;

	if (delc > R) {
		cout << "нет пересечения" << endl;
	}
	else if (delc == R) {
		cout << "соприкосновение" << endl;
	}

	else if ((rpok < r1)||(rpok < r2)) { //случай когда одна внутри другой - меньше считать чтобы.
		if (r1 <= r2) {
			sector = 3.1415926 * r1 * r1;
		}
		else {
			sector = 3.1415926 * r2 * r2;
		}
	}else{
		f1 = 2 * acos((r1 * r1 - r2 * r2 - delc * delc) / (2 * r1 * delc));
		f2 = 2 * acos((r2 * r2 - r1 * r1 - delc * delc) / (2 * r2 * delc));
		sec1 = (r1 * r1 * (f1 - sin(f1))) / 2;
		sec2 = (r2 * r2 * (f2 - sin(f2))) / 2;

		sector = sec1 + sec2;
	}

	cout << "площадь пересечения = " << sector << endl;

	double rastx1, rastx2, rasty1, rasty2, s1, s2;
	rastx1 = abs(x1 - x3);
	rastx2 = abs(x2 - x3);
	rasty1 = abs(y1 - y3);
	rasty2 = abs(y2 - y3);
	s1 = sqrt(rastx1 * rastx1 + rasty1 * rasty1);
	s2 = sqrt(rastx2 * rastx2 + rasty2 * rasty2);
	if ((s1 <= r1) && (s2 <= r2)) {
		cout << "точка {" << x3 << ";" << y3 << "} принадлежит области пересечения" << endl;
	}
	else {
		cout << "точка {"<< x3 <<";" << y3 <<"} не принадлежит области пересечения" << endl;
	}


	system("pause");
	return 0;
}