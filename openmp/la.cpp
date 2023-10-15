#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <omp.h>
#include "la.h"

const int bsize = BLOCK;
const int minParaVector = MINVEC;
const int minParaMatrix = MINMATRIX;
int size;

//Print a n x n matrix
void printMatrix(double *a, int n)
{
	for(int i = 0; i < n ; i++)
	{
		for(int j = 0; j < n; j++)
			printf("%f\t",a[loc(i,j,n)]);
		printf("\n");
	}		
}	

//Print a n long vector
void printVector(double *a, int n)
{
	printf("(");
	for(int i = 0; i < n; i++)
		printf("%f ",a[i]);
	printf(")\n");
}


// Add vector a to b and store result in c vectors are arrays of length n
void add(double *a, double *b, double* c, int n)
{
	if(omp_get_max_threads() == 1 || n < minParaVector )
	{
		for(int i = 0; i < n; i++)
			c[i] = a[i] + b[i];
	}
	else
	{
		#pragma omp parallel for
		for(int i = 0; i < n; i++)
			c[i] = a[i] + b[i];
	}
}

// Multiply matrices A and B and store result in C. doublehe matrices are n x n
void matmul(double *A, double *B, double *C, int n)
{
	#pragma omp parallel for
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[loc(i,j,n)] = 0.0;
	
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			double tmp = B[loc(i,j,n)];
			B[loc(i,j,n)] = B[loc(j,i,n)];
			B[loc(j,i,n)] = tmp;
		}
	}

	#pragma omp parallel for
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				C[loc(i,j,n)]+= A[loc(i,k,n)] * B[loc(j,k,n)];
				
}


// Sum the elements of vector a into b. Vector a is n length.
void sum(double *a, double &b, int n)
{
	double total = 0;
	
	//Sequential
	if(omp_get_max_threads() == 1 || n < minParaVector )
	{
		for(int i = 0; i < n; i++)
		{
			total += a[i];
		}
	}
	else
	{
		#pragma omp parallel for reduction(+:total)
		for(int i = 0; i < n; i++)
		{
			total += a[i];
		}
	}
	b = total;
}

// Puts the prefix sum of vector a into vector b. the vectors are length n
void prefix(double *a, double *b, int n)
{
		// for(int i = 0; i < n; i++)
		// {
		// 	if(i == 0)
		// 		b[i] = a[i];
		// 	else
		// 		b[i] = b[i-1] + a[i];
		// }

	int num_threads = omp_get_num_threads();
	#pragma omp parallel
	{
		for (int i = omp_get_thread_num()*n/num_threads; i < (omp_get_thread_num()+1)*n/num_threads; i++) {
			if (i == omp_get_thread_num()*n/num_threads) {
				b[i] = a[i];
			} else {
				b[i] = b[i-1] + a[i];
			}
		}
	}
}