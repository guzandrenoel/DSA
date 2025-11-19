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
    // - an empty spot (*trav == NULL)
    // - or a node with the same value (ignore duplicates)
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
        Node* temp = (Node*)malloc(sizeof(Node));  
        temp->elem = value;                        
        temp->LC = NULL;                         
        temp->RC = NULL;                            
        *trav = temp;                               
    }
}

// Simple inorder traversal to show the tree contents
void inorder(BST B) {
    if (B != NULL) {                        
        inorder(B->LC);
        printf("%d ", B->elem);            
        inorder(B->RC);
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
