#include <stdio.h>
#include <string.h>

// Sets head and tail to null, not necessary but seemed to help
void initializeData(LinkedListData data) {
    data.head = NULL;
    data.tail = NULL;
}

// Initializes a node with data, only used by head nodes
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

// Iterates through a list and grabs a node at the n-th index
Node *getElementFromIndex(LinkedListData *data, int index) {
    Node *currNode = data->head;
    for(int i = 0; i < index; i++) {
        currNode = currNode->nextPtr;
    }
    return currNode;
}

// Unnessesary? We seem to just need to swap
void insertElementToList(LinkedListData *data, int indexBefore) {
    
}

// Prints data within a node
void printNode(Node* nodeToBePrinted) {
    if(strcmp(nodeToBePrinted->data.color, "Yellow") == 0) {
        printf("\e[0;33m");
    } else if (strcmp(nodeToBePrinted->data.color, "Red") == 0){
        printf("\e[0;31m");
    } else if (strcmp(nodeToBePrinted->data.color, "Green") == 0){
        printf("\e[0;32m");
    } else if (strcmp(nodeToBePrinted->data.color, "Blue") == 0) {
        printf("\e[0;34m");
    } else {
        printf("\e[0;37m");
    }
    
    
    if(nodeToBePrinted->data.value >0) {
        printf("\n-----------------\n|\t\t|\n|\t\t|\n|\t\t|\n|\t\t|\n|\t%d\t|\n|\t\t|\n|\t\t|\n|\t\t|\n-----------------\n\n\n", nodeToBePrinted->data.value);
    } else {
        printf("-----------------\n|\t\t|\n|\t\t|\n|\t\t|\n|\t\t|\n|\t%c\t|\n|\t\t|\n|\t\t|\n|\t\t|\n-----------------\n\n\n", '#');
    }
}

// Iterates across an entire list and prints it
void printList(LinkedListData data) {
    Node *currNode = data.head;
    while (currNode != NULL) {
        if(currNode->data.value >=0) {
            printNode(currNode);
        }
        currNode = currNode->nextPtr;
    }
    printf("\e[0m");
}

// Prints a list backwards in case we want to, ensures backwards links
void printListBackwards(LinkedListData data) {
    Node *currNode = data.tail;
    while (currNode != NULL) {
        if(currNode->data.value >=0) {
            printNode(currNode);
        }
        currNode = currNode->nextPtr;
    }
}

// Just swaps the data, that's it
void swapNodes(Node *node1, Node *node2) {
    card temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

// Iterates until null and returns length of list
int getLinkedListLength(LinkedListData *data) {
    int returnVal = 0;
    Node *temp = data->head;
    while(temp != NULL) {
        returnVal++;
        temp = temp->nextPtr;
    }
    return returnVal;
}

// Moves a node into another linked list, to be used in gameplay
Node *moveToOtherLinkedList(LinkedListData *oldListData, LinkedListData *newListData, Node *oldNode) {
    oldNode->prevPtr->nextPtr = oldNode->nextPtr;
    oldNode->nextPtr->prevPtr = oldNode->prevPtr;
    Node *newHead = newListData->head;
    oldNode->nextPtr = newHead->nextPtr;
    newHead->nextPtr = oldNode;
    oldNode->prevPtr = newHead; 
}

// idk if this or the above works UPDATE: both work
void moveNode(LinkedListData *fromData, LinkedListData *toData, Node *toBeMoved) {
    toBeMoved->prevPtr->nextPtr = toBeMoved->nextPtr;
    toBeMoved->nextPtr->prevPtr = toBeMoved->prevPtr;
    toBeMoved->nextPtr = toData->head->nextPtr;
    toData->head->nextPtr = toBeMoved;
    toBeMoved->prevPtr = toData->head;
}

// Moves entire discard pile to draw pile, merge discards beforehand
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

// Shuffles the deck 50 times because why not
void shuffle(LinkedListData *data) {
    for(int timesToShuffle = 0; timesToShuffle<50; timesToShuffle++) {
        for(int i = 0; i<getLinkedListLength(data); i++) {
            Node* node1 = getElementFromIndex(data, rand()%(getLinkedListLength(data)-2) + 1);
            Node* node2 = getElementFromIndex(data, rand()%(getLinkedListLength(data)-2) + 1);
            swapNodes(node1, node2);
        }
    }
}

void drawFromDrawPile(LinkedListData playerHand, LinkedListData drawData) {
    moveNode(&drawData, &playerHand, drawData.head->nextPtr);
}

void updateListss(LinkedListData playerHand, LinkedListData discardPlayingOn, Node moveVal1, Node moveVal2) {

}

void turns(LinkedListData playerHand, LinkedListData discardPlayingOn, Node moveVal1, Node moveVal2) {

}

//Lame
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