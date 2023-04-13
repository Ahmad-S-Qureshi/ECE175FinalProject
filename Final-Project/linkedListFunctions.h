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
        printf("%s", currNode->data);
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

void shuffle(LinkedListData *data) {
    
}

int getLinkedListLength(LinkedListData *data) {
    int returnVal = 0;
    Node *temp = data->head;
    while(temp->nextPtr != NULL) {
        returnVal++;
        temp = temp->nextPtr;
    }
    return returnVal-1;
}

void swapNodes(LinkedListData *data, int lengthFromHeadToNode1, int lengthFromHeadToNode2) {
    Node *node1 = data->head;
    for(int i = 0; i<lengthFromHeadToNode1; i++) {
        node1 = node1->nextPtr;
    }
    Node *node2 = data->head;
    for(int i = 0; i<lengthFromHeadToNode2; i++) {
        node2 = node2->nextPtr;
    }
    Node *node2cpy = node2;
    Node *node1cpy = node1;

    Node *tempPtr = (Node*)malloc(sizeof(Node));
    tempPtr = node1->prevPtr;
    node1->prevPtr = node2->prevPtr;
    node2->prevPtr = tempPtr;
    tempPtr = node1->nextPtr;
    node1->nextPtr = node2->nextPtr;
    node2->nextPtr = tempPtr;
}