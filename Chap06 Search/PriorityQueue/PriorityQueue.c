#include "PriorityQueue.h"

PriorityQueue* PQ_Create(int InitialSize) {
	PriorityQueue* NewPQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	NewPQ->Capacity = InitialSize;
	NewPQ->UsedSize = 0;
	NewPQ->Nodes = (PQNode*)malloc(sizeof(PQNode) * NewPQ->Capacity);

	return NewPQ;
}
void PQ_Destroy(PriorityQueue* PQ) {
	free(PQ->Nodes);
	free(PQ);
}
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewData) {
	int CurPos = PQ->UsedSize;
	int ParentPos = HEAP_GetParent(CurPos);

	if (PQ->UsedSize == PQ->Capacity) {
		PQ->Capacity *= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}

	PQ->Nodes[CurPos].Data = NewData;

	// 만약 집어 넣은 값이 부모보다 작으면, 부모와 교환
	while (CurPos > 0
		&& PQ->Nodes[CurPos].Data < PQ->Nodes[ParentPos].Data) {
		HEAP_SwapNodes(PQ, CurPos, ParentPos);

		CurPos = ParentPos;
		ParentPos = HEAP_GetParent(CurPos);
	}

	PQ->UsedSize++;
 }

/*
1. Root(최솟값)를 지우고, 가장 깊은 곳에 있는 요소를 Root로 가져옴. 
2. Root의 왼쪽 자식과 오른쪽 자식 중 가장 작은 값과 교환.
3. 자식이 없거나 자식보다 작으면 종료.
*/
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root) {
	int ParentPos = 0;
	int LeftPos = 0;
	int RightPos = 0;

	// Root에 최솟값을 저장 및 초기화
	memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
	memset(&PQ->Nodes[0], 0, sizeof(PQNode));

	PQ->UsedSize--;
	// 힙의 첫번째 요소에 마지막 요소 복사
	PQ_SwapNodes(PQ, 0, PQ->UsedSize);

	LeftPos = PQ_GetLeftChild(0);
	RightPos = LeftPos + 1;

	while (1) {
		int SelectedChild = 0;

		// 범위 넘어가면 종료
		if (LeftPos >= PQ->UsedSize)
			break;

		// 왼쪽 자식만 있을경우
		if (RightPos >= PQ->UsedSize)
			SelectedChild = LeftPos;
		// 자식이 둘다 있을 경우, 둘 중 작은 요소를 선택
		else {
			if (PQ->Nodes[LeftPos].Data > PQ->Nodes[RightPos].Data)
				SelectedChild = RightPos;
			else
				SelectedChild = LeftPos;
		}


		// 교환
		if (PQ->Nodes[SelectedChild].Data < PQ->Nodes[RightPos].Data) {
			PQ_SwapNodes(PQ, ParentPos, SelectedChild);
			ParentPos = SelectedChild;
		}
		// 미성립시, 종료
		else
			break;

		LeftPos = PQ_GetLeftChild(ParentPos);
		RightPos = LeftPos + 1;
	}

	if (PQ->UsedSize < (PQ->Capacity / 2)) {
		PQ->Capacity /= 2;
		PQ->Nodes =
			(PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
}

int PQ_GetParent(int Index) {
	return (int)((Index - 1) / 2);
}
int PQ_GetLeftChild(int Index) {
	return (2 * Index) + 1;
}

void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2) {
	int CopySize = sizeof(PQNode);
	PQNode* Temp = (PQNode*)malloc(CopySize);

	memcpy(Temp, &PQ->Nodes[Index1], CopySize);
	memcpy(&PQ->Nodes[Index1], &PQ->Nodes[Index2], CopySize);
	memcpy(&PQ->Nodes[Index2], Temp, CopySize);

	free(Temp);
}
void PQ_PrintNodes(PriorityQueue* PQ) {
	int i = 0;
	for (i = 0; i < PQ->UsedSize; i++) {
		printf("%d ", PQ->Nodes[i].Data);
	}
	printf("\n");
}

int PQ_IsEmpty(PriorityQueue* PQ) {
	return (PQ->UsedSize == 0);
}