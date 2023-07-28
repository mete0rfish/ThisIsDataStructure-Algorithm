#include <stdio.h>
#include <stdlib.h>
#include "QuickSort.c"



void Print(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
    }
}

int main() {
    int arr[6] = { 1,5,4,2,3,6 };
    //BubbleSort(arr,6);
    //InsertSort(arr,6);
    //MergeSort(arr, 0, 6-1);
    QuickSort(arr, 0, 5);
    Print(arr, 6);

    return 0;
}