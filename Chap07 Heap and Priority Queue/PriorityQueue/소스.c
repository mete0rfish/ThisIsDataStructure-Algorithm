#include "PriorityQueue.h"

void PrintNode(PQNode* node) {
	printf("�۾���: %s (�켱����:%d)\n", node->Data, node->Priority);
}


int main() {
	PriorityQueue* pq = createPq(3);
	PQNode popped;

	PQNode Nodes[7] = {
		{34, (void*)"�ڵ�" },
		{12, (void*)"������" },
		{87, (void*)"Ŀ��Ÿ��" },
		{45, (void*)"�����ۼ�" },
		{35, (void*)"�����" },
		{66, (void*)"�̴۱�" },
	};

	enqueuePq(pq, Nodes[0]);
	enqueuePq(pq, Nodes[1]);
	enqueuePq(pq, Nodes[2]);
	enqueuePq(pq, Nodes[3]);
	enqueuePq(pq, Nodes[4]);
	enqueuePq(pq, Nodes[5]);

	printf("ť�� ���� �ִ� �۾��� �� : %d\n", pq->UserdSize);

	while (!isEmpty(pq)) {
		dequeuePq(pq, &popped);
		PrintNode(&popped);
	}
	return 0;
}
