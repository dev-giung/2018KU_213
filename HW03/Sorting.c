#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

/*
	Selection Sort
*/
void selectionSort(int *list, int n) {
	
	int i, j, minIndex;
	
	for( i = 0; i < n - 1; i++ ) {
		minIndex = i;
		for( j = i + 1; j < n; j++ ) {
			if( list[j] < list[minIndex] ) {
				minIndex = j;
			}
		}
		swap( &list[minIndex], &list[i] );
	}
}

/*
	Insertion Sort
*/
void insertionSort(int *list, int n) {
	
	int i, j, key;
	
	for( i = 1; i < n; i++ ) {
		key = list[i];
		for( j = i - 1; j >= 0 && list[j] > key; j-- ) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}

/*
	Bubble Sort
*/
void bubbleSort(int *list, int n) {
	
	int i, j;
	for( i = n - 1; i > 0; i-- ) {
		for( j = 0; j < i; j++ ) {
			if( list[j] > list[j + 1] ) {
				swap( &list[j], &list[j + 1] );
			}
		}
	}
}

/*
	Shell Sort
*/
void shellSort(int *list, int n) {
	
	int i, gap;
	for( gap = n / 2; gap > 0; gap = gap / 2 ) {
		if( gap % 2 == 0 ) {
			gap++;
		}
		for( i = 0; i < gap; i++ ) {
			inc_insertionSort( list, i, n - 1, gap );
		}
	}
}

void inc_insertionSort(int *list, int first, int last, int gap) {
	
	int i, j, key;
	for( i = first + gap; i <= last; i = i + gap ) {
		key = list[i];
		for( j = i - gap; j >= first && key < list[j]; j = j - gap ) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

/*
	Merge Sort
*/
void mergeSort(int *list, int n) {
	
	int left, mid, right;
	left = 0; right = n - 1;
	
	mergeSortRec(list, left, right);
}

void mergeSortRec(int *list, int left, int right) {
	
	int mid;
	if( left < right ) {
		mid = (left + right) / 2;
		mergeSortRec(list, left, mid);
		mergeSortRec(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

void merge(int *list, int left, int mid, int right) {
	
	int sorted[100];
	
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	
	while( i <= mid && j <= right ) {
		if( list[i] <= list[j] ) {
			sorted[k++] = list[i++];
		} else {
			sorted[k++] = list[j++];
		}
	}
	
	if( i > mid ) {
		for( l = j; l <= right; l++ ) {
			sorted[k++] = list[l];
		}
	} else {
		for( l = i; l <= mid; l++ ) {
			sorted[k++] = list[l];
		}
	}
	
	for( l = left; l <= right; l++ ) {
		list[l] = sorted[l];
	}
}

/*
	Quick Sort
*/
void quickSort(int *list, int n) {
	
	int left = 0;
	int right = n - 1;
	
	quickSortRec(list, left, right);
}

void quickSortRec(int *list, int left, int right) {
	
	if( left < right ) {
		int q = partition(list, left, right);
		quickSortRec(list, left, q - 1);
		quickSortRec(list, q + 1, right);
	}
}

int partition(int *list, int left, int right) {
	
	int pivot, low, high;
	
	low = left;
	high = right + 1;
	pivot = list[left];
	
	do {
		do {
			low++;
		} while( low <= right && list[low] < pivot );
		do {
			high--;
		} while( high >= left && list[high] > pivot);
		if( low < high ) {
			swap(&list[low], &list[high] );
		}
	} while( low < high );
	
	swap(&list[left], &list[high]);
	return high;
}

/*
	Print
*/
void printArray(int *list, int n) {
	
	int i;
	
	for( i = 0; i < n; i++ ) {
		printf("%d ", list[i]);
	}
	printf("\n");
}

int main() {
	
	int mylist[5] = {3, 1, 9, 2, 4};
	printArray(mylist, 5);
	
	//selectionSort(mylist, 5);
	//insertionSort(mylist, 5);
	//shellSort(mylist, 5);
	//mergeSort(mylist, 5);
	quickSort(mylist, 5);
	printArray(mylist, 5);
	
	return 0;
}
