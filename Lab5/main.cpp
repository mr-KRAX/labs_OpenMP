/**
* Lab3 op.1
* \author Alexandr Krasnov (PIN-31)
*/

#include <omp.h>
#include <iomanip>
#include <iostream>
#include <ctime>

using namespace std;

bool logIsOn;
#define LOG(msg, ...) do{\
  if (logIsOn) {\
    printf(msg, __VA_ARGS__);\
    printf("\n");\
  }\
} while (0)

int* createArray(int numOfElems) {
	int* arr = new int[numOfElems];
	if (arr != nullptr) {
		for (int i = 0; i < numOfElems; i++) {
			arr[i] = rand() % 100 - 50;
		}
	}
	return arr;
}

int main() {
	logIsOn = false;
	srand(1);

	unsigned long long tmp_res = 1, res = 1; // Result var
	int tmp; // Private vars
	double start, end, parallelSection2, parallelSection4, parallelSection8; // time vars
	int N; // Num of elements
	int* A, * B; // Arrays

	N = 100;
	std::cout << setw(10) << "N" << "  "
		<< setw(12) << "Section2" << "  "
		<< setw(12) << "Section4" << "  "
		<< setw(12) << "Section8" << endl;

	while (N != 100000000) {
		N *= 10;
		A = createArray(N);
		B = createArray(N);
		/**
		 * Parallel sections 1/2
		 */
		res = 1;
		start = omp_get_wtime();
#pragma omp parallel shared(A,B)		
		{
#pragma	omp	sections private(tmp, tmp_res) reduction(*: res)
			{
#pragma omp section
				{
					tmp_res = 1;
					for (int i = 0; i < N / 2 * 1; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 2 * 1); i < N; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
			}
		}
		end = omp_get_wtime();
		parallelSection2 = end - start;

		/**
		 * Parallel sections 1/4
		 */
		res = 1;
		start = omp_get_wtime();
#pragma omp parallel shared(A,B)
		{
#pragma omp sections 	 private(tmp, tmp_res) reduction(*: res)
			{
#pragma omp section 
				{
					tmp_res = 1;
					for (int i = 0; i < N / 4 * 1; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section 
				{
					tmp_res = 1;
					for (int i = N - (N / 4 * 1); i < N / 4 * 2; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section 
				{
					tmp_res = 1;
					for (int i = N - (N / 4 * 2); i < N / 4 * 3; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section 
				{
					tmp_res = 1;
					for (int i = N - (N / 4 * 3); i < N; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
			}
		}
		end = omp_get_wtime();
		parallelSection4 = end - start;

		/**
		 * Parallel sections 1/4
		 */
		res = 1;
		start = omp_get_wtime();
#pragma omp parallel shared(A,B)
		{
#pragma omp sections  private(tmp, tmp_res) reduction(*: res)
			{
#pragma omp section
				{
					tmp_res = 1;
					for (int i = 0; i < N / 8 * 1; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 1); i < N / 8 * 2; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 2); i < N / 8 * 3; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 3); i < (N / 8 * 4); i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 4); i < (N / 8 * 5); i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 5); i < N / 8 * 6; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 6); i < N / 8 * 7; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}
#pragma omp section 
				{
					tmp_res = 1;
					for (int i = N - (N / 8 * 7); i < N; i++) {
						tmp = A[i] + B[i];
						LOG("c tmp[%d] = %d", i, tmp);
						if (tmp != 0)
							tmp_res *= tmp;
					}
					res *= tmp_res;
				}

			}
		}
		end = omp_get_wtime();
		parallelSection8 = end - start;

		/**
		 * Results
		 */
		cout << setw(10) << N << "  "
			<< setw(12) << parallelSection2 << "  "
			<< setw(12) << parallelSection4 << "  "
			<< setw(12) << parallelSection8 << endl;
		delete A;
		delete B;
	}
	return 0;
}


