#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* mergeSort(int start, int end, int arr[]);
void* merge(int start, int mid, int end, int arr[]);
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


void* mergeSort(int start,int end, int arr[]){

    if(start<end){
        int mid = start + (end - start) / 2;

		/*pthread_t tid1, tid2, tid3;
		pthread_create(&tid1, NULL, mergeSort(start,mid), NULL); //left
		pthread_join(tid1,NULL);
		pthread_create(&tid2, NULL, mergeSort(mid+1,end), NULL); //right
		pthread_join(tid2,NULL);
		pthread_create(&tid3, NULL, merge(start, mid, end), NULL);*/

        mergeSort(start,mid, arr); //izquierda
        mergeSort(mid+1,end, arr); //derecha
        merge(start, mid, end, arr); //mezclar

    }

}


void* merge(int start, int mid, int end, int arr[]){
	int i, j, k;
	int n1 = mid - start + 1;
	int n2 = end - start;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[start + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = start; // Initial index of merged subarray
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
	printf("[ ");

	for(int* p=arr; p < arr+size; p++){
		printf("%d ",*p);
	}

	printf("]\n");
}

