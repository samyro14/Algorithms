#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void hepify(int* arr, int n, int root){
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != root){
        swap(&arr[root], &arr[largest]);
        hepify(arr, n, largest);
    }
}

void heapSort(int* arr, int n){
    for(int i = n / 2 - 1; i >= 0; --i){
        hepify(arr, n, i);
    }
    for(int i = n - 1; i >= 0; --i){
        swap(&arr[0], &arr[i]);
        hepify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vectorul nesortat:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Vectorul sortat (crescător):\n");
    printArray(arr, n);

    return 0;
}