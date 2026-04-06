//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{ // 파이썬에서 Node class
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{ // 파이썬에서 LinkedList class
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll); // 리스트 출력
void removeAllItems(LinkedList *ll); // 리스트 전체 삭제
ListNode *findNode(LinkedList *ll, int index); // 특정 위치 노드 찾기
int insertNode(LinkedList *ll, int index, int value); // 특정 위치에 새 노드 넣기
int removeNode(LinkedList *ll, int index); // 특정 위치 노드 삭제


//////////////////////////// main() //////////////////////////////////////////////

int main() // 프로그램의 시작점
{
	LinkedList ll; // 연결 리스트 전체
	int c, i, j; // c : 메뉴 선택 번호, i : 사용자가 넣고 싶은 숫자, j : 그 숫자가 들어간 위치
	c = 1;

	//Initialize the linked list 1 as an empty linked list (리스트 초기화)
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n"); // 숫자 넣기
	printf("2: Print the index of the most recent input value:\n"); // 방금 넣은 숫자의 위치 출력
	printf("3: Print sorted linked list:\n"); // 리스트 출력
	printf("0: Quit:"); // 종료

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c); // 메뉴 선택 받기

		switch (c)
		{
		case 1: // 숫자 넣기
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i); // i를 입력 받기
			j = insertSortedLL(&ll, i); // 이 숫자를 알맞는 자리에 넣어줘 -> j에게 돌려줌
			printf("The resulting linked list is: ");
			printList(&ll); // 현재 리스트 출력
			break;
		case 2: // 방금 넣은 숫자의 위치 출력
			printf("The value %d was added at index %d\n", i, j); // 마지막 넣은 i가 j 인덱스에 들어갔습니다.
			break;
		case 3: // 리스트 출력
			printf("The resulting sorted linked list is: ");
			printList(&ll); // 리스트 출력
			removeAllItems(&ll); // 리스트 전체 삭제 (테스트가 끝난 뒤 정리하려고 그런 듯)
			break;
		case 0: // 종료
			removeAllItems(&ll); // 리스트 전체 삭제
			break;
		default: // 이상한 숫자 넣으면
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item) // 몇 번째 자리에 넣을지 찾는 함수
{
	/* add your code here */
    int index = 0;
    ListNode *cur = ll -> head;

    while (cur && cur -> item < item) { 
        cur = cur -> next ;
        index += 1; 
    }

    if (cur != NULL) {
        if (cur -> item == item) {
            return -1;
        }
    }

    insertNode(ll, index, item);

    return index;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){ 

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
