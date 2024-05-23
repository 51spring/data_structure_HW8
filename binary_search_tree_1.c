#include <stdio.h>
#include <stdlib.h>

typedef struct node  // 트리 노드 구조체 key, left, right로 정의
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr);	  // 재귀적 중위 순회
void preorderTraversal(Node* ptr);    // 재귀적 전위 순회
void postorderTraversal(Node* ptr);	  // 재귀적 후위 순회
int insert(Node* head, int key);  // 트리에 노드 삽입
int deleteLeafNode(Node* head, int key);  // 리프 노드 삭제
Node* searchRecursive(Node* ptr, int key);  // 재귀적으로 노드 검색
Node* searchIterative(Node* head, int key);  // 반복적으로 노드 검색
int freeBST(Node* head); // 트리의 모든 노드 삭제

int main()
{
	printf("2021041002 오원석\n");
	char command; // 입력 명령어
	int key; // 노드의 키 값
	Node* head = NULL; // 트리의 루트 노드
	Node* ptr = NULL; // 노드 검색 결과

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // 트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); // 트리의 모든 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 삽입할 노드의 키 값 입력
			insert(head, key); // 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 삭제할 노드의 키 값 입력
			deleteLeafNode(head, key); // 리프 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // 검색할 노드의 키 값 입력
			ptr = searchIterative(head, key); // 반복적으로 노드 검색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // 노드 검색 성공
			else
				printf("\n Cannot find the node [%d]\n", key); // ptr == NULL 이면 노드 검색 실패
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); // 검색할 노드의 키 값 입력
			ptr = searchRecursive(head->left, key); // 재귀적으로 노드 검색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // 노드 검색 성공
			else
				printf("\n Cannot find the node [%d]\n", key); // ptr == NULL 이면 노드 검색 실패
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // 재귀적 중위 순회
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 재귀적 전위 순회
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 재귀적 후위 순회
			break;
		default: // 잘못된 명령어 입력 시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q 입력 시 종료

	return 1;
}

int initializeBST(Node** h) // 트리 초기화
{ 
	
    if(*h != NULL) // 트리가 이미 존재하면 트리의 모든 노드 삭제
		freeBST(*h);

	*h = (Node*)malloc(sizeof(Node)); // 트리 루트 노드 동적 할당
	(*h)->left = NULL;	// 루트 노드의 왼쪽 자식 노드 NULL
    (*h)->right = *h; // 루트 노드의 오른쪽 자식 노드 자기 자신
	(*h)->key = -9999; // 루트 노드의 키 값 -9999
	return 1;
}

void inorderTraversal(Node* ptr) // 재귀적 중위 순회 왼쪽 보고 키값 출력하고 오른쪽 보기
{
    if (ptr != NULL) // 노드가 NULL이 아니면
    { 
        inorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동
        printf("%d ", ptr->key); // 키값 출력
        inorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동
    }
}

void preorderTraversal(Node* ptr) // 재귀적 전위 순회. 키값 출력하고 왼쪽 보고 오른쪽 보기
{
    if (ptr != NULL) // 노드가 NULL이 아니면
    { 
        printf("%d ", ptr->key); // 키값 출력
        preorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동
        preorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동
    }
}

void postorderTraversal(Node* ptr) // 재귀적 후위 순회. 왼쪽 보고 오른쪽 보고 키값 출력
{
    if (ptr != NULL) 
    {
        postorderTraversal(ptr->left); // 왼쪽 자식 노드로 이동
        postorderTraversal(ptr->right); // 오른쪽 자식 노드로 이동
        printf("%d ", ptr->key); // 키값 출력
    }
}

