#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

#define maxsize 2000
#define chunk 128

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// ===========================================QUICK SORT==========================================
int partition(int* arr, int st, int dr){
    int indPivot = st;
    for(int i = st; i < dr; ++i){
        if(arr[i] < arr[dr]){
            swap(&arr[i], &arr[indPivot]);
            indPivot++;
        }
    }
    swap(&arr[indPivot], &arr[dr]);
    return indPivot;
}
void quicksort(int* arr, int st, int dr){
    if(st < dr){
        int poz = partition(arr, st, dr);
        quicksort(arr, st, poz - 1);
        quicksort(arr, poz + 1, dr);
    }
}


// ===========================================MERGE SORT==========================================

void mergeSort(int* arr, int st, int dr){
    if(st < dr){
        int mid = (st + dr) / 2;
        mergeSort(arr, st, mid);
        mergeSort(arr, mid + 1, dr);
        //fac interschimbarea
        int* temp = (int*)(malloc((dr - st + 1) * sizeof(int)));
        int i = st, j = mid + 1, k = 0;
        while(i <= mid && j <= dr){
            if(arr[i] < arr[j]){
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while(i <= mid){
            temp[k++] = arr[i++];
        }
        while(j <= dr){
            temp[k++] = arr[j++];
        }
        for(i = st, k = 0; i <= dr; i++, k++){
            arr[i] = temp[k];
        }
        free(temp);
    }
}
// ===========================================INSERTION SORT==========================================
void insertionSort(int* arr, int n){
    for(int i = 1; i < n; ++i){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j --;
        }
        arr[j + 1] = key;
    }
}
// ===========================================SELECTION SORT==========================================
void selectionSort(int* arr, int n){
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(arr[j] < arr[i]){
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

// ===========================================HEAP SORT==========================================
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



// ===========================================RADIX SORT==========================================

void radixSort(int* arr, int n){
    int max = arr[0];
    for(int i = 1; i < n; ++i){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    for(int exp = 1; max / exp > 0; exp *= 10){
        int* output = (int*)(malloc(n * sizeof(int)));
        int count[10] = {0};
        for(int i = 0; i < n; ++i){
            count[(arr[i] / exp) % 10]++;
        }
        for(int i = 1; i < 10; ++i){
            count[i] += count[i - 1];
        }
        for(int i = n - 1; i >= 0; --i){
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for(int i = 0; i < n; ++i){
            arr[i] = output[i];
        }
        free(output);
    }
}


// ==========================================Counting SORT==========================================
void countingSort1(int* arr, int n){
    int max = arr[0];
    for(int i = 1; i < n; ++i){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int* count = (int*)(calloc(max + 1, sizeof(int)));
    for(int i = 0; i < n; ++i){
        count[arr[i]]++;
    }
    int index = 0;
    for(int i = 0; i <= max; ++i){
        while(count[i] > 0){
            arr[index++] = i;
            count[i]--;
        }
    }
    free(count);
}

void countingSort2(int arr[], int n) {
    // 1. Găsim valoarea maximă din vector
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    // 2. Alocăm vectorul de frecvență (count). 
    // Dimensiunea este max + 1 (pentru a include și valoarea 'max')
    // Folosim calloc pentru a inițializa automat cu 0.
    int* count = (int*)calloc(max + 1, sizeof(int));
    
    // Alocăm vectorul de ieșire
    int* output = (int*)malloc(n * sizeof(int));

    if (count == NULL || output == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return;
    }

    // 3. Numărăm frecvența fiecărui element
    // count[x] va reține de câte ori apare x în vector
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 4. Calculăm pozițiile cumulative (Prefix Sum)
    // Acum, count[i] va spune "câte elemente sunt mai mici sau egale cu i"
    // Asta ne dă direct indexul final în vectorul sortat.
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // 5. Construim vectorul sortat
    // Parcurgem invers vectorul original pentru a păstra STABILITATEA
    for (int i = n - 1; i >= 0; i--) {
        int val = arr[i];
        int pozitie = count[val] - 1; // -1 deoarece indecșii încep de la 0
        
        output[pozitie] = val;
        count[val]--; // Decrementăm pentru cazul în care numărul apare de mai multe ori
    }

    // 6. Copiem rezultatul înapoi
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // Eliberăm memoria
    free(count);
    free(output);
}


// ==========================================SHELL SORT==========================================
void shellSort1(int* arr, int n){
    for(int gap = n / 2; gap > 0; gap /= 2){
        for(int i = gap; i < n; ++i){
            int temp = arr[i];
            int j;
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSort2(int arr[], int n) {
    // Începem cu un interval mare (gap), apoi îl reducem la jumătate la fiecare pas.
    // Când gap devine 1, algoritmul se comportă ca un Insertion Sort standard.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        
        // Parcurgem elementele de la 'gap' până la final.
        // Această buclă realizează o "sortare prin inserție cu pasul gap".
        for (int i = gap; i < n; i++) {
            
            // Salvăm elementul curent pe care vrem să îl inserăm
            // la poziția corectă în sub-șirul definit de gap.
            int temp = arr[i];
            
            int j;
            
            // Deplasăm elementele din sub-șirul "gap-sorted" care sunt
            // mai mari decât 'temp' spre dreapta, cu distanța 'gap'.
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            // Punem elementul salvat la locul său corect
            arr[j] = temp;
        }
    }
}
int main(void){
    int n;

    scanf("%d", &n);
    int* arr = (int*)(malloc(n * sizeof(int)));
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    // quicksort(arr, 0, n - 1);
    //mergeSort(arr, 0, n - 1);
    //insertionSort(arr, n);
    //selectionSort(arr, n);
    heapSort(arr, n);
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);


    return 0;
}
/*


*/



