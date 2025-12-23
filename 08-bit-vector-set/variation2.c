// Variation 2 - Bit fields

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned int field : 8;
}Set;

void initialize(Set *set);
void insert(Set *set, int element);
void Delete(Set *set, int element);
bool find(Set *set, int element);
Set Union(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(Set set);

int main (){
    Set A;
    initialize(&A);

    insert(&A, 1);
    insert(&A, 0);
    insert(&A, 7);

    Delete(&A, 0);

    (find(&A, 7)) ? printf("Element found.\n") : printf("Element not found.\n");

    display(A);
    return 0;
}

void initialize(Set *set){
    set->field = 0;
}

void insert(Set *set, int element){
    if(element >= 0 && element < 8){
        Set B;
        initialize(&B);
        B.field = (unsigned int)(1 << element);
        *set = Union(*set, B);
    } else {
        printf("Unable to insert.\n");
    }
}

void Delete(Set *set, int element){
    if(element >= 0 && element < 8){
        Set B;
        initialize(&B);
        B.field = (unsigned int)(1 << element);
        *set = difference(*set, B);
    } else {
        printf("Unable to delete.\n");
    }
}

bool find(Set *set, int element){
    if(element >= 0 && element < 8){
        unsigned int mask = (unsigned int)(1 << element);
        return (set->field & mask) != 0;
    }
    return false;
}

Set Union(Set A, Set B){
    Set C;
    initialize(&C);
    C.field = A.field | B.field;
    return C;
}

Set intersection(Set A, Set B){
    Set C;
    initialize(&C);
    C.field = A.field & B.field;
    return C;
}

Set difference(Set A, Set B){
    Set C;
    initialize(&C);
    C.field = A.field & ~(B.field);
    return C;
}

void display(Set set){
    printf("\n--- Display ---\n");
    printf("Set A = %d\n", set.field);

    printf("Binary of set:\n");
    for(int i = 7; i >= 0; i--){
        printf("%d ", (set.field & (1 << i)) ? 1 : 0);
    }

    printf("\nElements of set:\n");
    for(int i = 0; i < 8; i++){
        if(set.field & (1 << i)){
            printf("%d ", i);
        }
    }
    printf("\n");
}
