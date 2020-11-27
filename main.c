#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void mergeSort(int l, int r, int arr[]);
void merge(int l, int m, int r, int arr[]);
void printArr(int arr[], int size);
int* makeArr(char* str, int count);
int countNumbers(char* str);

int* list;

int main(int argc, char** argv){
    
	int size = countNumbers(argv[1]);
	if(size == 0){
		fprintf(stderr,"Entrada no permitida\n");
		return 1;
	}

	list = makeArr(argv[1], size);
	printf("Entrada:   ");
	printArr(list,size);

	mergeSort(0,size-1, list);
	printf("Resultado: ");
	printArr(list,size);

	free(list);
    return 0;
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int l, int m, int r, int arr[])
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int l, int r, int arr[])
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(l, m, arr);
		mergeSort(m + 1, r, arr);

		merge(l, m, r, arr);
	}
}


int countNumbers(char* str){
	if(str == NULL){
		return 0;
	}else{
		int size = strlen(str);
		int count = 0;

		for(int i=0; i<size; i++){
			if(str[i] == ','){
				count ++;
			}
		}

		count ++;

		return count;
	}
}

int* makeArr(char* str, int count){
	
	int size = strlen(str);
	char aux_arr[8] = {0};

	int j=0, k=0;

	int* arr = (int*)malloc(count * sizeof(int));

	int i=0;
	while(i<size){
		if(str[i] != ','){
			aux_arr[j] = str[i];
			j++;
		}
		if((str[i] == ',') || i == size-1){
			arr[k] = atoi(aux_arr);
			k++;
			j=0;
			memset(aux_arr,0,8);
		}
		i++;
	}

	return arr;
}



void printArr(int arr[], int size){
	printf("[");

	for(int* p=arr; p < arr+size; p++){
		printf("%d",*p);

		if(p != arr+(size-1)){
			printf(",");
		}

	}

	printf("]\n");
}

