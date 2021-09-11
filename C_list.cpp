/*************************************************************************
>> File Name: ����.c
>> Author: chenjunjie
>> Mail: 2716705056qq.com
>> Created Time: 2019.01.22

>> Last Modified : 2021��03��25�� ������ 10ʱ37��02��
�������½ṹ������ֻ����ͷ���ͽڵ���������

typedef struct List_Node
{
    int value;
    struct List_Node  *next;
}Node;

typedef struct LIST
{
    Node *head;
    int num;
}List;

*/

#include <iostream>
using namespace std;
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>

#include <queue>
#define ONE 1

typedef struct List_Node
{
    int value;
    struct List_Node *next;
} Node;

typedef struct LIST
{
    Node *head;
    int num;
} List;

void Initialize(List *list)  //��ʼ������
{
    list->head = NULL;
    list->num = 0;
}

bool ListIsFull(const List *list)  //�ж������Ƿ�����
{
    Node *node = (Node *)malloc(sizeof(Node));
    bool full;
    if (node == NULL)
        full = true;
    else
        full = false;
    free(node);
    node = NULL;
    return full;
}

bool ListIsEmpty(const List *list)  //�ж������Ƿ�Ϊ��
{
    if (list->head == NULL)
        return true;
    else
        return false;
}

void showNode(const Node *node)
{
    printf("%d  ", node->value);
}

void Traverse(const List *list,
              void (*pfun)(const Node *node))  //�Ժ���*pfun���������ÿ���ڵ�
{
    const Node *node = list->head;
    while (node != NULL)
    {
        (*pfun)(node);
        node = node->next;
    }
    printf("\n");
}

void Traverse1(Node *pHead,
               void (*pfun)(const Node *node))  //�Ժ���*pfun���������ÿ���ڵ�
{
    Node *node = pHead;
    while (node != NULL)
    {
        (*pfun)(node);
        node = node->next;
    }
    printf("\n");
}

bool addFromHead(List *list, int value)  //������ͷ���������
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("�޷������ڴ桢����������������...\n");
        return false;
    }
    node->value = value;
    if (list->head == NULL)
    {
        node->next = NULL;
        list->head = node;

    }
    else
    {
        node->next = list->head;
        list->head = node;
    }

    list->num++;
    return true;
}

bool addFromEnd(List *list, int value)  //������β����ӽڵ�
{
    Node *node = (Node *)malloc(sizeof(Node));
    Node *pr = list->head;
    if (node == NULL)
        //memory not enough
        return false;
    node->value = value;
    node->next = NULL;

    if (pr == NULL)
        list->head = node;
    else
    {
        while (pr->next != NULL) pr = pr->next;
        pr->next = node;
    }

    list->num++;
    return true;
}

void getListNodeNum(const List *list)  //��������ڵ�����
{
    int num = list->num;
    printf("List has %d nodes\n", num);
}

int *deleteFromHead(List *list)  //��ͷ��ɾ������Ľڵ�
{
    int *data = (int *)malloc(sizeof(int));
    Node *pr;
    if (list->head == NULL)
        data = NULL;
    else
    {
        *data = list->head->value;
        pr = list->head->next;
        free(list->head);
        list->head = pr;
    }
    list->num--;
    return data;
}

void deleteFromEnd(List *list, int *x)  //������β��ɾ���ڵ�
{
    Node *pr = list->head;
    if (list->head == NULL)
        return;
    else
    {
        if (list->head->next == NULL)
        {
            *x = list->head->value;
            list->head = NULL;
        }
        else
        {
            while (pr->next->next != NULL)
            {
                pr = pr->next;
            }
            *x = pr->next->value;
            free(pr->next);
            pr->next = NULL;
        }
        list->num--;
    }
}

void emptyList(List *list)  //�������
{

    Node *pr = (Node *)malloc(sizeof(Node));
    while (list->head != NULL)
    {
        pr = list->head->next;
        free(list->head);
        list->head = pr;
        list->num--;
    }
    //return false
}

