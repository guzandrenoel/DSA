#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int locate(List L, int data);
int retrieve(List L, int position);
void insertSorted(List *L, int data);
void display(List L);
void resize(List *L);
void makeNull(List *L);

int main(){
    List L;
    initialize(&L);

    insertPos(&L, 110, 0); // test resize()
    insertPos(&L, 100, 0);
    insertPos(&L, 90, 0);
    insertPos(&L, 80, 0);
    insertPos(&L, 70, 0);
    insertPos(&L, 60, 0);
    insertPos(&L, 50, 0);
    insertPos(&L, 40, 0);
    insertPos(&L, 30, 0);
    insertPos(&L, 20, 0);
    insertPos(&L, 10, 0);

    display(L);

    int locnum = 10, found = locate(L, locnum);
    (found != -1) ? printf("%d found on index %d!\n", locnum, found)
                  : printf("%d not found in array!\n", locnum);

    int retindex = 5, ret = retrieve(L, retindex);
    (ret != -1) ? printf("%d retrieved from index %d!\n", ret, retindex)
                : printf("None found in index %d!\n", retindex);

    makeNull(&L); // free memory at the end
    return 0;
}

void initialize(List *L){
    L->elemPtr = malloc(sizeof(int) * LENGTH);
    L->count = 0;
    L->max = LENGTH;
    for(int i = 0; i < LENGTH; i++){
        L->elemPtr[i] = -1;
    }
}

void insertPos(List *L, int data, int position){
    if(L->count == L->max){
        resize(L);
    }

    if(position >= 0 && position <= L->count){

        // FIX: shift only within used elements (count), not max
        for(int i = L->count; i > position; i--){
            L->elemPtr[i] = L->elemPtr[i-1];
        }

        L->elemPtr[position] = data;
        L->count++;

    } else {
        printf("Unable to add %d to position %d!\n", data, position);
    }
}

void deletePos(List *L, int position){
    // FIX: valid only if position < count
    if(position >= 0 && position < L->count){

        for(int i = position; i < L->count - 1; i++){
            L->elemPtr[i] = L->elemPtr[i+1];
        }

        // FIX: clear last used slot
        L->elemPtr[L->count - 1] = -1;
        L->count--;

    } else {
        printf("Unable to delete index %d!\n", position);
    }
}

int locate(List L, int data){
    // FIX: search only used part
    for(int i = 0; i < L.count; i++){
        if(L.elemPtr[i] == data){
            return i;
        }
    }
    return -1;
}

int retrieve(List L, int position){
    // FIX: must be position < count
    if(position >= 0 && position < L.count){
        return L.elemPtr[position];
    }
    return -1;
}

void insertSorted(List *L, int data){
    if(L->count == L->max){
        resize(L);
    }
    int i = L->count - 1;
    while(i >= 0 && L->elemPtr[i] >= data){
        L->elemPtr[i+1] = L->elemPtr[i];
        i--;
    }
    L->elemPtr[i+1] = data;
    L->count++;
}

void display(List L){
    printf("Display:\n");
    for(int i = 0; i < L.max; i++){
        printf("%d ", L.elemPtr[i]);
    }
    printf("\nCount = %d\n", L.count);
    printf("Max = %d\n", L.max);
}

void resize(List *L){
    printf("Resizing...\n");
    L->max = L->max * 2;
    L->elemPtr = realloc(L->elemPtr, sizeof(int) * L->max);
    for(int i = L->count; i < L->max; i++){
        L->elemPtr[i] = -1;
    }
    printf("Successfully resized array!\n");
}

void makeNull(List *L){
    free(L->elemPtr);
    L->elemPtr = NULL;   // FIX: avoid dangling pointer
    L->count = 0;
    L->max = 0;
    printf("Freed list!\n");
}
