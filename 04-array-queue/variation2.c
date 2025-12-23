
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

// extra functions
int getValue();
int choiceSelection();
void displayMenu();

int main(){
    Queue* Q = initialize();
    int choice = 0;

    while(choice < 4){
        displayMenu();
        choice = choiceSelection();

        switch(choice){
            case 1:
                enqueue(Q, getValue());
                break;

            case 2: {
                int x = dequeue(Q);
                if(x != -1) printf("Removed %d from the queue.\n", x);
                break;
            }

            case 3:
                display(Q);
                break;

            case 4:
                printf("Exiting program.\n");
                free(Q);
                return 0;
        }
    }

    free(Q);
    return 0;
}

// extra functions
int getValue(){
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    return value;
}

int choiceSelection(){
    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    return choice;
}

void displayMenu(){
    printf("\n---Queue Program---\n");
    printf("1. Queue\n2. Dequeue\n3. Display\n4. Exit Program\n");
}

// core functions
Queue* initialize(){
    Queue* q = malloc(sizeof(Queue));
    q->front = 1;
    q->rear = 0;
    return q;
}

bool isFull(Queue* q){
    return q->front == (q->rear + 2) % MAX;
}

bool isEmpty(Queue* q){
    return q->front == (q->rear + 1) % MAX;
}

void enqueue(Queue* q, int value){
    if(!isFull(q)){
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = value;
        printf("%d added to the queue!\n", value);
    } else {
        printf("Unable to enqueue, Queue is full!\n");
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){
        int removedElem = front(q);
        q->front = (q->front + 1) % MAX;
        return removedElem;
    } else {
        printf("Unable to dequeue, Queue is empty!\n");
        return -1;  
    }
}

int front(Queue* q){
    if(!isEmpty(q)){
        return q->items[q->front];
    }
    return -1;      
}

void display(Queue* q){
    printf("Displaying Queue Details:\n");
    if(!isEmpty(q)){
        for(int trav = q->front; trav != ((q->rear + 1) % MAX); trav = (trav + 1) % MAX){
            printf("%d ", q->items[trav]);
        }
        printf("\n");
    } else {
        printf("Queue is empty!\n");
    }
}