void reverseList(List *list)  //��ת����ѭ��ʵ��
{
    Node *next = NULL;
    Node *node = list->head;
    Node *pre = NULL;
    while (node != NULL)
    {
        next = node->next;
        node->next = pre;
        pre = node;
        node = next;
    }
    list->head = pre;
}

Node *reverseListRecurse(Node *node)  //��ת����:�ݹ�ʵ��
{
    if (node == NULL || node->next == NULL)
        return node;
    else
    {
        Node *tmpNode = reverseListRecurse(node->next);
        node->next->next = node;
        node->next = NULL;
        return tmpNode;
    }
}

Node *findKthTail1(Node *node, int k)  //���������ĵ�����K���ڵ�,�ݹ�ʵ��
{
    static int num;
    num = k;
    if (node == NULL) return NULL;
    Node *ptr = findKthTail1(node->next, k);
    if (ptr != NULL)
        return ptr;
    else
    {
        num--;
        if (num == 0) return node;
        return NULL;
    }
}

Node *findKthTail2(Node *pHead, int k)  //���������ĵ�����K���ڵ�,˫ָ��ʵ��
{
    if (pHead == NULL || k == 0) return NULL;
    Node *pt1 = pHead;
    Node *pt2 = pHead;
    for (int i = 0; i < k; i++)
    {
        if (pt1)
            pt1 = pt1->next;
        else
            return NULL;
    }
    while (pt1)
    {
        pt1 = pt1->next;
        pt2 = pt2->next;
    }
    return pt2;
}

bool IsExistLoop(Node *pHead)  //�ж������Ƿ��л�
{
    Node *fast = pHead;
    Node *slow = pHead;
    while (slow != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) return true;
    }
    return false;
}

Node *getMeetingNode(Node *pHead)  //�ж������Ƿ��л�
{
    Node *fast = pHead;
    Node *slow = pHead;
    while (slow != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) return slow;
    }
    return NULL;
}

Node *getEntryNodeofLoop(Node *pHead)  //�õ�������ڽڵ�
{
    Node *meet = getMeetingNode(pHead);
    if (meet == NULL) return NULL;
    Node *pt1 = meet;
    Node *pt2 = pHead;
    while (pt1 != pt2)
    {
        pt1 = pt1->next;
        pt2 = pt2->next;
    }
    return pt1;
}

int getLoopLength(Node *head)  //���㻷�ĳ���
{
    Node *slow = head;
    Node *fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)  //��һ������
            break;
    }
    // slow��fast����ǰ��
    slow = slow->next;
    fast = fast->next->next;
    int length = 1;       //������
    while (fast != slow)  //�ٴ�����
    {
        slow = slow->next;
        fast = fast->next->next;
        length++;  //�ۼ�
    }
    //��slow��fast�ٴ��������õ�������
    return length;
}

Node *MergeOrderList1(Node *pHead1, Node *pHead2)  //��ı�ԭ��Ҫ�ϲ�����������
{
    Node *pTail = NULL;  //ָ������������һ����� pTail->nextȥ����
    Node *newHead = NULL;  //ָ��ϲ��������һ�����
    Node *p1 = pHead1;
    Node *p2 = pHead2;
    if (p1 == NULL)
    {
        return p2;
    }
    else if (p2 == NULL)
    {
        return p1;
    }
    else
    {
        //ȷ��ͷָ��
        if (p1->value < p2->value)
        {
            newHead = p1;
            p1 = p1->next;  //ָ������ĵڶ������
        }
        else
        {
            newHead = p2;
            p2 = p2->next;
        }
        pTail = newHead;  //ָ���һ�����
        while (p1 && p2)
        {
            if (p1->value < p2->value)
            {
                pTail->next = p1;
                p1 = p1->next;
            }
            else
            {
                pTail->next = p2;
                p2 = p2->next;
            }
            pTail = pTail->next;
        }
        if (p1 == NULL)
        {
            pTail->next = p2;
        }
        else if (p2 == NULL)
        {
            pTail->next = p1;
        }
        return newHead;
    }
}

