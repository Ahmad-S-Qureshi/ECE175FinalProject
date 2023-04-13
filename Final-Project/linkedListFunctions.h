#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;

} Node;

void createLinkedListHead() {
    Node temp;
    temp->prevPtr = NULL;
    return temp;
}

void createLinkedListAtEnd(Node *headptr, Node *finalptr) {
    Node temp;
    temp->prevPtr = finalptr;
    temp->nextPtr = NULL;
    return temp;
}

void shuffle(Node *headPtr) {
    
}

int getLinkedListLength(Node *headPtr) {
    int returnVal = 0;
    while(headPtr->nextPtr != NULL) {
        returnVal++;
    }
    return returnVal;
}

void swapNodes(Node *node1, Node *node2) {
    prevPtr1 = node1->prevPtr;
    prevPtr2 = node2->prevPtr
    temp = prevPtr1;
    node1->prevPtr = prevPtr2;
    node2->prevPtr = temp;
}