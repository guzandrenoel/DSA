#include <stdio.h>
#include <stdlib.h>

struct node {
    int elem;
    struct node *LC;
    struct node *RC; 
};
typedef struct node Node;
typedef Node* BST;

BST root = NULL;

void insert(BST *T, int value) {
    BST *trav;

    // Traverse down the tree until we find:
    // - an empty spot (*trav == NULL), or
    // - a node with the same value (do nothing in that case)
    for (trav = T; *trav != NULL && (*trav)->elem != value; ) {
        if (value < (*trav)->elem) {
            trav = &(*trav)->LC;
        } else if (value > (*trav)->elem) {
            trav = &(*trav)->RC;
        } else {
            break;
        }
    }

    if (*trav == NULL) {
        *trav = (Node*)malloc(sizeof(Node));
        if (*trav == NULL) return;    
        (*trav)->elem = value;
        (*trav)->LC = (*trav)->RC = NULL;
    }
}

// Simple inorder traversal to show the tree contents
void inorder(BST T) {
    if (T != NULL) {
        inorder(T->LC);
        printf("%d ", T->elem);
        inorder(T->RC);
    }
}

int main(void) {
    insert(&root, 5);
    insert(&root, 2);
    insert(&root, 8);
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 9);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