Node *MergeOrderList2(Node *pHead1, Node *pHead2)  //��ı�ԭ��Ҫ�ϲ�����������
{
    if (pHead1 == NULL)
    {
        return pHead2;
    }
    else if (pHead2 == NULL)
    {
        return pHead2;
    }
    Node *newHead = NULL;
    if (pHead1->value <= pHead2->value)
    {
        newHead = pHead1;
        newHead->next = MergeOrderList2(pHead1->next, pHead2);
    }
    else
    {
        newHead = pHead2;
        newHead->next = MergeOrderList2(pHead1, pHead2->next);
    }
    return newHead;
}

void deleteNode(List *list, Node *pDeleteNode)  //ɾ���ڵ�,��ʱ�临�Ӷ�O(1)���
{
    if (pDeleteNode == NULL) return;

    if (pDeleteNode->next != NULL)
    {
        Node *pNext = pDeleteNode->next;
        pDeleteNode->value = pNext->value;
        pDeleteNode->next = pNext->next;
        delete pNext;
        pNext = nullptr;
    }
    else if (list->head == pDeleteNode)
    {
        delete pDeleteNode;
        pDeleteNode = nullptr;
        list->head = nullptr;
    }
    else
    {
        Node *ptr = list->head;
        while (ptr->next != pDeleteNode) ptr = ptr->next;
        ptr->next = NULL;
        delete pDeleteNode;
        pDeleteNode = NULL;
    }
}

vector<int> printListformTailtoHead1(List *list)  //��β��ͷ��ӡ����,�ǵݹ�ʵ��
{
    vector<int> result;
    Node *ptr = list->head;
    stack<int> Stack;
    while (ptr != NULL)
    {
        Stack.push(ptr->value);
        ptr = ptr->next;
    }

    while (!Stack.empty())
    {
        result.push_back(Stack.top());
        Stack.pop();
    }
    return result;
}

vector<int> printListformTailtoHead2(
    Node *pHead)  //��β��ͷ��ӡ����,�ݹ�ʵ�֣��汾һ
{
    static vector<int> REsult;
    Node *pt = pHead;
    if (pt != NULL)
    {
        if (pt->next != NULL) printListformTailtoHead2(pt->next);
        REsult.push_back(pt->value);
    }
    return REsult;
}
void printListformTailtoHead3(
    Node *pHead, vector<int> &result)  //��β��ͷ��ӡ����,�ݹ�ʵ�֣��汾��
{
    // static vector<int> REsult;
    Node *pt = pHead;
    if (pt != NULL)
    {
        if (pt->next != NULL) printListformTailtoHead3(pt->next, result);
        result.push_back(pt->value);
    }
    // return REsult;
}

