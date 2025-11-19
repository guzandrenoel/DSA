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

// Insert using pointer-to-pointer and loop
void insert(BST *T, int value) {
    BST *trav;

    for (trav = T; *trav != NULL && (*trav)->elem != value; ) {
        if (value < (*trav)->elem) trav = &(*trav)->LC;
        else if (value > (*trav)->elem) trav = &(*trav)->RC;
        else break;
    }

    if (*trav == NULL) {
        Node *temp = malloc(sizeof(Node));
        temp->elem = value;
        temp->LC = temp->RC = NULL;
        *trav = temp;
    }
}

// Iterative search
BST search(BST T, int value) {
    while (T != NULL && T->elem != value) {
        if (value < T->elem) T = T->LC;
        else T = T->RC;
    }
    return T;
}

// Traversals
void inorder(BST T) {
    if (T) {
        inorder(T->LC);
        printf("%d ", T->elem);
        inorder(T->RC);
    }
}

void preorder(BST T) {
    if (T) {
        printf("%d ", T->elem);
        preorder(T->LC);
        preorder(T->RC);
    }
}

void postorder(BST T) {
    if (T) {
        postorder(T->LC);
        postorder(T->RC);
        printf("%d ", T->elem);
    }
}

// Delete node from BST
void deleteNode(BST *T, int value) {
    BST *trav = T;

    while (*trav != NULL && (*trav)->elem != value) {
        if (value < (*trav)->elem) trav = &(*trav)->LC;
        else trav = &(*trav)->RC;
    }

    if (*trav == NULL) return;

    Node *target = *trav;

    if (target->LC == NULL || target->RC == NULL) {
        Node *child = target->LC ? target->LC : target->RC;
        *trav = child;
        free(target);
    } 
    else {
        BST *succ = &target->RC;
        while ((*succ)->LC != NULL) succ = &(*succ)->LC;

        target->elem = (*succ)->elem;

        Node *temp = *succ;
        Node *child = temp->RC;
        *succ = child;
        free(temp);
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

    printf("Inorder   : ");
    inorder(root);
    printf("\n");

    printf("Preorder  : ");
    preorder(root);
    printf("\n");

    printf("Postorder : ");
    postorder(root);
    printf("\n");

    // Search example
    BST f = search(root, 3);
    printf("Search 3: %s\n", f ? "Found" : "Not found");

    // Delete example
    deleteNode(&root, 2);
    printf("After deleting 2 (inorder): ");
    inorder(root);
    printf("\n");

    return 0;
}
