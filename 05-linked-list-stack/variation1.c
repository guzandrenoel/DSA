#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* top;
}Stack;

// core functions
Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

// extra functions
Node* createNode(int value);
void displayMenu();
int getChoice();
int getNumber();

void freeStack(Stack* s);

int main(){
    Stack *s = initialize();
    int choice = 0;

    while(1){
        displayMenu();
        choice = getChoice();

        switch(choice){
            case 1:
                push(s, getNumber());
                break;

            case 2: {
                int x = pop(s);
                if(x != -1) printf("Popped %d.\n", x);
                break;
            }

            case 3: {
                int x = peek(s);
                if(x != -1) printf("peek = %d.\n", x);
                break;
            }

            case 4:
                display(s);
                break;

            case 5:
                printf("Exiting program.\n");
                freeStack(s);
                free(s);
                return 0;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

// core functions
Stack* initialize(){
    Stack *s = malloc(sizeof(Stack));
    if(s == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

bool isFull(Stack* s){
    return false;
}

bool isEmpty(Stack* s){
    return s->top == NULL;
}

void push(Stack* s, int value){
    Node* newNode = createNode(value);
    if(newNode == NULL){
        printf("Unable to push, no memory.\n");
        return;
    }

    newNode->next = s->top;
    s->top = newNode;

    printf("Pushed %d.\n", value);
}

int pop(Stack* s){
    if(!isEmpty(s)){
        int removedElem = s->top->data;
        Node* temp = s->top;
        s->top = s->top->next;
        free(temp);
        return removedElem;
    } else {
        printf("Unable to pop, Stack is empty.\n");
        return -1;
    }
}

int peek(Stack* s){
    if(!isEmpty(s)){
        return s->top->data;
    } else {
        printf("Unable to peek, Stack is empty.\n");
        return -1;
    }
}

void display(Stack* s){
    printf("Printing stack details:\n");
    printf("top -> ");
    for(Node* trav = s->top; trav != NULL; trav = trav->next){
        printf("%d", trav->data);
        if(trav->next != NULL) printf(" -> ");
    }
    printf("\n");
}

// extra functions
Node* createNode(int value){
    Node* newNode = malloc(sizeof(Node));
    if(newNode == NULL) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void displayMenu(){
    printf("\n--- LL STACK PROGRAM BY JL ---\n");
    printf("1. Push\n2. Pop\n3. Peek\n4. Display Stack\n5. Exit\n");
}

int getChoice(){
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int getNumber(){
    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);
    return value;
}

void freeStack(Stack* s){
    while(!isEmpty(s)){
        pop(s);
    }
}
