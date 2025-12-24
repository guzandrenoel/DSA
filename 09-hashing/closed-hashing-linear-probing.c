#include <stdio.h>
#include <stdbool.h>

#define TABLE_SIZE 11

typedef enum { EMPTY, OCCUPIED, DELETED } SlotState;

typedef struct {
    int key;
    SlotState state;
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} HashTable;

int hash(int key) { return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE; }

void init(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i].key = 0;
        ht->table[i].state = EMPTY;
    }
}

bool insert(HashTable *ht, int key) {
    int h = hash(key);
    int firstDeleted = -1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (h + i) % TABLE_SIZE;

        if (ht->table[idx].state == OCCUPIED && ht->table[idx].key == key) {
            return false; // no duplicates
        }
        if (ht->table[idx].state == DELETED && firstDeleted == -1) {
            firstDeleted = idx;
        }
        if (ht->table[idx].state == EMPTY) {
            if (firstDeleted != -1) idx = firstDeleted;
            ht->table[idx].key = key;
            ht->table[idx].state = OCCUPIED;
            return true;
        }
    }

    if (firstDeleted != -1) {
        ht->table[firstDeleted].key = key;
        ht->table[firstDeleted].state = OCCUPIED;
        return true;
    }

    return false; // full
}

int search(HashTable *ht, int key) {
    int h = hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (h + i) % TABLE_SIZE;

        if (ht->table[idx].state == EMPTY) return -1;
        if (ht->table[idx].state == OCCUPIED && ht->table[idx].key == key) return idx;
    }
    return -1;
}

bool removeKey(HashTable *ht, int key) {
    int idx = search(ht, key);
    if (idx == -1) return false;
    ht->table[idx].state = DELETED;
    return true;
}

void display(HashTable *ht) {
    printf("\nIndex | Key  | State\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%5d | %4d | ", i, ht->table[i].key);
        if (ht->table[i].state == EMPTY) printf("EMPTY\n");
        else if (ht->table[i].state == OCCUPIED) printf("OCCUPIED\n");
        else printf("DELETED\n");
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

    display(&ht);

    printf("\nsearch 32 -> %d\n", search(&ht, 32));
    printf("remove 32 -> %s\n", removeKey(&ht, 32) ? "ok" : "fail");
    printf("search 32 -> %d\n", search(&ht, 32));

    display(&ht);

    return 0;
}
