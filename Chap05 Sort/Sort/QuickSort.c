#include <stdio.h>
#include <stdlib.h>

int Partition(int Arr[], int Left, int Right) {
    int i = Left;
    int Pivot = Arr[Right];

    Left++;

    for (int j = Left; j <= Right - 1; j++) {

        if (Arr[j] <= Pivot) {
            i++;
            int tmp = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = tmp;
        }

    }

    int tmp = Arr[i + 1];
    Arr[i + 1] = Arr[Right];
    Arr[Right] = tmp;

    return (i + 1);

}

void QuickSort(int arr[], int Left, int Right) {
    if (Left < Right) {
        int p = Partition(arr, Left, Right);

        QuickSort(arr, Left, p - 1);
        QuickSort(arr, p + 1, Right);
    }
}
