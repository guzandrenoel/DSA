#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node, *NodePtr;

typedef struct Queue{
    NodePtr front;
    NodePtr rear;
}Queue;

// core functions
Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

// extra functions
NodePtr createNode(int value);
void displayMenu();
int getChoice();
int getNumber();

// to store core function operations
void mainFunctions(Queue* q, int choice);

// cleanup
void freeQueue(Queue* q);

int main(){
    Queue *q = initialize();
    int choice;

    while(1){
        displayMenu();
        choice = getChoice();

        if(choice == 4){
            printf("Exiting program.\n");
            break;
        }

        mainFunctions(q, choice);
    }

    freeQueue(q);
    free(q);
    return 0;
}

void mainFunctions(Queue* q, int choice){
    switch(choice){
        case 1:
            enqueue(q, getNumber());
            break;

        case 2: {
            int removed = dequeue(q);
            (removed != -1) ? printf("%d has been dequeued.\n", removed)
                            : printf("Unable to dequeue. Queue is empty.\n");
            break;
        }

        case 3:
            display(q);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }
}

// core functions
Queue* initialize(){
    Queue *q = malloc(sizeof(Queue));
    if(q == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    printf("Queue initialized.\n");
    return q;
}

bool isFull(Queue* q){
    return false;
}

bool isEmpty(Queue* q){
    return q->front == NULL;
}

void enqueue(Queue* q, int value){
    NodePtr newNode = createNode(value);
    if(newNode == NULL){
        printf("Unable to enqueue, no memory.\n");
        return;
    }

    if(isEmpty(q)){
        q->front = newNode;
        q->rear  = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("%d has been queued.\n", value);
}

int dequeue(Queue* q){
    if(!isEmpty(q)){
        NodePtr temp = q->front;
        int removedElem = temp->data;

        q->front = q->front->next;
        if(isEmpty(q)){
            q->rear = NULL;
        }

        free(temp);
        return removedElem;
    }
    return -1;
}

int front(Queue* q){
    if(!isEmpty(q)){
        return q->front->data;
    }
    return -1;
}

void display(Queue* q){
    if(!isEmpty(q)){
        for(NodePtr trav = q->front; trav != NULL; trav = trav->next){
            printf("%d", trav->data);
            if(trav->next != NULL) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("Queue is empty.\n");
    }
}

// extra functions
NodePtr createNode(int value){
    NodePtr newNode = malloc(sizeof(Node));
    if(newNode == NULL) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void displayMenu(){
    printf("\n ---- Queue Program ---- \n");
    printf("1. Enqueue\n2. Dequeue\n3. Display Queue\n4. Exit\n");
}

int getChoice(){
    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    return choice;
}

int getNumber(){
    int value;
    printf("Enter number to enqueue: ");
    scanf("%d", &value);
    return value;
}

void freeQueue(Queue* q){
    while(!isEmpty(q)){
        dequeue(q);
    }
}
