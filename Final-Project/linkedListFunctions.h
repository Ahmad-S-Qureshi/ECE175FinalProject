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

void createLinkedListTail(Node headptr, Node finalptr) {
    Node temp;
    temp->prevPtr = finalptr;
    temp->nextPtr = NULL;
    return temp;
}

void nodeInsertAfter(Node* thisNode, Node* newNode) {
   Node* tmpNext = NULL;
   tmpNext = thisNode->nextNodePtr; // Remember next
   thisNode->nextNodePtr = newNode; // this -- new -- ?
   newNode->nextNodePtr = tmpNext;  // this -- new -- next
}

void shuffle(Node headPtr) {

}

void swapNodes(Node node1, Node node2) {
    prevPtr1 = node1->prevPtr;
    prevPtr2 = node2->prevPtr
    temp = prevPtr1;
    node1->prevPtr = prevPtr2;
    node2->prevPtr = temp;
}