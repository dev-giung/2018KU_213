#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> //더 정밀한 시간 측정을 위해 사용
#define SIZE 100
#define RADIX 10
#define DIGIT 3

typedef struct student {
	char name[100];
	int student_number;
	int score;
} student;

typedef struct QNode {
	int data;
	struct QNode *link;
}QNode;

typedef struct {
	QNode *front, *rear;
}LQueueType;

student c[SIZE];

double selectionSort(student a[], int size);
double insertionSort(student a[], int size);
double bubbleSort(student a[], int size);
double shellSort(student a[], int size);
double mergeSort(student a[], int m, int n);
void mergeSort2(student a[], int m, int n);
double quickSort(student a[], int begin, int end);
void quickSort2(student a[], int begin, int last);
double radixSort(student a[], int size);
student *copy(student b[]);
int partition(student b[], int begin, int last);
void intervalSort(student b[], int begin, int last, int interval);
void merge(student b[], int m, int middle, int n);
void enQueue(LQueueType *LQ, int item);
int deQueue(LQueueType *LQ);
int isEmpty(LQueueType *LQ);
LQueueType *createLinkedQueue();
void printSortResult(student b[], int i);

int main()
{
	FILE *fp = NULL;
	student students[SIZE];
	double sum[7] = { 0, };
	double temp = 0.0;
	int i, j; // index variables

	if ((fp = fopen("Student_info.txt", "r")) == NULL)
	{
		printf("Error file not open! \n");
		exit(0);
	}
	
	srand((int)time(NULL));
	
	for (j = 0; j < 100; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			fscanf(fp, "%d %[^\n]s", &students[i].student_number, students[i].name);
			students[i].score = rand() % 101;			
		}
		printf("%d번째\n", j + 1);
		
		temp = selectionSort(students, SIZE);
		sum[0] += temp;
		printf("Selection sort: %lf(ms)\t", temp);
		
		temp = insertionSort(students, SIZE);
		sum[1] += temp;
		printf("Insertion sort: %lf(ms)\t", temp);
		
		temp = bubbleSort(students, SIZE);
		sum[2] += temp;
		printf("Bubble sort: %lf(ms)\t", temp);
		
		temp = shellSort(students, SIZE);
		sum[3] += temp;
		printf("Shell sort: %lf(ms)\t", temp);
		
		temp = mergeSort(students, 0, SIZE - 1);
		sum[4] += temp;
		printf("Merge sort: %lf(ms)\t", temp);
		
		temp = quickSort(students, 0, SIZE - 1);
		sum[5] += temp;
		printf("Quick sort: %lf(ms)\t", temp);
		
		temp = radixSort(students, SIZE);
		sum[6] += temp;
		printf("Radix sort: %lf(ms)\t\n", temp);
	}
	
	printf("\n\n정렬 전:\n");
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", students[i].score);
	}
	printf("\n\n");
	for (i = 0; i < 7; i++) {
		printSortResult(students, i);
	}
	

	printf("\n\n\n\n");
	printf("Selection sort, Insertion sort, Bubble sort, Shell sort, Merge sort, Quick sort, Radix sort 100회 avg time: 단위(ms)\n");
	for (i = 0; i < 7; i++)
	{
		printf("%lf(ms)\t", sum[i]/100.0);
	}
	printf("\n");

	fclose(fp);

	return 0;
}

//정렬을 여러번 하기 때문에 매번 같은 구조체를 만들어서 정렬을 해줘야함
student* copy(student b[])
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{		
		c[i].score = b[i].score;
		c[i].student_number = b[i].student_number;
		for (j = 0; j < SIZE; j++)
		{
			if (b[i].name[j] == "\n") break;
			c[i].name[j] = b[i].name[j];
		}		
	}
	return c;
}

double selectionSort(student b[], int size)
{
	LARGE_INTEGER freq, start, end;
	double time;
	int max, temp;
	student *a = copy(b);	

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	int i,j;
	
	for (i = 0; i < size-1 ; i++)
	{
		max = i;
		for (j = i + 1; j < size; j++)
		{
			if (a[j].score > a[max].score) max = j;
		}
		temp = a[i].score;
		a[i].score = a[max].score;
		a[max].score = temp;
	}
	QueryPerformanceCounter(&end);

	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
	
	return time;
}

double insertionSort(student b[], int size)
{
	int i, j, temp;
	LARGE_INTEGER freq, start, end;
	double time;
	student *a = copy(b);

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	for (i = 1; i < size; i++)
	{
		temp = a[i].score;
		j = i;
		while ((j > 0) && (a[j - 1].score < temp))
		{
			a[j].score = a[j - 1].score;
			j = j - 1;
		}
		a[j].score = temp;
	}

	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
	
	return time;
}

double bubbleSort(student b[], int size)
{
	LARGE_INTEGER freq, start, end;
	double time;
	int temp;		
	student *a = copy(b);
	
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	
	int i, j;
	
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size-i-1; j++)
		{
			if (a[j].score < a[j + 1].score)
			{
				temp = a[j].score;
				a[j].score = a[j + 1].score;
				a[j + 1].score = temp;
			}
		}
	}
	
	QueryPerformanceCounter(&end);
	
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;

	return time;
}

