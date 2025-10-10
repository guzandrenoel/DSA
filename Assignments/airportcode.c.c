#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20
#define PRIMARY_SIZE (MAX/2)

typedef char Code[4];

typedef struct{
    Code code;
    int next;
}Cell, HeapSpace[MAX];

typedef struct{
    HeapSpace H;
    int avail;
}VHeap;

void initialize(VHeap *V);
int allocSpace(VHeap *V);
void deallocSpace(VHeap *V, int index);
int hashCode(Code code);
void insertAirport(VHeap *V, Code code);
bool searchAirport(VHeap V, Code code);
void deleteAirport(VHeap *V, Code code);
void display(VHeap V);
void displayHashTable(VHeap V);

int main(){
    VHeap V;
    initialize(&V);
    
    Code setA[] = {"JFK", "LAX", "SFO", "CDG", "LHR", "NRT", "ATL", "DXB", "PEK", "MIA", "SYD", "ORD"};
    int numAirports = sizeof(setA) / sizeof(setA[0]);
    
    printf("Inserting %d airports:\n", numAirports);
    for(int i = 0; i < numAirports; i++){
        printf("Adding %s... ", setA[i]);
        insertAirport(&V, setA[i]);
        printf("Done.\n");
    }
    
    printf("\n");
    displayHashTable(V);
    printf("\n");
    display(V);
    
    printf("\n");
    Code testCodes[] = {"JFK", "LAX", "XXX", "SFO"};
    for(int i = 0; i < 4; i++){
        if(searchAirport(V, testCodes[i])){
            printf("'%s' found in hash table.\n", testCodes[i]);
        } else {
            printf("'%s' NOT found in hash table.\n", testCodes[i]);
        }
    }
    
    return 0;
}

void initialize(VHeap *V){
    for(int i = 0; i < PRIMARY_SIZE; i++){
        strcpy(V->H[i].code, "");
        V->H[i].next = -1;
    }
    
    V->avail = PRIMARY_SIZE;
    for(int i = PRIMARY_SIZE; i < MAX - 1; i++){
        strcpy(V->H[i].code, "");
        V->H[i].next = i + 1;
    }
    strcpy(V->H[MAX - 1].code, "");
    V->H[MAX - 1].next = -1;
}

int allocSpace(VHeap *V){
    int ret = V->avail;
    if(ret != -1){
        V->avail = V->H[ret].next;
        V->H[ret].next = -1;
    }
    return ret;
}

void deallocSpace(VHeap *V, int index){
    if(index >= PRIMARY_SIZE && index < MAX){
        strcpy(V->H[index].code, "");
        V->H[index].next = V->avail;
        V->avail = index;
    }
}

int hashCode(Code code){
    int hash = 0;
    for(int i = 0; code[i] != '\0' && i < 3; i++){
        hash = (hash * 31 + code[i]) % PRIMARY_SIZE;
    }
    return hash;
}

void insertAirport(VHeap *V, Code code){
    int hash = hashCode(code);
    
    if(strcmp(V->H[hash].code, "") == 0){
        strcpy(V->H[hash].code, code);
    } else {
        int newCell = allocSpace(V);
        if(newCell != -1){
            strcpy(V->H[newCell].code, code);
            
            int *curr = &V->H[hash].next;
            while(*curr != -1){
                curr = &V->H[*curr].next;
            }
            *curr = newCell;
        } else {
            printf("Error: No space available to insert airport '%s'\n", code);
        }
    }
}

bool searchAirport(VHeap V, Code code){
    int hash = hashCode(code);
    int current = hash;
    
    while(current != -1){
        if(strcmp(V.H[current].code, code) == 0){
            return true;
        }
        current = V.H[current].next;
    }
    return false;
}

void display(VHeap V){
    printf("--- Display ---\n");
    printf("Avail = %d\n", V.avail);
    printf("Primary List:\n");
    printf("%5s|%-5s|%-5s\n", "index", "code", "next");
    for(int i = 0; i < PRIMARY_SIZE; i++){
        printf("%5d|%-5s|%-5d \n", i, V.H[i].code, V.H[i].next);
    }
    printf("Secondary List:\n");
    printf("%5s|%-5s|%-5s\n", "index", "code", "next");
    for(int i = PRIMARY_SIZE; i < MAX; i++){
        printf("%5d|%-5s|%-5d \n", i, V.H[i].code, V.H[i].next);
    }
}

void displayHashTable(VHeap V){
    printf("--- Hash Table ---\n");
    for(int i = 0; i < PRIMARY_SIZE; i++){
        printf("[%d]: %s", i, V.H[i].code);
        int current = V.H[i].next;
        while(current != -1){
            printf(" -> %s", V.H[current].code);
            current = V.H[current].next;
        }
        printf("\n");
    }
}