// 3_lab.cpp

#include <iostream>
#include <stdio.h>
#include <omp.h>
using namespace std;

double quadr(double a, double b, double c) {
	double D = b * b - 4 * a * c;
	return (-b + sqrt(D)) / (2 * a);
}

double Quadr(double a, double b, double c) {
	double _4 = 4;
	double _2 = 2;
	_asm
	{
		fld _4
		fmul a
		fmul c
		fld b
		fmul b
		fsub
		fsqrt
		fsub b
		fdiv _2
		fdiv a
	}
}

double cube(double a, double b, double c, double d) {

}
double Cube(double a, double b, double c, double d) {

}

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "\n-- task 1 --\n\n";	//1
	int a = 10, b = 20, s, S;

	auto t = omp_get_wtime();
	s = a + b;
	t = omp_get_wtime() - t;

	cout << "s = " << s << endl;
	cout << "t = " << t << endl;
	
	t = omp_get_wtime();
	_asm
	{
		mov eax, a
		add eax, b
		mov S, eax
	}
	t = omp_get_wtime() - t;

	cout << "S = " << S << endl;
	cout << "t = " << t << endl;

	cout << "\n-- task 2 --\n\n";	//2
	double p = 3.14, e = 2.71, kk, KK;
	
	t = omp_get_wtime();
	kk = p + e;
	t = omp_get_wtime() - t;

	cout << "kk = " << kk << endl;
	cout << "t = " << t << endl;
	
	t = omp_get_wtime();
	_asm
	{
		fld p
		fadd e
		fstp KK
	}
	t = omp_get_wtime() - t;

	cout << "KK = " << KK << endl;
	cout << "t = " << t << endl;

	cout << "\n-- task 3 --\n\n";	//3
	t = omp_get_wtime();
	auto _quadr = quadr(1, -2, 1);
	t = omp_get_wtime() - t;

	cout << "quadr = " << _quadr << endl;
	cout << "t = " << t << endl;

	t = omp_get_wtime();
	auto _Quadr = Quadr(1, -2, 1);
	t = omp_get_wtime() - t;

	cout << "Quadr= " << _Quadr << endl;
	cout << "t = " << t << endl;

	cout << "\n-- task 4 --\n\n";	//4
	//кубическое уравнение

	system("pause");
	return 0;
}