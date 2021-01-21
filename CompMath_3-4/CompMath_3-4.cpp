#include <iostream>
#include "locale.h"
#include <math.h>
#include <iomanip>

using namespace std;
const float eps = 0.001; // Точность (эпсилон)
const float x = 1, y = -1; // Начальное приближение
const int rr = 10000; // Округление
//float x0, y0, x1, y1;

float computing_methodX(float x0, float y0) {

	float mas[2][2] = {
		{1 / (2 * sqrt(x0)), 1},
		{4 / sqrt(x0), 2 * y0}
	};

	float det = mas[0][0] * mas[1][1] - mas[0][1] * mas[1][0];

	float obrMas[2][2] = {
		{ mas[1][1] / det, -1 * mas[0][1] / det },
		{ -1 * mas[1][0] / det, mas[0][0] / det }
	};
	float funcMas[2] = {
		sqrt(x0) + y0 - 4,
		8 * sqrt(x0) + pow(y0, 2) - 20
	};

	float resultMas[2] = {
		{ funcMas[0] * obrMas[0][0] + funcMas[1] * obrMas[0][1] },
		{ funcMas[0] * obrMas[1][0] + funcMas[1] * obrMas[1][1] }
	};

	return resultMas[0];
}

float computing_methodY(float x0, float y0) {

	float mas[2][2] = {
		{1 / (2 * sqrt(x0)), 1},
		{4 / sqrt(x0), 2 * y0}
	};

	float det = mas[0][0] * mas[1][1] - mas[0][1] * mas[1][0];

	float obrMas[2][2] = {
		{ mas[1][1] / det, -1 * mas[0][1] / det },
		{ -1 * mas[1][0] / det, mas[0][0] / det }
	};
	float funcMas[2] = {
		sqrt(x0) + y0 - 4,
		8 * sqrt(x0) + pow(y0, 2) - 20
	};

	float resultMas[2] = {
		{ funcMas[0] * obrMas[0][0] + funcMas[1] * obrMas[0][1] },
		{ funcMas[0] * obrMas[1][0] + funcMas[1] * obrMas[1][1] }
	};

	return resultMas[1];
}

void method_simple_implications() // Метод простых итераций
{
	int k = 0;
	float x0 = x, y0 = y, x1 = x, y1 = y; // x0 = x(k), x1 = x(k+1)
	float modx, mody; // y0 = y(k), y1 = y(k+1)
	do // modx: |x1 - x0|, mody: |y1 - y0|
	{
		x0 = x1, y0 = y1;
		x1 = x0 - 0.4 * (sqrt(x0) + y0 - 4) - 0.2 * (8 * sqrt(x0) + pow(y0, 2) - 20);
		y1 = y0 - 0.8 * (sqrt(x0) + y0 - 4) + 0.1 * (8 * sqrt(x0) + pow(y0, 2) - 20);
		/*x1 = - 4.0 *sqrt(x0) - pow(y0, 2) + 4.0 * y0 + 4.0;
		y1 = 0.25 * pow(y0, 2) - 2.0 * y0 + 3.0;*/
		modx = fabs(x1 - x0);
		mody = fabs(y1 - y0);
		cout << "|" << setw(4) << k << setw(4) << "|" << setw(8) << round(x0 * rr) / rr <<
			setw(5) << "|" << setw(10) << round(x1 * rr) / rr << setw(5) << "|" <<
			setw(14) << round(modx * rr) / rr << setw(8) << "|" << setw(9) << round(y0 * rr) / rr <<
			setw(4) << "|" << setw(9) << round(y1 * rr) / rr << setw(4) << "|" << setw(11)
			<< round(mody * rr) / rr << setw(7) << "|" << endl;
		k++;
	} while ((modx > eps) || (mody > eps));
}
void method_Newton() // Метод Ньютона
{
	int k = 0;
	float x0 = x, y0 = y, x1 = x, y1 = y; // x0 = x(k), x1 = x(k+1)
	float modx, mody; // y0 = y(k), y1 = y(k+1)

	do // modx: |x1 - x0|, mody: |y1 - y0|
	{
		x0 = x1, y0 = y1;
		x1 = x0 - computing_methodX(x0, y0);
		y1 = y0 - computing_methodY(x0, y0);

		modx = fabs(x1 - x0);
		mody = fabs(y1 - y0);
		cout << "|" << setw(4) << k << setw(4) << "|" << setw(8) << round(x0 * rr) / rr <<
			setw(5) << "|" << setw(10) << round(x1 * rr) / rr << setw(5) << "|" <<
			setw(14) << round(modx * rr) / rr << setw(8) << "|" << setw(9) << round(y0 * rr) / rr
			<< setw(4) << "|" << setw(9) << round(y1 * rr) / rr << setw(4) << "|" << setw(11)
			<< round(mody * rr) / rr << setw(7) << "|" << endl;
		k++;
	} while (((modx > eps) || (mody > eps)) && k <= 100);
}


void show_table()
{
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << "|   k   |   X(k)     |  X(k + 1)    |  |(X(k+1) - X(k))|  |    Y(k)    |  Y(k+1)    |  |Y(k+1) - Y(k)| |\n";
	cout << "-------------------------------------------------------------------------------------------------------\n";
}
void func()
{
	int n;
	while (true)
	{
		cout << "Если Вы хотите произвести поиск корней на отрезке: " << endl;
		cout << "По Методу Простых Итераций - нажмите 1" << endl;
		cout << "По Методу Ньютона - нажмите 2" << endl;
		cout << "Введите команду: "; cin >> n;
		switch (n)
		{
		case 1:
			cout << "\nМетод простых итераций" << endl;
			show_table();
			method_simple_implications();
			cout << "\nПроцесс поиска корня на отрезке прошел успешно !" << endl;
			break;
		case 2:
			cout << "\nМетод Ньютона" << endl;
			show_table();
			method_Newton();
			cout << "\nПроцесс поиска корня на отрезке прошел успешно !" << endl;
			break;
		default:
			cout << "Ошибка ввода !";
			break;
		}
		cout << "\n";
	}
}
int main()
{
	setlocale(0, "");
	cout << "Лабораторная работа по Вычислительной математике No3-4\n" << endl;
	cout << "Выполнили студенты группы 4310 Мулюков Роберт и Кутдусов Ильшат\n"
		<< endl;
	cout << "Вариант No 4\nСистема нелинейных уравнений:" << endl;
	cout << "sqrt(x) + y - 4 = 0\n8 * sqrt(x) + y^2 - 20 = 0\nНачальное приближение: (1, -1)\n" << endl;
	func();
	system("pause");
	return 0;
}