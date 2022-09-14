// 1_lab.cpp

#include <iostream>
#include <stdio.h>
#include <omp.h>

int main() {
	setlocale(LC_ALL, "Russian");
#ifndef _OPENMP
	printf("omp not supported!\n");
#else
	std::cout << "number of processors available : " << omp_get_num_procs() << std::endl;
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl;

	std::cout << "\n--task 3--\n\n";	//3
#pragma omp parallel
	{
		std::cout << "sequential region 1\n";
	}
#pragma omp parallel num_threads(3)
	{
		std::cout << "\tsequential region 2\n";
	}
	omp_set_num_threads(4);
#pragma omp parallel
	{
		std::cout << "\t\tsequential region 3\n";
	}

	std::cout << "\n--task 1 --\n\n";	//1
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl;
	omp_set_num_threads(5);
	std::cout << "set num threads 5" << std::endl;
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl << std::endl;

	std::cout << "sequential area 1" << std::endl;
#pragma omp parallel
	{
		std::cout << "sequential area\n";
	}
	std::cout << "sequential area 2" << std::endl;

	std::cout << "\n--task 2--\n\n";	//2
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl;
#pragma omp parallel
	{
		std::cout << "my number: " << omp_get_thread_num() << std::endl;
	}

	std::cout << "\n--task 4--\n\n";	//4
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl;
	omp_set_num_threads(128);
	std::cout << "set num threads 128" << std::endl;
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl << std::endl;
	omp_set_dynamic(0);
	std::cout << "(dynamic mode off) number of threads : " << omp_get_max_threads() << std::endl << std::endl;
#pragma omp parallel
	{
		std::cout << "my number: " << omp_get_thread_num() << std::endl;
	}
	omp_set_dynamic(1);
	std::cout << "(dynamic mode on ) number of threads : " << omp_get_max_threads() << std::endl << std::endl;
#pragma omp parallel
	{
		std::cout << "my number: " << omp_get_thread_num() << std::endl;
	}

	std::cout << "\n--task 5--\n\n";	//5
	std::cout << "enter argument: ";
	std::string s;
	std::cin >> s;
	std::string par("parallel");
	std::string ser("serial");
	bool flag = false;
	if (s != par && s != ser)
		std::cout << "invalid argument\n";
	else
		if (s == par)
		{
			flag = true;
			std::cout << "parallel mod on\n";
		}
		else
			std::cout << "serial mod on\n";

	std::cout << "\nnumber of threads : " << omp_get_max_threads() << std::endl;
	omp_set_num_threads(5);
	std::cout << "set num threads 5" << std::endl;
	std::cout << "number of threads : " << omp_get_max_threads() << std::endl << std::endl;
	int len = 10000000;
	auto t = omp_get_wtime();;

	if (!flag) {
		for (int i = 0; i < len; i++)
			auto a = sin(i);
		t = omp_get_wtime() - t;
		std::cout << "time: " << t << std::endl;
	}
	else {
		len /= omp_get_max_threads();
#pragma omp parallel
		{
			for (int i = 0; i < len; i++)
				auto a = sin(i);
		}
		t = omp_get_wtime() - t;
		std::cout << "time: " << t << std::endl;
	}

#endif
	system("pause");
	return 0;
}
