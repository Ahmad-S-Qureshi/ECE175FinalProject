#include <stdio.h>
#include <string.h>


void initializeData(LinkedListData data) {
    data.head = NULL;
    data.tail = NULL;
}

void initializeNode(Node *prevNode, Node *toBeInitialized, char *data) {
    if (prevNode != toBeInitialized) {
        prevNode->nextPtr = toBeInitialized;
    } else {
        prevNode->prevPtr = NULL;
    }
    toBeInitialized->nextPtr = NULL;
    strcpy((toBeInitialized->data).string, data);
}

Node *getElementFromIndex(LinkedListData *data, int index) {
    Node *currNode = data->head;
    for(int i = 0; i < index; i++) {
        currNode = currNode->nextPtr;
    }
    return currNode;
}

void insertElementToList(LinkedListData *data, int indexBefore) {
    
}

void printNode(Node* nodeToBePrinted) {
    printf("%s", nodeToBePrinted->data.string);
}

void printList(LinkedListData data) {
    Node *currNode = data.head;
    while (currNode != NULL) {
        printNode(currNode);
        currNode = currNode->nextPtr;
    }
}




void shuffle(LinkedListData *data) {
    
}

int getLinkedListLength(LinkedListData *data) {
    int returnVal = 0;
    Node *temp = data->head;
    while(temp != NULL) {
        returnVal++;
        temp = temp->nextPtr;
    }
    return returnVal ;
}

Node *moveDiscardToDraw(LinkedListData discardData, LinkedListData drawData) {
    Node *prevNode = drawData.head;
    for(int i = getLinkedListLength(&discardData); i>0; i--) {
        Node *currNode = discardData.head;
        currNode = currNode->nextPtr;
        //int randNum = (rand()%(i-2)) + 1;
        int j = 0;
        for(j = 0; j<0/*i-2*/; j++) {
            currNode = currNode->nextPtr;
        }
        if(i>-1) {
            currNode->prevPtr->nextPtr = currNode->nextPtr;
            currNode->nextPtr->prevPtr = currNode->prevPtr;
            currNode->prevPtr = prevNode;
            currNode->prevPtr = prevNode;
            currNode->nextPtr = NULL;
            prevNode = currNode;
            printList(discardData);
            printList(drawData);
        }
    }
    return prevNode;
}

// void swapNodes(LinkedListData *data, int lengthFromHeadToNode1, int lengthFromHeadToNode2) {
//     Node *node1 = data->head;
//     for(int i = 0; i<lengthFromHeadToNode1; i++) {
//         node1 = node1->nextPtr;
//     }
//     Node *node2 = data->head;
//     for(int i = 0; i<lengthFromHeadToNode2; i++) {
//         node2 = node2->nextPtr;
//     }
//     Node *node2cpy = node2;
//     Node *node1cpy = node1;

//     Node *tempPtr = (Node*)malloc(sizeof(Node));
//     node1->prevPtr->nextPtr=node2;
//     node2->prevPtr->nextPtr=node1;
//     node1->nextPtr->prevPtr=node2;
//     node2->nextPtr->prevPtr=node1;
//     tempPtr = node1->prevPtr;
//     node1->prevPtr = node2->prevPtr;
//     node2->prevPtr = tempPtr;
//     tempPtr = node1->nextPtr;
//     node1->nextPtr = node2->nextPtr;
//     node2->nextPtr = tempPtr;
//     free(tempPtr);
// }