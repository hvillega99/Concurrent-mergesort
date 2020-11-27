#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//cantidad de hilos
#define BOUND 4 

//funciones de ordenamiento
//---------------------------------
void mergeSort(int l, int r);
void merge(int l, int m, int r);
void* thread_mergeSort(void* arg);
//---------------------------------

//funciones para manipular la cadena de entrada
//---------------------------------
void printArr(int arr[], int size);
int* makeArr(char* str, int count);
int countNumbers(char* str);
//---------------------------------

//---------------------------------
int* arr;
int arr_size;
int part = 0; 
//---------------------------------

//---------------------------------
int main(int argc, char** argv){
    
	int arr_size = countNumbers(argv[1]);
	if(arr_size == 0){
		fprintf(stderr,"Entrada incorrecta\nUso: %s x1,x2,...,xn\n", argv[0]);
		return 1;
	}

	arr = makeArr(argv[1], arr_size);
	printf("Entrada:   ");
	printArr(arr,arr_size);

	//---------------------------------
	pthread_t threads[BOUND]; 

	//creando hilos 
	for (int i = 0; i < BOUND; i++) 
		pthread_create(&threads[i], NULL, thread_mergeSort, (void*)NULL); 

	//joining 
	for (int i = 0; i < 4; i++) 
		pthread_join(threads[i], NULL); 

	//mezclando las últimas 4 partes
	merge(0, (arr_size / 2 - 1) / 2, arr_size / 2 - 1); 
	merge(arr_size / 2, arr_size/2 + (arr_size-1-arr_size/2)/2, arr_size - 1); 
	merge(0, (arr_size - 1)/2, arr_size - 1);
	//---------------------------------

	printf("Resultado: ");
	printArr(arr,arr_size);

	free(arr);
    return 0;
}
//---------------------------------


//---------------------------------
void merge(int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];


	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	
	i = 0; 
	j = 0; 
	k = l; 
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

	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(int l, int r)
{
	if (l < r) {
		
		int m = l + (r - l) / 2;

		mergeSort(l, m);
		mergeSort(m + 1, r);

		merge(l, m, r);
	}
}

void* thread_mergeSort(void* arg) { 

	int thread_part = part++; 

	int start = thread_part * (arr_size / BOUND); 
	int end = (thread_part + 1) * (arr_size / BOUND) - 1; 

	int mid = start + (end - start) / 2; 
	if (start < end) { 
		mergeSort(start, mid); 
		mergeSort(mid + 1, end); 
		merge(start, mid, end); 
	} 
}

//---------------------------------


//---------------------------------
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
//---------------------------------