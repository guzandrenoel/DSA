#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct{
    int elem;
    int next;
}Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
}VHeap;

typedef int List;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, int index);
void insertFirst(int *L, VHeap *V, int elem);
void insertLast(int* L, VHeap *V, int elem);
void insertPos(int* L, VHeap* V, int elem);
void insertSorted(int *L, VHeap *V, int elem);
void delete(int *L, VHeap *V, int elem);
void deleteAllOccurrence(int *L, VHeap *V, int elem);
void display(int L, VHeap V);

int main(){
    List L = -1;
    VHeap V;
    initialize(&V);

    insertFirst(&L, &V, 40);
    insertLast(&L, &V, 10);
    insertLast(&L, &V, 20);
    insertLast(&L, &V, 30);

    display(L, V);
    return 0;
}

void initialize(VHeap *V){
    V->avail = MAX - 1;
    for(int i = MAX - 1; i > 0; i--){
        V->H[i].next = i - 1;
    }
    V->H[0].next = -1;
}

int allocSpace(VHeap *V){
    int ret = V->avail;
    if(ret != -1){
        V->avail = V->H[ret].next;
    }
    return ret;
}

void deallocSpace(VHeap *V, int index){
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int *L, VHeap *V, int elem){
    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = *L;
        *L = newCell;
    } else {
        printf("No space available.\n");
    }
}

void insertLast(int* L, VHeap *V, int elem){
    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;
        V->H[newCell].next = -1;

        int *trav = L;
        while(*trav != -1){
            trav = &V->H[*trav].next;
        }
        *trav = newCell;
    } else {
        printf("No space available.\n");
    }
}

void insertSorted(int *L, VHeap *V, int elem){
    int newCell = allocSpace(V);
    if(newCell != -1){
        V->H[newCell].elem = elem;

        int *trav = L;
        while(*trav != -1 && V->H[*trav].elem < elem){
            trav = &V->H[*trav].next;
        }

        V->H[newCell].next = *trav;
        *trav = newCell;
    } else {
        printf("No space available.\n");
    }
}

void insertPos(int* L, VHeap* V, int elem){
    int index;
    printf("Enter index to insert: ");
    scanf("%d", &index);

    if(index == 0){
        insertFirst(L, V, elem);
    } else if(index == -1){
        insertLast(L, V, elem);
    } else {
        int newCell = allocSpace(V);
        if(newCell == -1){
            printf("No space available.\n");
            return;
        }

        V->H[newCell].elem = elem;

        int *trav = L;
        for(int i = 0; *trav != -1 && i < index - 1; i++){
            trav = &V->H[*trav].next;
        }

        V->H[newCell].next = *trav;
        *trav = newCell;
    }
}

void delete(int *L, VHeap *V, int elem){
    int *trav = L;

    while(*trav != -1 && V->H[*trav].elem != elem){
        trav = &V->H[*trav].next;
    }

    if(*trav != -1){
        int temp = *trav;
        *trav = V->H[temp].next;
        deallocSpace(V, temp);
    }
}

void deleteAllOccurrence(int *L, VHeap *V, int elem){
    int *trav = L;

    while(*trav != -1){
        if(V->H[*trav].elem == elem){
            int temp = *trav;
            *trav = V->H[temp].next;
            deallocSpace(V, temp);
        } else {
            trav = &V->H[*trav].next;
        }
    }
}

void display(int L, VHeap V){
    printf("\n--- Display ---\n");
    printf("L = %d\n", L);
    printf("%-5s | %-5s | %5s\n","Index","Elem","Next");

    for(int trav = L; trav != -1; trav = V.H[trav].next){
        printf("%-5d | %-5d | %5d\n", trav, V.H[trav].elem, V.H[trav].next);
    }
}
