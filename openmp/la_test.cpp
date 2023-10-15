#include <climits>
#include <iostream>
#include <random>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "la.h"


// #define RANDTOP INT_MAX
#define RANDTOP 10

int main(int argc, char *argv[])
{
	int n;
	double *A;
	double *B;
	double *C;
	double *a;
	double *b;
	double *c;
	double result;
	int resultloc;

	omp_set_num_threads(2);	
	if(argc == 1){
		auto start{std::chrono::steady_clock::now()};
    	auto end{std::chrono::steady_clock::now()};

		n = 100;
	
		A =(double *) malloc(sizeof(double)*n*n);
		B =(double *) malloc(sizeof(double)*n*n);
		C = (double *) malloc(sizeof(double)*n*n);

		for(int i=0; i < n; i++)
			for(int j=0; j < n; j++)
			{
				A[loc(i,j,n)] = i + j;
				B[loc(i,j,n)] = (i == j) ? 1 : 0;
				C[loc(i,j,n)] = 0;
			}

		start = std::chrono::steady_clock::now();
		matmul(A, B, C, n);
		end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds{end - start};

		std::cout << "matmul runs in " << elapsed_seconds.count() << "s\n";








	} else if(argc == 2) {
		n = 5000;
		A = (double*) malloc(sizeof(double)*n*n);
		B = (double*) malloc(sizeof(double)*n*n);

	
		auto start{std::chrono::steady_clock::now()};
    	auto end{std::chrono::steady_clock::now()};

		for(int i=0; i < n; i++)
		{
			for(int j=0; j < n; j++)
			{
				A[loc(i,j,n)] = B[loc(i,j,n)] = i;
			}
		}

		// test here
		start = std::chrono::steady_clock::now();
		prefix(A, B, n);

		end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds{end - start};

		std::cout << "prefix runs in " << elapsed_seconds.count() << "s\n";


	} else {
		std::cout << "This only takes the n dimension as an argument" << std::endl;
		return 1;
	}

	return 0;
}