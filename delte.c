#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE 100
typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer left;
    treePointer right;
}node;
treePointer root = NULL;
treePointer queue[MAX_QUEUE];
int front = 0;
int rear = -1;

//binary search tree - temp 노드 찾기
treePointer modifisearch(treePointer tree, int k) {
    while (tree)
    {
        if (k < tree->data) {
            if (tree->left == NULL)
                return tree;
            else
                tree = tree->left;
        }
        else if (k > tree->data) {
            if (tree->right == NULL)
                return tree;
            else
                tree = tree->right;
        }
    }
    return tree; // tree가 NULL일때
}
//binary search tree - ptr 노드 삽입 함수
void insert(int k) {
    treePointer ptr = (treePointer)malloc(sizeof(node));
    treePointer node = root;
    treePointer temp = modifisearch(node, k);

    if (temp || !(node)) {
        ptr->data = k;
        ptr->left = NULL;
        ptr->right = NULL;
        if (node) {
            if (k < temp->data) temp->left = ptr;
            else temp->right = ptr;
        }
        else root = ptr;
    }
}
//level order방식 출력
void addq(treePointer newnode) {
    queue[++rear] = newnode;
}
treePointer deleteq() {
    return queue[front++];
}
void levelorder(treePointer ptr) {
    front = 0; rear = -1;
    for (int i = 0; i < MAX_QUEUE; i++) {
        queue[i] = NULL;
    }
    if (!ptr) return;
    addq(ptr);
    for (;;) {
        ptr = deleteq();
        if (ptr) {
            printf("%d ", ptr->data);
            if (ptr->left) {
                addq(ptr->left);
            }
            if (ptr->right) {
                addq(ptr->right);
            }
        }
        else {
            break;
        }
    }
    printf("\n");
}

treePointer search(treePointer tree, int k) {
    while (tree) {
        if (k < tree->data) {
            tree = tree->left;
        }
        else if (k > tree->data) {
            tree = tree->right;
        }
        else if (k == tree->data) {
            return tree;
        }
    }
    return tree; //tree가 NULL일때
}


int deletenode(treePointer root, int k) {
    treePointer delnode = search(root, k); //삭제할 노드
    treePointer tmp;
    treePointer pre;

    if (delnode == NULL)
        return 0;

    if (delnode->left) {            //delnode의 left 자식이 존재할때 (delnode의 left subtree 중 가장 큰값 찾기)

        pre = delnode;              //temp의 이전노드(부모노드)
        tmp = delnode->left;        //delnode의 left

        if (tmp->right == NULL) {                 //tmp->right 존재안할 경우
            delnode->data = tmp->data;
            delnode->left = tmp->left;
        }

        else {
            while (tmp->right) {         //tmp->right 존재할경우 tmp->right == NULL 일때까지 temp 이동
                pre = tmp;
                tmp = tmp->right;
            }

            delnode->data = tmp->data;
            pre->right = tmp->left;
        }

    }

    else if ((delnode->left == NULL) && (delnode->right != NULL)) {              //delnode의 left 자식 없고 right 자식만 존재할때(delnode의 right subtree 중 가장 작은 값 찾기)

        pre = delnode;              //temp의 이전노드(부모노드)
        tmp = delnode->right;       //delnode의 right


        if (tmp->left == NULL) {                 //tmp->left 존재안할 경우
            delnode->data = tmp->data;
            delnode->right = tmp->right;
        }
        else {
            while (tmp->left != NULL) {               //tmp->left 존재할경우 tmp->left == NULL될때까지 temp이동
                pre = tmp;
                tmp = tmp->right;
            }
            delnode->data = tmp->data;
            pre->left = tmp->right;
        }
    }

    else {                                                                //delnode의 자식이 없을때
        delnode = NULL;
    }
    return 1;
}


void main() {
    FILE* fp = fopen("input.txt", "r");
    FILE* fp2 = fopen("output.txt", "w");
    int n, m, i, num, result;
    fscanf(fp, "%d %d", &n, &m);

    //binary search Tree 구성
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &num);
        insert(num);
    }
    //levelorder 출력
    levelorder(root);

    //노드 제거
    for (i = 0; i < m; i++) {
        fscanf(fp, "%d", &num);
        result = deletenode(root, num);
        if (result == 0) {
            printf("-1\n");
        }
        else {
            levelorder(root);

        }
    }
}