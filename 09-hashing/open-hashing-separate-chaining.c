#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 11

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[TABLE_SIZE];
} HashTable;

int hash(int key) { return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE; }

void init(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) ht->buckets[i] = NULL;
}

Node* createNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    n->key = key;
    n->next = NULL;
    return n;
}

bool search(HashTable *ht, int key) {
    int h = hash(key);
    for (Node *t = ht->buckets[h]; t != NULL; t = t->next) {
        if (t->key == key) return true;
    }
    return false;
}

bool insert(HashTable *ht, int key) {
    if (search(ht, key)) return false;

    int h = hash(key);
    Node *n = createNode(key);
    if (!n) return false;

    n->next = ht->buckets[h];
    ht->buckets[h] = n;
    return true;
}

bool removeKey(HashTable *ht, int key) {
    int h = hash(key);
    Node **trav = &ht->buckets[h];

    while (*trav != NULL && (*trav)->key != key) {
        trav = &(*trav)->next;
    }
    if (*trav == NULL) return false;

    Node *temp = *trav;
    *trav = temp->next;
    free(temp);
    return true;
}

void display(HashTable *ht) {
    printf("\nSeparate Chaining Table\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        for (Node *t = ht->buckets[i]; t != NULL; t = t->next) {
            printf("%d", t->key);
            if (t->next) printf(" -> ");
        }
        printf("\n");
    }
}

void destroy(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *t = ht->buckets[i];
        while (t) {
            Node *next = t->next;
            free(t);
            t = next;
        }
        ht->buckets[i] = NULL;
    }
}

int main() {
    HashTable ht;
    init(&ht);

    insert(&ht, 10);
    insert(&ht, 21);
    insert(&ht, 32);
    insert(&ht, 43);
    insert(&ht, 54);
    insert(&ht, 65);

    display(&ht);

    printf("\nsearch 43 -> %s\n", search(&ht, 43) ? "found" : "not found");
    printf("remove 43 -> %s\n", removeKey(&ht, 43) ? "ok" : "fail");

    display(&ht);
    destroy(&ht);
    return 0;
}
