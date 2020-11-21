/**
* Lab3 op.1
* \author Alexandr Krasnov (PIN-31)
*/

#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

bool logIsOn = true;
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
			arr[i] = rand() % 100 -50 ;
		}
	}
	return arr;
}

int main() {
	logIsOn = false;
	srand(1);

	unsigned long long res = 1; // Result var
	int i, tmp; // Private vars
	double start, end, parallelRedTime, parallelCritTime, sequentalTime; // time vars
	int N; // Num of elements
	int* A, * B; // Arrays
	//cout << "Enter N: ";
	//cin >> N;

	//A = createArray(N);
	//B = createArray(N);

	N = 100;
	cout << "N\t\tCritical\tReduction\tSequenal" << endl;

	while (N != 100000000) {
		N *= 10;
		A = createArray(N);
		B = createArray(N);
		/**
		 * Parallel critical
		 */
		res = 1;
		start = omp_get_wtime();
		#pragma omp parallel shared(A, B, res)
		{
		#pragma omp for private(i, tmp)
			for (i = 0; i < N; i++) {
				tmp = A[i] + B[i];
				LOG("c tmp[%d] = %d", i, tmp);
				if (tmp != 0) {
					#pragma omp atomic
					res *= tmp;
			}
			}
		}
		end = omp_get_wtime();
		parallelCritTime = end - start;

		/**
		 * Parallel reduction
		 */
		res = 1;
		start = omp_get_wtime();
		#pragma omp parallel shared(A, B)
		{
		#pragma omp for private(i, tmp) reduction(*: res)
			for (i = 0; i < N; i++) {
				tmp = A[i] + B[i];
				LOG("r tmp[%d] = %d", i, tmp);
				if (tmp)
					res *= tmp;
			}
		}
		end = omp_get_wtime();
		parallelRedTime = end - start;

		/**
		 * Sequental
		 */
		res = 1;
		start = omp_get_wtime();
		for (i = 0; i < N; i++) {
			tmp = A[i] + B[i];
			LOG("s tmp[%d] = %d", i, tmp);
			if (tmp != 0)
				res *= tmp;
		}
		end = omp_get_wtime();
		sequentalTime = end - start;

		/**
		 * Results
		 */
		cout << N << "\t\t"
			<< parallelCritTime << "\t"
			<< parallelRedTime << "\t"
			<< sequentalTime << endl;
		delete A;
		delete B;
	}



	return 0;
}


