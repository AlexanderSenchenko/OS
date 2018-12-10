#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t mutex;

int threshold;
int nthreads = 8;
int max_active_lvl;

typedef struct
{
	int *v;
	int i;
	int j;
	int lvl;
} Pth_arg;

double wtime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1E-6;
}

void print_vect(int *arr, int n)
{
	printf("Arr: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int *vi, int *vj)
{
	int buf = *vi;
	*vi = *vj;
	*vj = buf;
}

void partition(int *v, int *i, int *j, int low, int high) {
	*i = low;
	*j = high;
	
	int pivot = v[(low + high) / 2];
	
	do {
		while (v[*i] < pivot) (*i)++;
		while (v[*j] > pivot) (*j)--;
		
		if (*i <= *j) {
			swap(&v[*i], &v[*j]);
			(*i)++;
			(*j)--;
		}
	} while (*i <= *j);
}

void quicksort(int *v, int low, int high) {
	int i = 0;
	int j = 0;
	
	partition(v, &i, &j, low, high);
	
	if (low < j)
		quicksort(v, low, j);
	if (i < high)
		quicksort(v, i, high);
}

void *quicksort_parallel(void *arg)
{
	Pth_arg *v_right = (Pth_arg *) arg;

	if (max_active_lvl > v_right->lvl) {

		int i = 0;
		int j = 0;

		pthread_t tid;

		v_right->lvl++;

		partition(v_right->v, &i, &j, v_right->i, v_right->j);

		Pth_arg v_left = { v_right->v, v_right->i, j, v_right->lvl };

		v_right->i = i;
		
		pthread_create(&tid, NULL, quicksort_parallel, &v_left);

		quicksort_parallel(v_right);

		pthread_join(tid, NULL);
	} else {
		quicksort(v_right->v, v_right->i, v_right->j);
	}

	return NULL;
}

int main()
{
	srand(time(NULL));

	#if 1
	double t_stream;
	double t_parallel;

	int n = pow(10, 6);
	int n_max = pow(10, 8);

	for (int j = n; j <= n_max; j *= 10) {

		int *arr = malloc(sizeof(int) * j);
		int *arr_stream = malloc(sizeof(int) * j);
		int *arr_parallel = malloc(sizeof(int) * j);

		for (int i = 0; i < j; i++) {
			arr[i] = rand() % 1000;
			arr_stream[i] = arr[i];
		}
		
		t_stream = wtime();
		quicksort(arr_stream, 0, j - 1);
		t_stream = wtime() - t_stream;

		for (int i = 2; i <= nthreads; i *= 2) {
			max_active_lvl = log2(i);

			for (int i = 0; i < j; i++)
				arr_parallel[i] = arr[i];

			Pth_arg arg = { arr_parallel, 0, j - 1, 0};

			t_parallel = wtime();
			quicksort_parallel(&arg);
			t_parallel = wtime() - t_parallel;

			// printf("Time(threads = %d, n = %d): %.6f sec.\n", i, j, t_parallel);
			// printf("S(threads = %d, n = %d, threshold = %d) = %.6f sec.\n", i, j, threshold, t_stream / t_parallel);
			// printf("%d n=%d threshold=%d %.6f\n", i, j, threshold, t_stream / t_parallel);	
			printf("p=%d n=%d %.6f\n", i, j, t_stream / t_parallel);
		}

		free(arr);
		free(arr_stream);
		free(arr_parallel);
	}
	#endif

	#if 0
	int n = pow(10, 6);
	
	max_active_lvl = log2(8);

	int *arr_stream = malloc(sizeof(int) * n);
	int *arr_parallel = malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		arr_stream[i] = rand() % 1000;
		arr_parallel[i] = arr_stream[i];
	}

	Pth_arg arg = { arr_parallel, 0, n - 1, 0};

	double t_stream = wtime();
	quicksort(arr_stream, 0, n - 1);
	t_stream = wtime() - t_stream;

	double t_parallel = wtime();
	quicksort_parallel(&arg);
	t_parallel = wtime() - t_parallel;

	printf("t(stream) = %.6f\n", t_stream);
	printf("t(parallel) = %.6f\n", t_parallel);
	printf("S = %.6f\n", t_stream / t_parallel);
	#endif

	return 0;
}
