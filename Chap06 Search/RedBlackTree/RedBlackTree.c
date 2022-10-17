#include "RedBlackTree.h"
#include <string.h>

extern RBTNode* Nil;

RBTNode* RBT_CreateNode(ElementType NewData)
{
    RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));
    NewNode->Parent = NULL;
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;
    NewNode->Color = BLACK;

    return NewNode;
}

void RBT_DestroyNode(RBTNode* Node)
{
    free(Node);
}

void RBT_DestroyTree(RBTNode* Tree)
{
    if (Tree->Right != Nil)
        RBT_DestroyTree(Tree->Right);

    if (Tree->Left != Nil)
        RBT_DestroyTree(Tree->Left);

    Tree->Left = Nil;
    Tree->Right = Nil;

    RBT_DestroyNode(Tree);
}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
    if (Tree == Nil)
        return NULL;

    if (Tree->Data > Target)
        return RBT_SearchNode(Tree->Left, Target);
    else if (Tree->Data < Target)
        return RBT_SearchNode(Tree->Right, Target);
    else
        return Tree;
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
    if (Tree == Nil)
        return Nil;

    if (Tree->Left == Nil)
        return Tree;
    else
        return RBT_SearchMinNode(Tree->Left);
}

void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{
    RBT_InsertNodeHelper(Tree, NewNode);

    NewNode->Color = RED;
    NewNode->Left = Nil;
    NewNode->Right = Nil;

    RBT_RebuildAfterInsert(Tree, NewNode);
}

void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{
    if ((*Tree) == NULL)
        (*Tree) = NewNode;

    // 기존 노드 < 새로운 노드
    // 기존 노드의 오른쪽이 닐일때 추가
    if ((*Tree)->Data < NewNode->Data) 
    {
        if ((*Tree)->Right == Nil)
        {
            (*Tree)->Right = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);

    }
    // 기존 노드 > 새로운 노드
    // 기존 노드의 왼쪽이 닐일때 추가
    else if ((*Tree)->Data > NewNode->Data)
    {
        if ((*Tree)->Left == Nil)
        {
            (*Tree)->Left = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
    }
}

/*
1. LeftChild을 불러와서 부모Left에 저장.
2. LeftChild이 닐이 아니면 LeftChild의 부모에 저장.
3. 
*/
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
    RBTNode* LeftChild = Parent->Left;

    Parent->Left = LeftChild->Right;

    if (LeftChild->Right != Nil)
        LeftChild->Right->Parent = Parent;

    LeftChild->Parent = Parent->Parent;

    // 부모가 루트면 루트에 LeftChild 추가
    if (Parent->Parent == NULL)
        (*Root) = LeftChild;
    else
    {
        // 부모가 할아버지의 왼쪽 자식이면
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = LeftChild;
        else
            Parent->Parent->Right = LeftChild;
    }

    LeftChild->Right = Parent;
    Parent->Parent = LeftChild;
}

void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{
    RBTNode* RightChild = Parent->Right;

    Parent->Right = RightChild->Left;

    if (RightChild->Left != Nil)
        RightChild->Left->Parent = Parent;

    RightChild->Parent = Parent->Parent;

    if (Parent->Parent == NULL)
        (*Root) = RightChild;
    else
    {
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = RightChild;
        else
            Parent->Parent->Right = RightChild;
    }

    RightChild->Left = Parent;
    Parent->Parent = RightChild;
}

void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X)
{
    while (X != (*Root) && X->Parent->Color == RED) // 4번을 만족할때까지 반복 (RED가 연속으로 오지 않음)
    {
        // 부모가 할아버지의 왼쪽 자식.
        if (X->Parent == X->Parent->Parent->Left)
        {
            RBTNode* Uncle = X->Parent->Parent->Right;
            if (Uncle->Color == RED) // Case 1. 부모도 Red, 삼촌도 Red
            {
                // 부모와 삼촌의 색 = Black , 할아버지 색 = Red
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent->Color = RED;

                X = X->Parent->Parent;
            }
            else
            {
                if (X == X->Parent->Right) // Case 2. 꺾임.
                {
                    X = X->Parent;
                    RBT_RotateLeft(Root, X); // 부모기준 좌회전.
                }

                // Case 3. 일직선.
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;

                RBT_RotateRight(Root, X->Parent->Parent);
            }
        }

        // 부모가 할아버지의 오른쪽 자식.
        else
        {
            RBTNode* Uncle = X->Parent->Parent->Left;
            if (Uncle->Color == RED) // Case 1. 부모도 Red, 삼촌도 Red
            {
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent->Color = RED;

                X = X->Parent->Parent;
            }
            else
            {
                if (X == X->Parent->Left) // Case 2. 꺾임.
                {
                    X = X->Parent;
                    RBT_RotateRight(Root, X);
                }

                // Case 3. 일직선.
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;
                RBT_RotateLeft(Root, X->Parent->Parent);
            }
        }
    }

    (*Root)->Color = BLACK;
}

RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
    RBTNode* Removed = NULL;
    RBTNode* Successor = NULL;
    RBTNode* Target = RBT_SearchNode((*Root), Data);

    if (Target == NULL)
        return NULL;

    // 타겟의 자식이 없을 때,
    if (Target->Left == Nil || Target->Right == Nil)
    {
        Removed = Target;
    }
    // Successor와 교환
    else
    {
        Removed = RBT_SearchMinNode(Target->Right); // Successor
        Target->Data = Removed->Data;
    }

    // Successor가 Nil이 아니면
    if (Removed->Left != Nil)
        Successor = Removed->Left; // successor 자리에 올 녀석
    else
        Successor = Removed->Right;


    // Successor로 올라오는 녀석 설정.
    Successor->Parent = Removed->Parent;

    // Successor가 Root면 루트로.
    if (Removed->Parent == NULL)
        (*Root) = Successor;
    else
    {
        if (Removed == Removed->Parent->Left)
            Removed->Parent->Left = Successor;
        else
            Removed->Parent->Right = Successor;
    }

    // BLACK 삭제되면 extra-black 처리
    if (Removed->Color == BLACK)
        RBT_RebuildAfterRemove(Root, Successor);

    return Removed;
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
    RBTNode* Sibling = NULL;

    while (Successor->Parent != NULL && Successor->Color == BLACK) // Root 거나 Red로 Black이 넘어가면 종료
    {
        if (Successor == Successor->Parent->Left) // 왼쪽 자식이면
        {
            Sibling = Successor->Parent->Right; // 형제 정의

            if (Sibling->Color == RED) //  Case#1 형제가 RED
            {
                /*
                형제와 부모의 색 변경 후, 좌회전
                */
                Sibling->Color = BLACK;
                Successor->Parent->Color = RED;
                RBT_RotateLeft(Root, Successor->Parent);
            }
            else
            {
                // Case#2 형제의 LEFT가 BLACK && 형제의 RIGHT가 BLACK
                if (Sibling->Left->Color == BLACK &&
                    Sibling->Right->Color == BLACK)
                {
                    /*
                    1. doubly-black 과 형제의 블랙 모아서 부모로 줌.
                    2. 부모의 red-and-black 해결.
                    */
                    Sibling->Color = RED;
                    Successor = Successor->Parent;
                }
                else
                {
                    // Case#3 형제가 Black && 형제 자식 왼쪽 Red, 오른쪽 Black
                    if (Sibling->Left->Color == RED)
                    {
                        /*
                        형제의 오른쪽 자녀가 Red 되게 변경 후 Case.4로 해결
                        1. 형제와 형제의 왼쪽 Red와 색 변경.
                        2. 형제 기준으로 우회전.
                        */
                        Sibling->Left->Color = BLACK;
                        Sibling->Color = RED;

                        RBT_RotateRight(Root, Sibling);
                        Sibling = Successor->Parent->Right;
                    }

                    // Case#4 
                    /*
                    1. 형제 색을 부모 색으로.
                    2. 부모& 형제의 오른쪽 자식 검은색.
                    3. 부모 기준 왼쪽으로 회전.
                    */
                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = BLACK;
                    Sibling->Right->Color = BLACK;
                    RBT_RotateLeft(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
        // 반대
        else
        {
            Sibling = Successor->Parent->Left;

            if (Sibling->Color == RED)
            {
                Sibling->Color = BLACK;
                Successor->Parent->Color = RED;
                RBT_RotateRight(Root, Successor->Parent);
            }
            else
            {
                if (Sibling->Right->Color == BLACK &&
                    Sibling->Left->Color == BLACK)
                {
                    Sibling->Color = RED;
                    Successor = Successor->Parent;
                }
                else
                {
                    if (Sibling->Right->Color == RED)
                    {
                        Sibling->Right->Color = BLACK;
                        Sibling->Color = RED;

                        RBT_RotateLeft(Root, Sibling);
                        Sibling = Successor->Parent->Left;
                    }

                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = BLACK;
                    Sibling->Left->Color = BLACK;
                    RBT_RotateRight(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
    }

    Successor->Color = BLACK;
}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount)
{
    int   i = 0;
    char c = 'X';
    int  v = -1;
    char cnt[100];

    if (Node == NULL || Node == Nil)
        return;

    if (Node->Color == BLACK)
        BlackCount++;

    if (Node->Parent != NULL)
    {
        v = Node->Parent->Data;

        if (Node->Parent->Left == Node)
            c = 'L';
        else
            c = 'R';
    }

    if (Node->Left == Nil && Node->Right == Nil)
        sprintf(cnt, "--------- %d", BlackCount);
    else
        strncpy(cnt, "", sizeof(cnt));

    for (i = 0; i < Depth; i++)
        printf("  ");

    printf("%d %s [%c,%d] %s\n", Node->Data,
        (Node->Color == RED) ? "RED" : "BLACK", c, v, cnt);

    RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
    RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}