int main(int argc, char *argv[])
{
    List *myList = (List *)malloc(sizeof(List));
    // List myList;
    bool flag;
    Initialize(myList);
    addFromEnd(myList, 1);
    addFromEnd(myList, 3);
    addFromEnd(myList, 5);
    addFromEnd(myList, 7);
    addFromEnd(myList, 9);
    addFromEnd(myList, 11);
    addFromEnd(myList, 13);
    addFromEnd(myList, 15);

    getListNodeNum(myList);
    Traverse(myList, &showNode);
    cout << endl;

    printf("��ת�����ǵݹ�ʵ��\n");
    reverseList(myList);
    getListNodeNum(myList);
    Traverse(myList, &showNode);
    cout << '\n';

    cout << "��ת����,�ݹ�ʵ��\n";
    myList->head = reverseListRecurse(myList->head);
    getListNodeNum(myList);
    Traverse(myList, &showNode);
    cout << '\n';

    Node *ptr1 = findKthTail1(myList->head, 3);
    printf("�����������ڵ�Ϊ:%d\n", ptr1->value);

    Node *ptr2 = findKthTail2(myList->head, 3);
    printf("�����������ڵ�Ϊ:%d\n", ptr2->value);

    printf("ɾ��ͷ��������β���������Ԫ��\n");
    int *a;
    a = deleteFromHead(myList);
    int *b;
    b = deleteFromHead(myList);
    int c;
    deleteFromEnd(myList, &c);
    int d;
    deleteFromEnd(myList, &d);

    printf("a = %d,b = %d,c = %d,d = %d\n", *a, *b, c, d);
    printf("\n");
    getListNodeNum(myList);
    Traverse(myList, &showNode);
    printf("\n");

    // emptyList( myList );

    cout << "�����ӡ����,�ǵݹ�ʵ��" << endl;
    vector<int> Result = printListformTailtoHead1(myList);
    for (auto i : Result)
    {
        cout << i << "  ";
    }
    cout << "\n\n";

    getListNodeNum(myList);
    Traverse(myList, &showNode);
    cout << endl;

    List *myList1 = (List *)malloc(sizeof(myList));
    Initialize(myList1);
    addFromEnd(myList1, 2);
    addFromEnd(myList1, 4);
    addFromEnd(myList1, 6);
    addFromEnd(myList1, 8);
    addFromEnd(myList1, 10);
    addFromEnd(myList1, 12);
    addFromEnd(myList1, 14);
    addFromEnd(myList1, 16);
    getListNodeNum(myList1);
    Traverse(myList1, &showNode);
    printf("\n");

    List *myList_copy = myList;

    printf("�ϲ������ǵݹ�ʵ��\n");
    Node *MergeList = MergeOrderList1(myList->head, myList1->head);
    Traverse1(MergeList, &showNode);
    cout << '\n';

    Traverse(myList_copy, &showNode);
    Traverse(myList1, &showNode);

    cout << "�����ӡ����,�ݹ�ʵ�֣��汾һ" << endl;
    vector<int> REsult1;
    REsult1 = printListformTailtoHead2(MergeList);
    for (auto i : REsult1)
    {
        cout << i << "  ";
    }
    cout << endl;

    cout << "�����ӡ����,�ݹ�ʵ�֣��汾��" << endl;
    vector<int> REsult2;
    printListformTailtoHead3(MergeList, REsult2);
    for (auto i : REsult2)
    {
        cout << i << "  ";
    }
    cout << endl;

    /*
        printf("�ϲ������ݹ�ʵ��\n");
        Node *MergeList1 = MergeOrderList2(myList -> head, myList1 -> head);
        Traverse1(MergeList1,&showNode);
        cout << '\n';

        Traverse(myList,&showNode);
        Traverse(myList1,&showNode);

        cout << "�����ӡ����,�ݹ�ʵ��" << endl;
        vector<int> RESult;
        RESult = printListformTailtoHead2(MergeList1);
        for(auto i : RESult)
        {
            cout << i << "  ";
        }
        cout << endl;
    */
    return 0;
}

/*
���Ϊ:

List has 8 nodes
1  3  5  7  9  11  13  15

��ת�����ǵݹ�ʵ��
List has 8 nodes
15  13  11  9  7  5  3  1

��ת����,�ݹ�ʵ��
List has 8 nodes
1  3  5  7  9  11  13  15

�����������ڵ�Ϊ:11
�����������ڵ�Ϊ:11
ɾ��ͷ��������β���������Ԫ��
a = 1,b = 3,c = 15,d = 13

List has 4 nodes
5  7  9  11

�����ӡ����,�ǵݹ�ʵ��
11  9  7  5

List has 4 nodes
5  7  9  11

List has 8 nodes
2  4  6  8  10  12  14  16

�ϲ������ǵݹ�ʵ��
2  4  5  6  7  8  9  10  11  12  14  16

5  6  7  8  9  10  11  12  14  16
2  4  5  6  7  8  9  10  11  12  14  16
�����ӡ����,�ݹ�ʵ�֣��汾һ
16  14  12  11  10  9  8  7  6  5  4  2
�����ӡ����,�ݹ�ʵ�֣��汾��
16  14  12  11  10  9  8  7  6  5  4  2

*/
