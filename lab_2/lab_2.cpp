// 2_lab.cpp

#include <iostream>
#include <stdio.h>
#include <omp.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
#ifndef _OPENMP	//OMP off
	printf("omp not supported!\n");
#else	//OMP on
	cout << "number of processors available : " << omp_get_num_procs() << endl;
	cout << "number of threads : " << omp_get_max_threads() << endl;


	cout << "\n-- task 1 --\n\n";	//1
	std::cout << "enter num a: ";
	float a, b;
	cin >> a;
	std::cout << "enter num b: ";
	cin >> b;
	int len = 10000000;
	auto t = omp_get_wtime();;
	for (int i = 0; i < len; i++)
		auto c = a * b;
	t = omp_get_wtime() - t;
	std::cout << "time (single): " << t << std::endl;
	t = omp_get_wtime();
	len /= omp_get_max_threads();
#pragma omp parallel
	{
		for (int i = 0; i < len; i++)
			auto c = a * b;
	}
	t = omp_get_wtime() - t;
	std::cout << "time (parallel): " << t << std::endl;


	cout << "\n-- task 2 --\n\n";	//2
	t = omp_get_wtime();
#pragma omp parallel
	{
		//space
	}
	t = omp_get_wtime() - t;
	cout << "time: " << t << std::endl;


	cout << "\n-- task 3 --\n\n";	//3
	omp_set_num_threads(3);
	cout << "number of threads : " << omp_get_max_threads() << endl;
	cout << "omp single\n";
#pragma omp parallel 
	{
		cout << "start (" << omp_get_thread_num() << ")\n";
#pragma omp single
		{ cout << "one thread (" << omp_get_thread_num() << ")\n"; }
		cout << "finish (" << omp_get_thread_num() << ")\n";
	}
	cout << "omp single nowait\n";
#pragma omp parallel 
	{
		cout << "start (" << omp_get_thread_num() << ")\n";
#pragma omp single nowait
		{ cout << "one thread (" << omp_get_thread_num() << ")\n"; }
		cout << "finish (" << omp_get_thread_num() << ")\n";
	}


	cout << "\n-- task 4 --\n\n";	//4
	cout << "number of threads : " << omp_get_max_threads() << endl;
#pragma omp parallel
	{
		cout << "(" << omp_get_thread_num() << ") beginning\n";
#pragma omp master
		{
			cout << "(" << omp_get_thread_num() << ") MASTER\n";
			cout << "(" << omp_get_thread_num() << ") MASTER\n";
		}
		cout << "(" << omp_get_thread_num() << ") middle\n";
#pragma omp master
		{
			cout << "(" << omp_get_thread_num() << ") MASTER\n";
			cout << "(" << omp_get_thread_num() << ") MASTER\n";
		}
		cout << "(" << omp_get_thread_num() << ") end\n";
	}


	cout << "\n-- task 5 --\n\n";	//5
	omp_set_num_threads(2);
	cout << "number of threads : " << omp_get_max_threads() << endl;
	int n = 10;
	cout << "n = " << n << endl;
#pragma omp parallel private(n)
	{
		int n = 10;
		cout << "(" << omp_get_thread_num() << ") parallel region n = " << n << endl;
		n = omp_get_thread_num();
		cout << "(" << omp_get_thread_num() << ") parallel region n = " << n << endl;
	}
	cout << "n = " << n << endl;


	cout << "\n-- task 6 --\n\n";	//6
	cout << "number of threads : " << omp_get_max_threads() << endl;
	int m[5] = { 0 };
	for (int i = 0; i < 5; i++)
		cout << m[i] << " ";
	cout << endl;
#pragma omp parallel shared(m)
	{
		for (int i = 0; i < 5; i++)
			if (i == omp_get_thread_num())
				m[i] = 1;
	}
	for (int i = 0; i < 5; i++)
		cout << m[i] << " ";
	cout << endl;


	cout << "\n-- task 7 --\n\n";	//7
	int thr_num = 8;
	int sum = 0;
	omp_set_num_threads(thr_num);
	cout << "number of threads : " << omp_get_max_threads() << endl;
	cout << "sum = " << sum << endl;
#pragma omp parallel reduction(+:sum)
	{
		sum++;
		cout << "(" << omp_get_thread_num() << ") parallel region sum = " << sum << endl;
	}
	cout << "sum = " << sum << endl;


	cout << "\n-- task 8 --\n\n";	//8
	omp_set_num_threads(4);
	cout << "number of threads : " << omp_get_max_threads() << endl;
	sum = 0;
	cout << "sum = " << sum << endl;
#pragma omp parallel reduction(+:sum)
	{
		sum = omp_get_thread_num();
		cout << "(" << omp_get_thread_num() << ") parallel region sum = " << sum << endl;
	}
	cout << "sum = " << sum << endl;
#endif
	system("pause");
	return 0;
}