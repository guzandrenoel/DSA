#include <stdio.h>
#include <stdbool.h>

void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void Delete(unsigned char *set, int element);
bool find(unsigned char set, int element);
void display(unsigned char set);

int main() {
    unsigned char A;
    initialize(&A);

    insert(&A, 1);
    insert(&A, 6);
    insert(&A, 7);

    Delete(&A, 1);

    find(A, 3) ? printf("found!\n") : printf("not found!\n");

    display(A);
    return 0;
}

void initialize(unsigned char *set){
    *set = 0;
}

void insert(unsigned char *set, int element){
    if(element >= 0 && element < 8){
        *set |= (unsigned char)(1 << element);   // set bit
    } else {
        printf("Element size is not valid.\n");
    }
}

void Delete(unsigned char *set, int element){
    if(element >= 0 && element < 8){
        *set &= (unsigned char)~(1 << element);  // clear bit
    } else {
        printf("Element size is not valid.\n");
    }
}

bool find(unsigned char set, int element){
    if(element >= 0 && element < 8){
        return (set & (unsigned char)(1 << element)) != 0;
    }
    return false;
}

void display(unsigned char set){
    printf("char A = %d\n", set);

    printf("Printing Binary:\n");
    for(int i = 7; i >= 0 ; i--){
        printf("%d ", (set & (1 << i)) ? 1 : 0);
    }

    printf("\nPrinting Elements:\n");
    for(int i = 0; i < 8 ; i++){
        if(set & (1 << i)){
            printf("%d ", i);
        }
    }
    printf("\n");
}
