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

//binary search tree - temp ��� ã��
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
    return tree; // tree�� NULL�϶�
}
//binary search tree - ptr ��� ���� �Լ�
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
//level order��� ���
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
    return tree; //tree�� NULL�϶�
}


int deletenode(treePointer root, int k) {
    treePointer delnode = search(root, k); //������ ���
    treePointer tmp;
    treePointer pre;

    if (delnode == NULL)
        return 0;

    if (delnode->left) {            //delnode�� left �ڽ��� �����Ҷ� (delnode�� left subtree �� ���� ū�� ã��)

        pre = delnode;              //temp�� �������(�θ���)
        tmp = delnode->left;        //delnode�� left

        if (tmp->right == NULL) {                 //tmp->right ������� ���
            delnode->data = tmp->data;
            delnode->left = tmp->left;
        }

        else {
            while (tmp->right) {         //tmp->right �����Ұ�� tmp->right == NULL �϶����� temp �̵�
                pre = tmp;
                tmp = tmp->right;
            }

            delnode->data = tmp->data;
            pre->right = tmp->left;
        }

    }

    else if ((delnode->left == NULL) && (delnode->right != NULL)) {              //delnode�� left �ڽ� ���� right �ڽĸ� �����Ҷ�(delnode�� right subtree �� ���� ���� �� ã��)

        pre = delnode;              //temp�� �������(�θ���)
        tmp = delnode->right;       //delnode�� right


        if (tmp->left == NULL) {                 //tmp->left ������� ���
            delnode->data = tmp->data;
            delnode->right = tmp->right;
        }
        else {
            while (tmp->left != NULL) {               //tmp->left �����Ұ�� tmp->left == NULL�ɶ����� temp�̵�
                pre = tmp;
                tmp = tmp->right;
            }
            delnode->data = tmp->data;
            pre->left = tmp->right;
        }
    }

    else {                                                                //delnode�� �ڽ��� ������
        delnode = NULL;
    }
    return 1;
}


void main() {
    FILE* fp = fopen("input.txt", "r");
    FILE* fp2 = fopen("output.txt", "w");
    int n, m, i, num, result;
    fscanf(fp, "%d %d", &n, &m);

    //binary search Tree ����
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &num);
        insert(num);
    }
    //levelorder ���
    levelorder(root);

    //��� ����
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