#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data){
    Node *n = (Node*)malloc(sizeof(Node));
    if(!n) return NULL;
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

Node* insert(Node *root, int data){
    if(root == NULL) return createNode(data);
    if(data < root->data) root->left = insert(root->left, data);
    else if(data > root->data) root->right = insert(root->right, data);
    return root;
}

bool search(Node *root, int data){
    while(root != NULL){
        if(data == root->data) return true;
        root = (data < root->data) ? root->left : root->right;
    }
    return false;
}

Node* findMin(Node *root){
    while(root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node *root, int data){
    if(root == NULL) return NULL;

    if(data < root->data) root->left = deleteNode(root->left, data);
    else if(data > root->data) root->right = deleteNode(root->right, data);
    else {
        if(root->left == NULL){
            Node *r = root->right;
            free(root);
            return r;
        } else if(root->right == NULL){
            Node *l = root->left;
            free(root);
            return l;
        } else {
            Node *succ = findMin(root->right);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
    }
    return root;
}

void inorder(Node *root){
    if(!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node *root){
    if(!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

/* BFS queue for Node* */
typedef struct QNode {
    Node *ptr;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front, *rear;
} Queue;

void qInit(Queue *q){ q->front = q->rear = NULL; }
bool qEmpty(Queue *q){ return q->front == NULL; }

void enqueue(Queue *q, Node *p){
    QNode *n = (QNode*)malloc(sizeof(QNode));
    if(!n) return;
    n->ptr = p;
    n->next = NULL;
    if(q->rear == NULL){
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

Node* dequeue(Queue *q){
    if(qEmpty(q)) return NULL;
    QNode *t = q->front;
    Node *p = t->ptr;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(t);
    return p;
}

void levelOrder(Node *root){
    if(!root) return;
    Queue q; qInit(&q);
    enqueue(&q, root);

    while(!qEmpty(&q)){
        Node *cur = dequeue(&q);
        printf("%d ", cur->data);
        if(cur->left) enqueue(&q, cur->left);
        if(cur->right) enqueue(&q, cur->right);
    }
}

void destroy(Node *root){
    if(!root) return;
    destroy(root->left);
    destroy(root->right);
    free(root);
}

int main(){
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("DFS Inorder   : "); inorder(root); printf("\n");
    printf("DFS Preorder  : "); preorder(root); printf("\n");
    printf("DFS Postorder : "); postorder(root); printf("\n");
    printf("BFS LevelOrder: "); levelOrder(root); printf("\n");

    printf("search 60: %s\n", search(root, 60) ? "found" : "not found");

    root = deleteNode(root, 70);
    printf("After delete 70 (inorder): "); inorder(root); printf("\n");

    destroy(root);
    return 0;
}