int insert(Node* head, int key) 
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 동적 할당
    newNode->key = key; // 새로운 노드의 키값 설정
    newNode->left = NULL; // 새로운 노드의 왼쪽 자식 노드 NULL
    newNode->right = NULL; // 새로운 노드의 오른쪽 자식 노드 NULL

    if(head->left == NULL) 
    {
        head->left = newNode; // 헤드 노드가 NULL이면 새로운 노드를 추가
    } 
    else 
    {
        Node* current = head->left; // 현재 노드를 헤드 노드의 왼쪽 자식 노드로 설정
        Node* parent = NULL; // 부모 노드 NULL로 초기화

        while(current != NULL) // BST에서 삽입할 위치 찾기
        {
            parent = current; // parent 노드를 current 노드로 설정
            if(key < current->key) // 삽입할 키값이 현재 노드의 키값보다 작으면
            {
                current = current->left; // 현재 노드를 왼쪽 자식 노드로 이동
            } 
            else 
            {
                current = current->right; // 삽입할 키값이 현재 노드의 키값보다 크면 현재 노드를 오른쪽 자식 노드로 이동
            }
        }

        if(key < parent->key) // 삽입할 키값이 부모 노드의 키값보다 작으면
        {
            parent->left = newNode; // 부모 노드의 왼쪽 자식 노드로 새로운 노드 추가
        } 
        else 
        {
            parent->right = newNode; // 삽입할 키값이 부모 노드의 키값보다 크면 부모 노드의 오른쪽 자식 노드로 새로운 노드 추가
        }
    }

    return 1;
}

int deleteLeafNode(Node* head, int key) // 리프 노드 삭제
{
    Node* current = head->left;  // 루트 노드를 current 노드로 설정
    Node* parent = NULL; // 부모 노드 NULL로 초기화

    while (current != NULL && current->key != key) // current 노드가 NULL이 아니고 current 노드의 키값이 삭제할 키값과 같지 않을때까지
    {
        parent = current; // parent 노드를 current 노드로 설정
        if (key < current->key) // 삭제할 키값이 current 노드의 키값보다 작으면
            current = current->left; // current 노드를 왼쪽 자식 노드로 이동
        else
            current = current->right; // 삭제할 키값이 current 노드의 키값보다 크면 current 노드를 오른쪽 자식 노드로 이동
    }

    if (current == NULL) // 목표 노드가 없으면 -1 반환
    {
        printf("the node [%d] is not in the tree\n", key);
        return -1;
    }

    if (current->left == NULL && current->right == NULL) // current 노드가 리프 노드이면
    {
        if (parent->left == current) // current 노드가 부모 노드의 왼쪽 자식 노드이면
            parent->left = NULL; // 부모 노드의 왼쪽 자식 노드 NULL
        else
            parent->right = NULL; // current 노드가 부모 노드의 오른쪽 자식 노드이면 부모 노드의 오른쪽 자식 노드 NULL 

        printf("delete [%d] node\n", key);
        free(current); // current 노드 동적 할당 해제
        return 1;
    } 
    else {
        printf("the node [%d] is not a leaf\n", key); // current 노드가 리프 노드가 아니면 문구 출력후 -1 반환
        return -1;
    }
}

Node* searchRecursive(Node* ptr, int key) // 재귀적으로 노드 검색
{
    if (ptr == NULL || ptr->key == key) // ptr이 NULL이거나 ptr의 키값이 찾는 키값과 같으면 ptr 반환
        return ptr;

    if (ptr->key < key) // ptr의 키값이 찾는 키값보다 작으면
        return searchRecursive(ptr->right, key); // 오른쪽 자식 노드로 이동

    return searchRecursive(ptr->left, key); // ptr의 키값이 찾는 키값보다 크면 왼쪽 자식 노드로 이동
}

Node* searchIterative(Node* head, int key)  // 반복적으로 노드 검색
{
    Node* current = head->left;  // 루트 노드를 current 노드로 설정

    while (current != NULL) // current 노드가 NULL이 아닐때까지
    {
        if (key == current->key) // 찾는 키값이 current 노드의 키값과 같으면 current 노드 반환
            return current;
        else if (key < current->key) // 찾는 키값이 current 노드의 키값보다 작으면
            current = current->left; // 왼쪽 자식 노드로 이동
        else
            current = current->right; // 찾는 키값이 current 노드의 키값보다 크면 오른쪽 자식 노드로 이동
    }

    return NULL;  // 찾는 키값이 없으면 NULL 반환
}

int freeBST(Node* head) // 트리 후위 순회로 모든 노드 삭제ㅉ
{
    if (head != NULL) // 헤드 노드가 NULL이 아니면
    {
        freeBST(head->left); // 왼쪽 자식 노드로 이동
        freeBST(head->right); // 오른쪽 자식 노드로 이동
        free(head); // 헤드 노드 동적 할당 해제
    }

    return 0;
}





