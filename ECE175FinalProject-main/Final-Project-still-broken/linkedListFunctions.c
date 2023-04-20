#include <stdio.h>
#include <string.h>


void initializeData(LinkedListData data) {
    data.head = NULL;
    data.tail = NULL;
}

void initializeNode(Node *prevNode, Node *toBeInitialized, char *color, int val) {
    if (prevNode != toBeInitialized) {
        prevNode->nextPtr = toBeInitialized;
    } else {
        prevNode->prevPtr = NULL;
    }
    toBeInitialized->nextPtr = NULL;
    strcpy((toBeInitialized->data).color, color);
    toBeInitialized->data.value = val;
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
    printf("%d of color %s\n", nodeToBePrinted->data.value, nodeToBePrinted->data.color);
}

void printList(LinkedListData data) {
    Node *currNode = data.head;
    while (currNode != NULL) {
        printNode(currNode);
        currNode = currNode->nextPtr;
    }
}

void printListBackwards(LinkedListData data) {
    Node *currNode = data.tail;
    while (currNode != NULL) {
        printNode(currNode);
        currNode = currNode->prevPtr;
    }
}


void swapNodes(Node *node1, Node *node2) {
    card temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}



int getLinkedListLength(LinkedListData *data) {
    int returnVal = 0;
    Node *temp = data->head;
    while(temp != NULL) {
        returnVal++;
        temp = temp->nextPtr;
    }
    return returnVal;
}

Node *moveToOtherLinkedList(LinkedListData *oldListData, LinkedListData *newListData, Node *oldNode) {
    oldNode->prevPtr->nextPtr = oldNode->nextPtr;
    oldNode->nextPtr->prevPtr = oldNode->prevPtr;
    Node *newHead = newListData->head;
    oldNode->nextPtr = newHead->nextPtr;
    newHead->nextPtr = oldNode;
    oldNode->prevPtr = newHead; 
}

void moveNode(LinkedListData *fromData, LinkedListData *toData, Node *toBeMoved) {
    toBeMoved->prevPtr->nextPtr = toBeMoved->nextPtr;
    toBeMoved->nextPtr->prevPtr = toBeMoved->prevPtr;
    toBeMoved->nextPtr = toData->head->nextPtr;
    toData->head->nextPtr = toBeMoved;
    toBeMoved->prevPtr = toData->head;
}

Node *moveDiscardToDraw(LinkedListData discardData, LinkedListData drawData) {
    Node *prevNode = drawData.head;
    for(int i = getLinkedListLength(&discardData); i>2; i--) {
        Node *currNode = discardData.head;
        currNode = currNode->nextPtr;
        currNode->prevPtr->nextPtr = currNode->nextPtr;
        currNode->nextPtr->prevPtr = currNode->prevPtr;
        prevNode->nextPtr = currNode;
        currNode->prevPtr = prevNode;
        currNode->nextPtr = NULL;
        prevNode = currNode;
    }
    discardData.tail->prevPtr=prevNode;
    prevNode->nextPtr = discardData.tail;
    strcpy(discardData.tail->data.color, "tail draw");
    prevNode->data.value = -10;
    return prevNode;
}

void shuffle(LinkedListData *data) {
    for(int timesToShuffle = 0; timesToShuffle<50; timesToShuffle++) {
        for(int i = 0; i<getLinkedListLength(data); i++) {
            Node* node1 = getElementFromIndex(data, rand()%(getLinkedListLength(data)-2) + 1);
            Node* node2 = getElementFromIndex(data, rand()%(getLinkedListLength(data)-2) + 1);
            swapNodes(node1, node2);
        }
    }
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