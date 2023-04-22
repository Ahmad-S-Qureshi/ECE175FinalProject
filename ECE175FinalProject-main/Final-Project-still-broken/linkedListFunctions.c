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
    int cardNum = 1;
    while (currNode != NULL) {
        if(currNode->data.value >=0) {
            printf("Card Number %d\n", cardNum);
            cardNum++;
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

int getSumOfHand(LinkedListData data) {
    Node *currNode = data.head;
    int returnVal;
    while (currNode != NULL) {
        if(currNode->data.value >=0) {
            if(currNode->data.value > 0 && currNode->data.value != 2) {
                returnVal+=currNode->data.value;
            } else if (currNode->data.value == 2) {
                returnVal += 40;
            } else if (currNode->data.value == 0) {
                returnVal +=10;
            }
        }
        currNode = currNode->nextPtr;
    }
    printf("\e[0m");
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

// idk if this or the above works UPDATE: both work but need the node to be immediately after the head
void moveNode(LinkedListData *fromData, LinkedListData *toData, Node *toBeMoved) {
    //swapNodes(fromData->head->nextPtr, toBeMoved);
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

int updateListsForTurnWithTwoCards(LinkedListData playerHand, Node discardPlayingOn, Node moveVal1, Node moveVal2) {

}

//Return 1 if color match, 0 if not color match but valid move, -1 if invalid move
int updateListsForTurnWithOneCard(LinkedListData playerHand, Node discardPlayingOn, Node *moveVal1, LinkedListData playPiles, LinkedListData discardPile) {
    if((moveVal1->data.value == discardPlayingOn.data.value || moveVal1->data.value == 0 || discardPlayingOn.data.value == 0) && strcmp(moveVal1->data.color, discardPlayingOn.data.color) == 0) {
        printf("Single Color Match!\n");
        //swapNodes(playerHand.head->nextPtr, moveVal1);
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn);
        moveVal1->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        return 1;
    } else if ((moveVal1->data.value == discardPlayingOn.data.value || moveVal1->data.value == 0 || discardPlayingOn.data.value == 0)){
        printf("Move processed successfully\n");
        //swapNodes(playerHand.head->nextPtr, moveVal1); //Works
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn); //
        moveVal1->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        return 0;
    } else {
        printf("Invalid move, try again!\n");
        return -1;
    }
}

void emptyList(LinkedListData toBeVanished) {
    Node *currNode = toBeVanished.head;
    Node *prevNode = toBeVanished.head;
    currNode = currNode->nextPtr;
    while (currNode != NULL) {
        if(prevNode->data.value >=0) {
            free(prevNode);
        }
        prevNode = currNode;
        currNode = currNode->nextPtr;
    }
    toBeVanished.head->nextPtr=toBeVanished.tail;
    toBeVanished.head->prevPtr = NULL;
    toBeVanished.tail->prevPtr=toBeVanished.head;
    toBeVanished.tail->nextPtr = NULL;
}

int turns(LinkedListData playerHand, Node discardPlayingOn, LinkedListData drawData, LinkedListData playPiles, LinkedListData discardData) {
    //blah blah logic
    
    printf("Now playing on:\n");
    printNode(&discardPlayingOn);
    printf("Your cards are as follows: ");
    printList(playerHand);
    bool playPileComplete = false;

    while (!playPileComplete){
        int cardsToPlay = 0;
        printf("Enter how many cards you want to play on this card, 0 (draw), 1, or 2: ");
        scanf("%d", &cardsToPlay);

        if(cardsToPlay == 2) {
            int nodeIndex1 = 0;
            int nodeIndex2 = 0;
            printf("Enter the two cards in this form \"1 and 2\": ");
            scanf("%d and %d", &nodeIndex1, &nodeIndex2);
            updateListsForTurnWithTwoCards(playerHand, discardPlayingOn, *getElementFromIndex(&playerHand, nodeIndex1), *getElementFromIndex(&playerHand, nodeIndex2));
            playPileComplete = true;
        } else if (cardsToPlay == 1) {
            int nodeIndex = 0;
            printf("Enter the card in this form \"1\":");
            scanf("%d", &nodeIndex);

            if(updateListsForTurnWithOneCard(playerHand, discardPlayingOn, getElementFromIndex(&playerHand, nodeIndex), playPiles, discardData) >= 0){
                playPileComplete = true;
            }
        } else if (cardsToPlay == 0) {
            drawFromDrawPile(playerHand, drawData);
            playPileComplete = true;
        } else {
            printf("Invalid Input, try again \n");
        }
    }
    return getLinkedListLength(&playerHand);
}

void updateScore(PlayerHand winner, LinkedListData aLoser) {
    winner.score+=getSumOfHand(aLoser);
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