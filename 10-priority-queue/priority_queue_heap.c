#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int data[MAX];
    int size;
} PriorityQueue;

void init(PriorityQueue *pq) { pq->size = 0; }
bool isEmpty(PriorityQueue *pq) { return pq->size == 0; }
bool isFull(PriorityQueue *pq) { return pq->size == MAX; }

void swap(int *a, int *b){ int t = *a; *a = *b; *b = t; }

void push(PriorityQueue *pq, int value) {
    if (isFull(pq)) {
        printf("Priority Queue is full.\n");
        return;
    }

    int i = pq->size;
    pq->data[i] = value;
    pq->size++;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (pq->data[p] <= pq->data[i]) break;
        swap(&pq->data[p], &pq->data[i]);
        i = p;
    }
}

int peek(PriorityQueue *pq) {
    if (isEmpty(pq)) return -1;
    return pq->data[0];
}

int pop(PriorityQueue *pq) {
    if (isEmpty(pq)) return -1;

    int root = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];

    int i = 0;
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < pq->size && pq->data[l] < pq->data[smallest]) smallest = l;
        if (r < pq->size && pq->data[r] < pq->data[smallest]) smallest = r;

        if (smallest == i) break;
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }

    return root;
}

void display(PriorityQueue *pq) {
    printf("Heap array: ");
    for (int i = 0; i < pq->size; i++) printf("%d ", pq->data[i]);
    printf("\n");
}

int main() {
    PriorityQueue pq;
    init(&pq);

    push(&pq, 10);
    push(&pq, 5);
    push(&pq, 20);
    push(&pq, 3);
    push(&pq, 7);

    display(&pq);
    printf("peek: %d\n", peek(&pq));

    printf("pop: %d\n", pop(&pq));
    printf("pop: %d\n", pop(&pq));
    display(&pq);

    return 0;
}
