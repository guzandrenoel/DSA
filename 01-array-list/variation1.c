#include <stdio.h>
#include <stdlib.h>

#define size 10

typedef struct{
    int elem[size];
    int count;
}List;

List initialize ();
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate (List L, int data);
List insertSorted(List L, int data);
void display(List L);

int main(){
    List L = initialize();

    L = insertPos(L, 5, 0);
    L = insertPos(L, 10, 1);
    L = insertPos(L, 15, 2);
    L = insertPos(L, 30, 1);
    L = insertPos(L, 100, 9);
    display(L);

    printf("\nAfter Deletion\n");
    L = deletePos(L, 2);
    display(L);

    printf("\nLocate number\n");
    int found = locate(L, 20);
    (found != -1)? printf("Data found on index %d\n", found): printf("Data not found!\n");
    display(L);

    printf("\nInsert Sorted\n");
    L = insertSorted(L, 30);
    L = insertSorted(L, 20);
    L = insertSorted(L, 1);
    L = insertSorted(L, 2);
    L = insertSorted(L, 3);
    L = insertSorted(L, 100);
    L = insertSorted(L, 5);
    L = insertSorted(L, 6);
    L = insertSorted(L, 7);
    display(L);

    printf("\nDeleting!\n");
    L = deletePos(L, 2);
    display(L);

    return 0;
}

void display(List L){
    printf("List:\n");
    for(int i = 0; i < size; i++){
        printf("%d ", L.elem[i]);
    }
    printf("\nCount = %d\n", L.count);
}

List initialize (){
    List L;
    for(int i = 0; i < size; i++){
        L.elem[i] = -1;
    }
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position){
    int count = L.count;

    if(position >= 0 && position <= count && count < size){

        // shift RIGHT starting from last used index (count-1)
        for(int i = count; i > position; i--){
            L.elem[i] = L.elem[i-1];
        }

        L.elem[position] = data;
        L.count = count + 1;

    } else {
        printf("Cannot insert %d at position %d\n", data, position);
    }
    return L;
}

List deletePos(List L, int position){
    int count = L.count;

    if(count != 0 && position >= 0 && position < count){

        // shift LEFT only within used elements
        for(int i = position; i < count - 1; i++){
            L.elem[i] = L.elem[i+1];
        }

        // clear last used slot
        L.elem[count - 1] = -1;
        L.count = count - 1;

    } else {
        printf("Cannot delete from position %d\n", position);
    }
    return L;
}

int locate (List L, int data){
    printf("Looking for %d: ", data);
    for(int i = 0; i < L.count; i++){
        if(L.elem[i] == data){
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data){
    int count = L.count;

    if(count < size){
        int i = count - 1;
        while(i >= 0 && L.elem[i] > data){
            L.elem[i + 1] = L.elem[i];
            i--;
        }
        L.elem[i + 1] = data;
        L.count = count + 1;
    } else {
        printf("List is full, can not insert %d!\n", data);
    }
    return L;
}
