#include <stdio.h>

void InsertSort(int arr[], int len) {
    int idx = 1;
    for (int i = 1; i < len; i++) {
        for (int j = 0; j <= i; j++) {
            if (i > j && arr[i] < arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}