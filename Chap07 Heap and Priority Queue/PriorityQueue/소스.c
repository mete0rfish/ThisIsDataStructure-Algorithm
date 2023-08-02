#include "PriorityQueue.h"

void PrintNode(PQNode* node) {
	printf("작업명: %s (우선순위:%d)\n", node->Data, node->Priority);
}


int main() {
	PriorityQueue* pq = createPq(3);
	PQNode popped;

	PQNode Nodes[7] = {
		{34, (void*)"코딩" },
		{12, (void*)"고객미팅" },
		{87, (void*)"커피타기" },
		{45, (void*)"문서작성" },
		{35, (void*)"디버깅" },
		{66, (void*)"이닦기" },
	};

	enqueuePq(pq, Nodes[0]);
	enqueuePq(pq, Nodes[1]);
	enqueuePq(pq, Nodes[2]);
	enqueuePq(pq, Nodes[3]);
	enqueuePq(pq, Nodes[4]);
	enqueuePq(pq, Nodes[5]);

	printf("큐에 남아 있는 작업의 수 : %d\n", pq->UserdSize);

	while (!isEmpty(pq)) {
		dequeuePq(pq, &popped);
		PrintNode(&popped);
	}
	return 0;
}
