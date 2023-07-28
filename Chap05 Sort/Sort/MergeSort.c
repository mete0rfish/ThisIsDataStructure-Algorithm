void Merge(int Arr[], int StartIdx, int MiddleIdx, int EndIdx) {
    int LeftIdx = StartIdx;
    int RightIdx = MiddleIdx + 1;
    int ResIdx = 0;

    int* ResArr = (int*)malloc(sizeof(int) * (EndIdx - StartIdx + 1));

    while (LeftIdx <= MiddleIdx && RightIdx <= EndIdx) {
        if (Arr[LeftIdx] < Arr[RightIdx]) {
            ResArr[ResIdx++] = Arr[LeftIdx];
            LeftIdx++;
        }
        else {
            ResArr[ResIdx++] = Arr[RightIdx];
            RightIdx++;
        }
    }

    while (LeftIdx <= MiddleIdx) {
        ResArr[ResIdx++] = Arr[LeftIdx++];
    }
    while (RightIdx <= EndIdx) {
        ResArr[ResIdx++] = Arr[RightIdx++];
    }

    ResIdx = 0;
    for (int i = StartIdx; i <= EndIdx; i++) {
        Arr[i] = ResArr[ResIdx++];
    }
    free(ResArr);
}

void MergeSort(int Arr[], int StartIdx, int EndIdx) {
    int MiddleIdx = 0;

    if (EndIdx - StartIdx < 1)   return;


    MiddleIdx = (EndIdx + StartIdx) / 2;

    MergeSort(Arr, StartIdx, MiddleIdx);
    MergeSort(Arr, MiddleIdx + 1, EndIdx);

    Merge(Arr, StartIdx, MiddleIdx, EndIdx);
}
