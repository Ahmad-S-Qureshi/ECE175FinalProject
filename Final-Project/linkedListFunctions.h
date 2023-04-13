#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;
    char data[50];
} Node;

typedef struct linkedListData {
    Node* head;
    Node* tail;
} LinkedListData;

void initializeData(LinkedListData data) {
    data.head = NULL;
    data.tail = NULL;
}

void initializeNode(Node *prevNode, Node *toBeInitialized, char *data) {
    if (prevNode != toBeInitialized) {
        prevNode->nextPtr = toBeInitialized;
    }
    toBeInitialized->nextPtr = NULL;
    strcpy(toBeInitialized->data, data);
}

void printList(LinkedListData data) {
    Node *currNode = data.head;
    while (currNode->nextPtr != NULL) {
        printf("%s\n", currNode->data);
        currNode = currNode->nextPtr;
    }
    printf("%s\n", currNode->data);

}

// void createLinkedListHead(LinkedListData *data) {
//     Node temp;
//     temp.prevPtr = NULL;

//     return temp;
// }

// Node createLinkedListNotHead(LinkedListData *data, Node *prevPtr) {
//     Node temp;
//     temp.prevPtr = prevPtr;
//     prevPtr->nextPtr = &temp;
//     temp.nextPtr = NULL;
//     return temp;
// }

void shuffle(Node *headPtr) {
    
}

int getLinkedListLength(LinkedListData *data) {
    int returnVal = 0;
    Node *temp = data->head;
    while(temp->nextPtr != NULL) {
        returnVal++;
        temp = temp->nextPtr;
    }
    return returnVal;
}

// void swapNodes(Node *node1, Node *node2) {
//     prevPtr1 = node1->prevPtr;
//     prevPtr2 = node2->prevPtr
//     temp = prevPtr1;
//     node1->prevPtr = prevPtr2;
//     node2->prevPtr = temp;
// }