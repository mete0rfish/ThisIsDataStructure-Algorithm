#include "Heap.h"

Heap* HEAP_Create(int InitialSize) {
	Heap* NewHeap = (Heap*)malloc(sizeof(Heap));
	NewHeap->Capacity = InitialSize;
	NewHeap->UsedSize = 0;
	NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * NewHeap->Capacity);

	printf("size : %d\n", sizeof(HeapNode));

	return NewHeap;
}
void HEAP_Destroy(Heap* H) {
	free(H->Nodes);
	free(H);
}
void HEAP_Insert(Heap* H, ElementType NewData) {
	int CurPos = H->UsedSize;
	int ParentPos = HEAP_GetParent(CurPos);

	if (H->UsedSize == H->Capacity) {
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}

	H->Nodes[CurPos].Data = NewData;

	// 만약 집어 넣은 값이 부모보다 작으면, 부모와 교환
	while (CurPos > 0
		&& H->Nodes[CurPos].Data < H->Nodes[ParentPos].Data) {
		HEAP_SwapNodes(H, CurPos, ParentPos);

		CurPos = ParentPos;
		ParentPos = HEAP_GetParent(CurPos);
	}

	H->UsedSize++;
 }

/*
1. Root(최솟값)를 지우고, 가장 깊은 곳에 있는 요소를 Root로 가져옴. 
2. Root의 왼쪽 자식과 오른쪽 자식 중 가장 작은 값과 교환.
3. 자식이 없거나 자식보다 작으면 종료.
*/
void HEAP_DeleteMin(Heap* H, HeapNode* Root) {
	int ParentPos = 0;
	int LeftPos = 0;
	int RightPos = 0;

	// Root에 최솟값을 저장 및 초기화
	memcpy(Root, &H->Nodes[0], sizeof(HeapNode));
	memset(&H->Nodes[0], 0, sizeof(HeapNode));

	H->UsedSize--;
	// 힙의 첫번째 요소에 마지막 요소 복사
	HEAP_SwapNodes(H, 0, H->UsedSize);

	LeftPos = HEAP_GetLeftChild(0);
	RightPos = LeftPos + 1;

	while (1) {
		int SelectedChild = 0;

		// 범위 넘어가면 종료
		if (LeftPos >= H->UsedSize)
			break;

		// 왼쪽 자식만 있을경우
		if (RightPos >= H->UsedSize)
			SelectedChild = LeftPos;
		// 자식이 둘다 있을 경우, 둘 중 작은 요소를 선택
		else {
			if (H->Nodes[LeftPos].Data > H->Nodes[RightPos].Data)
				SelectedChild = RightPos;
			else
				SelectedChild = LeftPos;
		}


		// 교환
		if (H->Nodes[SelectedChild].Data < H->Nodes[RightPos].Data) {
			HEAP_SwapNodes(H, ParentPos, SelectedChild);
			ParentPos = SelectedChild;
		}
		// 미성립시, 종료
		else
			break;

		LeftPos = HEAP_GetLeftChild(ParentPos);
		RightPos = LeftPos + 1;
	}

	if (H->UsedSize < (H->Capacity / 2)) {
		H->Capacity /= 2;
		H->Nodes =
			(HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
	}
}

int HEAP_GetParent(int Index) {
	return (int)((Index - 1) / 2);
}
int HEAP_GetLeftChild(int Index) {
	return (2 * Index) + 1;
}

void HEAP_SwapNodes(Heap* H, int Index1, int Index2) {
	int CopySize = sizeof(HeapNode);
	HeapNode* Temp = (HeapNode*)malloc(CopySize);

	memcpy(Temp, &H->Nodes[Index1], CopySize);
	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
	memcpy(&H->Nodes[Index2], Temp, CopySize);

	free(Temp);
}
void HEAP_PrintNodes(Heap* H) {
	int i = 0;
	for (i = 0; i < H->UsedSize; i++) {
		printf("%d ", H->Nodes[i].Data);
	}
	printf("\n");
}