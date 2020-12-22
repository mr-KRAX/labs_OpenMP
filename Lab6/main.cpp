/**
* Lab3 op.1
* \author Alexandr Krasnov (PIN-31)
*/

#include <omp.h>
#include <iomanip>
#include <iostream>
#include <ctime>

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
	double start, end, parallelLockTime, parallelBarrierTime, sequentalTime, parallelRedTime; // time vars
	int N; // Num of elements
	int* A, * B; // Arrays
	N = 100;
	std::cout << setw(10) << "N" << "  "
		<< setw(12) << "LockTime" << "  "
		<< setw(12) << "BarrierTime" << "  "
		<< setw(12) << "RedTime" << "  "
		<< setw(12) << "sequentalTime" << endl;

	while (N != 100000000) {
		N *= 10;
		A = createArray(N);
		B = createArray(N);
		/**
		 * Parallel lock
		 */
		res = 1;
		omp_lock_t lock;
		omp_init_lock(&lock);
		start = omp_get_wtime();
		#pragma omp parallel shared(A, B, res)
		{
		#pragma omp for private(i, tmp)
			for (i = 0; i < N; i++) {
				tmp = A[i] + B[i];
				LOG("c tmp[%d] = %d", i, tmp);
				if (tmp != 0) {
					omp_set_lock(&lock);
					res *= tmp;
					omp_unset_lock(&lock);
			}
			}
		}
		end = omp_get_wtime();
		parallelLockTime = end - start;

		/**
		 * Parallel lock + barrier
		 */
		res = 1;
		start = omp_get_wtime();
#pragma omp parallel shared(A, B, res) private(i, tmp)
		{
			int step = N / omp_get_num_threads();
			int leftRange = omp_get_thread_num() * step;
			int rightRange = leftRange + step;
			rightRange = (N - rightRange >= step) ? rightRange : N;
			//omp_set_lock(&lock);
			//cout << "[" << step << "] " << leftRange << " - " << rightRange << endl;
			//omp_unset_lock(&lock);
			for (i = leftRange; i < rightRange; i++) {
				tmp = A[i] + B[i];
				LOG("c tmp[%d] = %d", i, tmp);
				if (tmp != 0) {
					omp_set_lock(&lock);
					res *= tmp;
					omp_unset_lock(&lock);
				}
			}
#pragma omp barrier
		}
		end = omp_get_wtime();
		parallelBarrierTime = end - start;
		omp_destroy_lock(&lock);

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
		cout << setw(10) << N << "  "
			<< setw(12) << parallelLockTime << "  "
			<< setw(12) << parallelBarrierTime << "  "
			<< setw(12) << parallelRedTime << "  "
			<< setw(12) << sequentalTime << endl;
		delete A;
		delete B;
	}
	return 0;
}