double shellSort(student b[], int size)
{
	int i, interval;
	LARGE_INTEGER freq, start, end;
	double time;	
	student *a = copy(b);
	
	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	interval = size / 2;
	while (interval >= 1)
	{
		for (i = 0;i < interval;i++) intervalSort(a, i, size - 1, interval);
		interval = interval / 2;
	}

	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;

	return time;
}

double mergeSort(student b[], int m, int n)
{
	int middle;
	LARGE_INTEGER freq, start, end;
	double time;
	student *a = copy(b);

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	if (m < n)
	{
		middle = (m + n) / 2;
		mergeSort2(a, m, middle);
		mergeSort2(a, middle + 1, n);
		merge(a, m, middle, n);
	}

	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
	
	return time;
}

void mergeSort2(student a[], int m, int n)
{
	int middle;
	
	if (m < n)
	{
		middle = (m + n) / 2;
		mergeSort2(a, m, middle);
		mergeSort2(a, middle + 1, n);
		merge(a, m, middle, n);
	}
}

double quickSort(student b[], int begin, int last)
{
	LARGE_INTEGER freq, start, end;
	double time;
	student *a = copy(b);
	int p;
	
	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	
	if (begin < last)
	{
		p = partition(a, begin, last);
		quickSort2(a, begin, p - 1);
		quickSort2(a, p + 1, last);
	}
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;	
	
	return time;
}

void quickSort2(student a[], int begin, int last)
{
	int p;
	
	if (begin < last)
	{
		p = partition(a, begin, last);
		quickSort2(a, begin, p - 1);
		quickSort2(a, p + 1, last);
	}	
}

double radixSort(student b[], int size)
{
	int i, bucket, d, factor = 1;
	LARGE_INTEGER freq, start, end;
	double time;
	student *a = copy(b);
	LQueueType *Q[RADIX];
	for (bucket = 0; bucket < RADIX; bucket++)
		Q[bucket] = createLinkedQueue();

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&start);
	for (d = 0;d < DIGIT;d++) {
		for (i = 0; i < size ;i++)
			enQueue(Q[(a[i].score / factor) % 10], a[i].score);
		for (bucket = RADIX-1, i = 0 ;bucket >= 0;bucket--)
			while (!isEmpty(Q[bucket])) a[i++].score = deQueue(Q[bucket]);
		factor = factor * 10;
	}

	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
	
	return time;
}
//quick sort에 쓰이는 함수
int partition(student a[], int begin, int last)
{
	int pivot, L, R, t;
	int temp;
	L = begin;
	R = last;	
	pivot = (int)((begin + last) / 2.0);

	while (L < R)
	{
		while ((a[L].score > a[pivot].score) && (L < R)) L++;
		while ((a[R].score <= a[pivot].score) && (L < R)) R--;
		if(L<R) 
		{
			temp = a[L].score;
			a[L].score = a[R].score;
			a[R].score = temp;

			if (L == pivot)
				pivot = R;
		}
	}

	temp = a[pivot].score;
	a[pivot].score = a[R].score;
	a[R].score = temp;
	return R;
}
//shell sort에 사용되는 함수
void intervalSort(student a[], int begin, int last, int interval)
{
	int i, j;
	int item;
	for (i = begin + interval; i <= last; i = i + interval)
	{
		item = a[i].score;
		for (j = i - interval; j >= begin && item > a[j].score; j = j - interval)
			a[j + interval].score = a[j].score;
		a[j + interval].score = item;
	}
}
//merge sort에 사용되는 함수
void merge(student a[], int m, int middle, int n)
{
	int sorted[SIZE];
	int i, j, k, t;
	i = m;
	j = middle + 1;
	k = m;

	while (i <= middle && j <= n)
	{
		if (a[i].score >= a[j].score)
		{
			sorted[k] = a[i].score;
			i++;
		}
		else
		{
			sorted[k] = a[j].score;
			j++;
		}
		k++;
	}

	if (i > middle) for (t = j;t <= n;t++, k++) sorted[k] = a[t].score;
	else for (t = i;t <= middle;t++, k++) sorted[k] = a[t].score;

	for (t = m;t <= n;t++) a[t].score = sorted[t];

}

//radix sort를 하기 위한 큐 관련 함수
LQueueType *createLinkedQueue() {
	LQueueType *LQ;
	LQ = (LQueueType *)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

int isEmpty(LQueueType *LQ) {
	if (LQ->front == NULL) return 1;
	else return 0;
}

void enQueue(LQueueType *LQ, int item)
{
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

int deQueue(LQueueType *LQ) {
	QNode *old = LQ->front;
	int item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}

//정렬된 배열을 출력하는 함수
void printSortResult(student b[], int caseNum)
{
	int i;
	student *a = copy(b);
	
	switch (caseNum) {
		case 0:
			selectionSort(a, SIZE);
			printf("Selection Sort\n");
			break;
		case 1:
			insertionSort(a, SIZE);
			printf("Insertion Sort\n");
			break;
		case 2:
			bubbleSort(a, SIZE);
			printf("Bubble Sort\n");
			break;
		case 3:
			shellSort(a, SIZE);
			printf("Shell Sort\n");
			break;
		case 4:
			mergeSort(a, 0, SIZE-1);
			printf("Merge Sort\n");
			break;
		case 5:
			quickSort(a, 0, SIZE-1);
			printf("Quick Sort\n");
			break;
		case 6:
			radixSort(a, SIZE);
			printf("Radix Sort\n");
			break;
	}		
	
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", a[i].score);
	}
	printf("\n\n");
}
