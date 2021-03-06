#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>

/**
 * @brief Struct to pass the length from an array as an argument
 * 
 */
typedef struct {
    int* a;
    int length;
} IntArray;

/**
 * @brief struct for p_thread operations
 * stores the splitted array parts and the thread_id
 */
typedef struct {
    int thread_id;
    IntArray array;

    int start;
    int end;
    int size;
} p_thread;

/**
 * @brief allocates int array with given size
 * 
 * @param size size of the allocated array
 * @return int* allocated array of given size
 */
int* allocIntArray(int size) {
    return (int *)malloc(sizeof(int) * size);
}

p_thread* allocStructArray(int size) {
    return (p_thread *)malloc(sizeof(p_thread) * size);
}
/*
pthread_t* allocThreadArray(int size) {
    return (pthread_t *)malloc(sizeof(pthread_t) * size);
}
*/

/**
 * @brief testing method to print the content of an array
 * 
 * @param a array (as struct IntArray for the length)
 */
void printArray(IntArray a) {
    int n = a.length;
    for (int i = 0; i < n; i++) {
        printf("%d ", a.a[i]);
    }
    printf("\n");
}

/**
 * @brief copies the content of an array to a new array 
 * 
 * @param a input array
 * @param from position in array where to start
 * @param to position in array where to stop
 * @return IntArray array with copied content from input array
 */
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

/**
 * @brief runs normal MergeSort when given 1 Thread
 * splits array in n-thread parts
 * @param a input array
 * @param threadCount number of threads
 */
/*
void parallelMerge(IntArray* a ,int threadCount) {
    if (threadCount < 2) {
        mergeSort(a);
    } else {
        p_thread* threads = (p_thread *)malloc(sizeof(p_thread) * threadCount);
        pthread_t* th = (pthread_t *)malloc(sizeof(pthread_t) * threadCount);
	printf("1\n");
        int tmpThreadStart = 0;
        for (int i = 0; i < threadCount; i++) {
            if (i == 0) {
                p_thread tmpStruct = {
                    .start = 0,
                    .end = (int)(a->length / threadCount),
                    .size = (int)(a->length / threadCount),
                    .array = copyOfRange(*a, 0, (int)(a->length / threadCount)),
                };
                threads[i] = tmpStruct;
                tmpThreadStart = (int)(a->length / threadCount);
            } else if (i != threadCount - 2) {
                p_thread tmpStruct = {
                    .start = tmpThreadStart + 1,
                    .end = (tmpThreadStart + 1) + (int)(a->length / threadCount),
                    .size =(int)(a->length / threadCount),
                    .array = copyOfRange(*a, tmpThreadStart + 1, (tmpThreadStart + 1) + (int)(a->length / threadCount)),
                };
                threads[i] = tmpStruct; 
                tmpThreadStart += 1 + (int)(a->length / threadCount);
            } else {
                p_thread tmpStruct = {
                    .start = tmpThreadStart + 1,
                    .end = (tmpThreadStart + 1) + (int)(a->length / threadCount) + (a->length%threadCount),
                    .size = (int)(a->length / threadCount) + (a->length%threadCount),
                    .array = copyOfRange(*a, tmpThreadStart + 1, (tmpThreadStart + 1) + (int)(a->length / threadCount) + (a->length%threadCount)), 
                };
                threads[i] = tmpStruct;
            }
            int rc;
            rc = pthread_create(&th[i], NULL, mergeSort, &threads[i].array);
            if (rc) {
                printf("Fehler beim Erstellen der Threads");
                exit(-1);
            }
        }
	printf("Im Here\n");
        for (int i = 0; i < threadCount; i += 2) {
            pthread_join(th[i], NULL);
            pthread_join(th[i + 1], NULL);
	    printf("banane%d\n",i);
            merge(&threads[i].array, &threads[i+1].array, a);
        }
	printf("drei\n");
        free(th);
        free(threads);
    }
}
*/

/**
 * @brief generates array with random numbers in range of 0 to given size
 * 
 * @param size size of array and range of numbers
 * @return int* random array with size-elements
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
        .a = generateRandomArray(25),
        .length = 25,
    };
    printArray(tmp);
    mergeSort(&tmp);
    printArray(tmp);
    printf("%d\n",isSorted(tmp));
    return 0;
}

