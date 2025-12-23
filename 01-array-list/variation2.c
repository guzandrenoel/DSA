#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
}Etype, *EPtr;

void initialize(EPtr L);
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, int data);
int retrieve(EPtr L, int position);
void insertSorted(EPtr L, int data);
void display(EPtr L);
void makeNULL(EPtr L);

int main(){
    EPtr L = malloc(sizeof(Etype));
    initialize(L);

    display(L);

    insertPos(L, 10, 0);
    insertPos(L, 11, 0);
    insertPos(L, 12, 0);
    insertPos(L, 9, 3);

    display(L);

    deletePos(L, 2);
    display(L);

    int lookfor = 12, found = locate(L, lookfor);
    (found == -1)? printf("%d not found.\n", lookfor): printf("%d found on index %d.\n", lookfor, found);

    int get = 1, ret = retrieve(L, get);
    (ret == -1)? printf("Element does not exist!\n"): printf("%d retrieved from list!\n", ret);

    insertSorted(L, 1);
    display(L);

    // If you want to reset:
    // makeNULL(L);
    // display(L);

    free(L);   // proper cleanup
    return 0;
}

void display(EPtr L){
    printf("\nDisplaying List:\n");
    for(int i = 0; i < MAX; i++){
        printf("%d ", L->elem[i]);
    }
    printf("\nCount = %d.\n", L->count);
}

void initialize(EPtr L){
    for(int i = 0; i < MAX; i++){
        L->elem[i] = -1;
    }
    L->count = 0;
    printf("Successfully initialized!\n\n");
}

void insertPos(EPtr L, int data, int position){
    if(position >= 0 && position <= L->count && L->count < MAX){

        // shift RIGHT
        for(int i = L->count; i > position; i--){
            L->elem[i] = L->elem[i-1];
        }

        L->elem[position] = data;
        L->count++;

    } else {
        printf("Error! Can't add %d at position %d.\n", data, position);
    }
}

void deletePos(EPtr L, int position){
    printf("Deleting position = %d.\n", position);

    if(position >= 0 && position < L->count){

        // shiftss LEFT 
        for(int i = position; i < L->count - 1; i++){
            L->elem[i] = L->elem[i+1];
        }

        // clear last used slot
        L->elem[L->count - 1] = -1;
        L->count--;

    } else {
        printf("Error deleting! count = %d, delete position = %d.\n", L->count, position);
    }
}

int locate(EPtr L, int data){
    printf("Looking for %d.\n", data);
    for(int i = 0; i < L->count; i++){
        if(L->elem[i] == data){
            return i;
        }
    }
    return -1;
}

int retrieve(EPtr L, int position){
    if(position >= 0 && position < L->count){
        return L->elem[position];
    }
    return -1;
}

void insertSorted(EPtr L, int data){
    if(L->count < MAX){
        int i = L->count - 1;
        while(i >= 0 && L->elem[i] > data){
            L->elem[i+1] = L->elem[i];
            i--;
        }
        L->elem[i+1] = data;
        L->count++;
        printf("Added %d successfully!\n", data);
    } else {
        printf("Error! Unable to add %d.\n", data);
    }
}


void makeNULL(EPtr L){
    for(int i = 0; i < MAX; i++){
        L->elem[i] = -1;
    }
    L->count = 0;
}
