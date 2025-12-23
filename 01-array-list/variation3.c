#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);

int main(){
    List L;               
    L = initialize(L);     

    L = insertPos(L, 5, 0);
    L = insertPos(L, 1, 0);
    L = insertPos(L, 2, 1);
    L = insertPos(L, 3, 2);
    L = insertPos(L, 4, 3);
    L = insertPos(L, 6, 5);
    L = insertPos(L, 7, 6);
    L = insertPos(L, 8, 7);
    L = insertPos(L, 9, 8);
    L = insertPos(L, 10, 9);

    display(L);

    L = deletePos(L, 9);
    L = deletePos(L, 0);

    display(L);

    int num = 4, found = locate(L, num);
    (found != -1) ? printf("%d found on index %d.\n", num, found) : printf("%d not found.\n", num);

    L = insertSorted(L, 11);
    L = insertSorted(L, 12);
    L = insertSorted(L, 10);

    display(L);

    L = deletePos(L, 9);
    display(L);

    free(L.elemPtr);        
    return 0;
}

List initialize(List L){
    L.elemPtr = malloc(sizeof(int) * LENGTH);
    for(int i = 0; i < LENGTH; i++){
        L.elemPtr[i] = -1;
    }
    L.count = 0;
    L.max = LENGTH;
    return L;
}

List insertPos(List L, int data, int position){
    if(position >= 0 && position <= L.count){

        if(L.count == L.max){
            printf("List is full, resizing.\n");
            L = resize(L);
        }

        for(int i = L.count; i > position; i--){
            L.elemPtr[i] = L.elemPtr[i-1];
        }

        L.elemPtr[position] = data;
        L.count++;

    } else {
        printf("Error adding! position %d, count %d\n", position, L.count);
    }
    return L;
}

List deletePos(List L, int position){

    if(position >= 0 && position < L.count){
        printf("Deleting %d in index %d!\n", L.elemPtr[position], position);

        for(int i = position; i < L.count - 1; i++){
            L.elemPtr[i] = L.elemPtr[i+1];
        }

        L.elemPtr[L.count - 1] = -1;
        L.count--;

    } else {
        printf("Error deleting! position %d, count %d\n", position, L.count);
    }
    return L;
}

int locate(List L, int data){
    for(int i = 0; i < L.count; i++){
        if(L.elemPtr[i] == data){
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data){
    if(L.count == L.max){
        printf("List is full, resizing.\n");
        L = resize(L);
    }

    int i = L.count - 1;
    while(i >= 0 && L.elemPtr[i] >= data){
        L.elemPtr[i+1] = L.elemPtr[i];
        i--;
    }
    L.elemPtr[i+1] = data;
    L.count++;

    return L;
}

void display(List L){
    printf("Displaying List\n");
    for(int i = 0; i < L.max; i++){
        printf("%d ", L.elemPtr[i]);
    }
    printf("\nCount = %d\n", L.count);
    printf("Max = %d\n", L.max);
}

List resize(List L){
    printf("Doubling size of array and max.\n");
    L.elemPtr = realloc(L.elemPtr, sizeof(int) * (L.max * 2));
    L.max = L.max * 2;

    for(int i = L.count; i < L.max; i++){
        L.elemPtr[i] = -1;
    }
    return L;
}
