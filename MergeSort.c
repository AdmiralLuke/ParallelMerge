#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>

typedef struct {
    int* a;
    int length;
} IntArray;

typedef struct {
    int thread_id;
    IntArray array;

    int start;
    int end;
    int size;
} p_thread;

int* allocIntArray(int size) {
    return (int *)malloc(sizeof(int) * size);
}

void printArray(IntArray a) {
    int n = a.length;
    for (int i = 0; i < n; i++) {
        printf("%d ", a.a[i]);
    }
    printf("\n");
}

IntArray copyOfRange(IntArray a, int from, int to) {
    int n = to - from;
    // printf("%d %d %d\n", from, to, n);
    IntArray retA = {
        .a = allocIntArray(n),
        .length = n,
    };
    for (int i = 0; i < n; i++) {
        retA.a[i] = a.a[from + i];
    }
    return retA;
}


void merge(IntArray* left, IntArray* right, IntArray* a) {
    int rL = right->length;
    int lL = left->length;
    int aL = a->length;

    int j, k = 0;
    for (int i = 0; i < aL; i++) {
        if (k >= rL || (j < lL && left->a[j] < right->a[k])) {
            a->a[i] = left->a[j];
            j++;
        } else {
            a->a[i] = right->a[k];
            k++;
        }
    }
}

void mergeSort(IntArray* a) {
    if (a->length >= 2) {
        IntArray left = copyOfRange(*a, 0, a->length / 2);
        IntArray right = copyOfRange(*a, a->length / 2, a->length);

        mergeSort(&left);
        mergeSort(&right);

        merge(&left, &right, a);
    }
}



int isSorted(IntArray a) {
    int aL = a.length;
    for (int i = 0; i < aL - 1; i++) {
        if (a.a[i] > a.a[i + 1]) {
            return 0;
        }
    }
    return 1;
}

/*
void parallelMerge(IntArray* a ,int threadCount) {
    if (threadCount < 2) {
        mergeSort(a);
    } else {
        p_thread threads[threadCount];
        int tmpThreadStart = 0;
        for (int i = 0; i < threadCount; i++) {
            if (i == 0) {
                p_thread[i] = {
                    .start = 0,
                    .end = (int)(a->size / thread_count),
                    .size = .end - .start,
                    .array = copyOfRange(a, 0, .end),
                };
                tmpThreadStart = (int)(a->size / threadCount);
            } else if (i != threadCount - 2) {
                p_thread[i] = {
                    .end = 
                }
            }
        }
    }
}

*/

int* generateRandomArray(int size) {
    int* randArray = allocIntArray(size);
    for (int i = 0; i < size; i++) {
        randArray[i] = rand() % (size + 1);
    }
    return randArray;
}


int main() {
    IntArray tmp = {
        .a = generateRandomArray(25000000),
        .length = 25000000,
    };
    printArray(tmp);
    mergeSort(&tmp);
    printArray(tmp);
    printf("%d",isSorted(tmp));
    return 0;
}

