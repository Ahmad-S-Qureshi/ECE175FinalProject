#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
typedef struct card_s {
    char color[10];
    int value;
    char action[15];
    struct card_s *pt;
} card;


typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;
    card data;
} Node;

typedef struct linkedListData {
    Node* head;
    Node* tail;
} LinkedListData;

typedef struct playerHand {
    LinkedListData dataStorage;
    int score;
} PlayerHand;

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
    int i = 0; 
    while(i < index) {
        currNode = currNode->nextPtr;
        if(currNode->data.value != -3) {
            i++;
        }
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
    printf("\e[0m");
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

int turnValid(Node moveVal1, Node moveVal2, Node discardPlayingOn) {
    
}

int doubleColorMatch() {
    
}

int updateListsForTurnWithTwoCards(LinkedListData playerHand, Node discardPlayingOn, Node *moveVal1, Node *moveVal2, LinkedListData playPiles, LinkedListData discardPile, LinkedListData drawData, int *cardsPlayed) {
    int sum = moveVal1->data.value + moveVal2->data.value;
    bool isAnyHashtag = (moveVal1->data.value==0 || moveVal2->data.value == 0 || discardPlayingOn.data.value == 0);
    bool isSameColor = (((strcmp(moveVal1->data.color, moveVal2->data.color) == 0) && (strcmp(moveVal1->data.color, discardPlayingOn.data.color) == 0)) ||
                        ((strcmp(moveVal1->data.color, "Wild") == 0) && (strcmp(moveVal2->data.color, discardPlayingOn.data.color) == 0)) ||
                        ((strcmp(moveVal2->data.color, "Wild") == 0) && (strcmp(moveVal1->data.color, discardPlayingOn.data.color) == 0)) ||
                        ((strcmp(discardPlayingOn.data.color, "Wild") == 0) && strcmp(moveVal2->data.color, moveVal1->data.color) == 0) ||
                        ((strcmp(discardPlayingOn.data.color, "Wild") == 0) && strcmp(moveVal2->data.color, moveVal1->data.color) == 0) ||
                        ((strcmp(discardPlayingOn.data.color, "Wild") == 0) + (strcmp(moveVal1->data.color, "Wild") == 0) + (strcmp(moveVal2->data.color, "Wild") == 0) > 1));
    if(((sum == discardPlayingOn.data.value) || (sum < discardPlayingOn.data.value && isAnyHashtag)) && isSameColor) {
        printf("Double Color Match!\n");
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn); 
        moveVal1->data.value = -3;
        moveVal2->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        
        doubleColorMatch();
        *cardsPlayed = *cardsPlayed+1;
        return 1;
    } else if (sum < discardPlayingOn.data.value && isAnyHashtag){
        printf("Move processed successfully\n");
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn); 
        moveVal1->data.value = -3;
        moveVal2->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        *cardsPlayed = *cardsPlayed+1;
        return 0;
    } else if (sum == discardPlayingOn.data.value) {
        printf("Move processed successfully\n");
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn); 
        moveVal1->data.value = -3;
        moveVal2->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        *cardsPlayed = (*cardsPlayed)-(*cardsPlayed)+1;
        return 0;
    } else {
        printf("Invalid move, try again!\n");
        return -1;
    }
}



int singleColorMatch() {

}

//Return 1 if color match, 0 if not color match but valid move, -1 if invalid move
int updateListsForTurnWithOneCard(LinkedListData playerHand, Node discardPlayingOn, Node *moveVal1, LinkedListData playPiles, LinkedListData discardPile, LinkedListData drawData, int *cardsPlayed) {
    if((moveVal1->data.value == discardPlayingOn.data.value || moveVal1->data.value == 0 || discardPlayingOn.data.value == 0) && strcmp(moveVal1->data.color, discardPlayingOn.data.color) == 0) {
        moveVal1->data.value = -3;
        while(getLinkedListLength(&playPiles) < 4) {
            drawFromDrawPile(playPiles, drawData);
        }
        printf("Single Color Match! Now select a second card to move into play\n");
        printf("Your cards are as follows\n");
        printList(playerHand);
        int cardToMoveIndex;
        printf("Enter a card as such \"1\": ");
        scanf("%d", &cardToMoveIndex);
        while (cardToMoveIndex> getLinkedListLength(&playerHand)){
            printf("Invalid Input, try again: ");
            scanf("%d", &cardToMoveIndex);
        }
        printf("Moving This card\n");
        printNode(getElementFromIndex(&playerHand, cardToMoveIndex));
        //swapNodes(playerHand.head->nextPtr, moveVal1);
        playPiles.head->nextPtr->data.value = -3;
        swapNodes(playPiles.head->nextPtr, getElementFromIndex(&playerHand, cardToMoveIndex));
        
        //drawFromDrawPile(discardPile, playPiles);
        *cardsPlayed = *cardsPlayed+1;
        return 0;
    } else if ((moveVal1->data.value == discardPlayingOn.data.value || moveVal1->data.value == 0 || discardPlayingOn.data.value == 0)){
        printf("Move processed successfully\n");
        //swapNodes(playerHand.head->nextPtr, moveVal1); //Works
        swapNodes(playPiles.head->nextPtr, &discardPlayingOn); //
        moveVal1->data.value = -3;
        drawFromDrawPile(discardPile, playPiles);
        *cardsPlayed = *cardsPlayed+1;
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

int turns(LinkedListData playerHand, Node discardPlayingOn, LinkedListData drawData, LinkedListData playPiles, LinkedListData discardData, int *cardsToPull, int *cardsPlayed) {
    //blah blah logic
    
    
    bool playPileComplete = false;

    while (!playPileComplete){
        printf("Now playing on:\n");
        printNode(&discardPlayingOn);
        printf("Your cards are as follows: \n");
        printList(playerHand);
        int cardsToPlay = 0;
        printf("Enter how many cards you want to play on this card, 0, 1, or 2: ");
        scanf("%d", &cardsToPlay);

        if(cardsToPlay == 2) {
            int nodeIndex1 = 0;
            int nodeIndex2 = 0;
            printf("Enter the two cards in this form \"1 and 2\": ");
            scanf("%d and %d", &nodeIndex1, &nodeIndex2);
            *cardsToPull = updateListsForTurnWithTwoCards(playerHand, discardPlayingOn, getElementFromIndex(&playerHand, nodeIndex1), getElementFromIndex(&playerHand, nodeIndex2), playPiles, discardData, drawData, cardsPlayed);
            if(*cardsToPull <= 0) {
                playPileComplete = true;
            }
        } else if (cardsToPlay == 1) {
            int nodeIndex = 0;
            printf("Enter the card in this form \"1\": ");
            scanf("%d", &nodeIndex);

            if(updateListsForTurnWithOneCard(playerHand, discardPlayingOn, getElementFromIndex(&playerHand, nodeIndex), playPiles, discardData, drawData, cardsPlayed) >= 0){
                playPileComplete = true;
            }
            *cardsToPull = cardsToPlay;

        } else if (cardsToPlay == 0) {
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


#include <stdio.h>
#include <stdlib.h>

// // Unused, for debugging to make sure every card was accounted for
// int getNumCards (FILE* fp) {
//     char line[50];
//     int numLines = 0;
//     while (fscanf(fp, "%s", line) != EOF){
//         numLines++;
//     }
//     fclose(fp);
//     fp = fopen("listOfCards.txt", "r");
//     return numLines;
// }

// Grabs every line assuming form int value space string color
Node *initializeLinkedListFromFile(LinkedListData data, FILE *fp) {
    // Prepares an empty node to fill in with details
    Node *toBeNext = (Node*)malloc(sizeof(Node));

    // Every the previous node is set to be the head, initialized elsewhere
    Node *prev = data.head;

    // A string to hold the color values
    char color[10];

    // An int to hold card number value (Wilds set to be zero)
    int value; 

    char nothing[20];

    // Reads in a link
    fscanf(fp, "%s %d %s\n", color, &value, nothing);
    if (value == 11) {
        value = 0;
    }
    if(strcmp(color, "black") ==0) {
        strcpy(color, "Wild");
    } else if (strcmp(color, "yellow") == 0) {
        strcpy(color, "Yellow");
    } else if (strcmp(color, "blue") == 0) { 
        strcpy(color, "Blue");
    } else if (strcmp(color, "green") == 0) { 
        strcpy(color, "Green");
    } else if (strcmp(color, "red") == 0) { 
        strcpy(color, "Red");
    }


    // Continually reads lines and makes nodes until the line is Tail
    while(!feof(fp)) {

        // Ensures a line has something in it
        if(strcmp("\n", color) != 0) {
            if (value == 11) {
                value = 0;
            }
            if(strcmp(color, "black") ==0) {
                strcpy(color, "Wild");
            } else if (strcmp(color, "yellow") == 0) {
                strcpy(color, "Yellow");
            } else if (strcmp(color, "blue") == 0) { 
                strcpy(color, "Blue");
            } else if (strcmp(color, "green") == 0) { 
                strcpy(color, "Green");
            } else if (strcmp(color, "red") == 0) { 
                strcpy(color, "Red");
    }

            // Makes the previous node point to the new one to be formed
            prev->nextPtr = toBeNext;

            // Makes sure the next pointer is null (unnesscesary but worth doing)
            toBeNext->nextPtr = NULL;

            // Makes the new node point to the last node
            toBeNext -> prevPtr = prev;

            // Writes data in
            strcpy(toBeNext -> data.color, color);
            toBeNext->data.value=value;

            // Grabs next line
            fscanf(fp, "%s %d %s\n", color, &value, nothing);

            // Iterates prev and makes a new node to insert
            prev = toBeNext;
            toBeNext = (Node*)malloc(sizeof(Node));
        }
    }
    // Initializes tail node
    toBeNext->prevPtr = prev;
    prev->nextPtr = toBeNext;
    toBeNext->nextPtr=NULL;

    // Rewinds file
    fclose(fp);
    fp = fopen("listOfCards.txt", "r");

    // Returns tail for later use
    return toBeNext;
}


int main() {
    srand((int)time(NULL));
    bool closed = false;
    printf("Welcome to DOS! \nDon't wory about cheating, the screen clears as necessary just follow the prompts as they show up.\n");
    printf("Enter the filename of the deck or \"standard\" for the basic deck: ");
    char filename[FILENAME_MAX];
    scanf("%s", filename);
    if(strcmp(filename, "standard") == 0) {
        strcpy(filename, "CardDeck.txt");
    }
    printf("Enter the number of players (2-6) planning to play: ");
    int numPlayers;
    scanf("%d", &numPlayers);
    while (numPlayers < 2 || numPlayers > 6) {
        printf("Invalid number of players, try again: ");
        scanf("%d", &numPlayers);
    }
    PlayerHand playerHands[numPlayers];
    for(int i = 0; i < numPlayers; i++) {
        initializeData(playerHands[i].dataStorage);
        Node* currPlayerHeadNode = (Node*)malloc(sizeof(Node));
        char playerHeadNodeText[15];
        strcpy(playerHeadNodeText, "head player");
        playerHeadNodeText[strlen(playerHeadNodeText) + 1] ='\0';
        playerHeadNodeText[strlen(playerHeadNodeText)] = i + '0';
        initializeNode(currPlayerHeadNode, currPlayerHeadNode, playerHeadNodeText, -2);
        Node* currPlayerTailNode = (Node*)malloc(sizeof(Node));
        char playerTailNodeText[15];
        strcpy(playerTailNodeText, "tail player");
        playerTailNodeText[strlen(playerTailNodeText) + 1] ='\0';
        playerTailNodeText[strlen(playerTailNodeText)] = i + '0';
        playerHands[i].dataStorage.tail = currPlayerTailNode;
        playerHands[i].dataStorage.head = currPlayerHeadNode;
        strcpy(currPlayerTailNode->data.color, playerHeadNodeText);
        currPlayerTailNode->data.value = -5;
        currPlayerHeadNode->nextPtr = currPlayerTailNode;
        currPlayerTailNode->prevPtr = currPlayerHeadNode;
    }
    while(!closed) {
        int currPlayer = 0;
        bool roundComplete = false;
        // Game Prep goes here
        

        // Move two cards for the two discard piles (making two linked lists)
        // initialize file into discard
        // move discard into draw
        // Deal cards

        LinkedListData discardData;
        initializeData(discardData);
        FILE* fp = fopen(filename, "r");
        Node discardHeadNode;
        initializeNode(&discardHeadNode, &discardHeadNode, "head discard", -2);
        discardData.head = &discardHeadNode;
        discardData.tail = initializeLinkedListFromFile(discardData, fp);
        strcpy((discardData.tail)->data.color, "tail discard");
        discardData.tail->data.value = -5;
        shuffle(&discardData);
        LinkedListData drawData;
        Node drawHeadNode;
        initializeNode(&drawHeadNode, &drawHeadNode, "head draw", -2);
        drawData.head = &drawHeadNode;
        drawData.tail = moveDiscardToDraw(discardData, drawData);
        initializeData(drawData);
        LinkedListData playPiles;
        initializeData(playPiles);
        playPiles.head = (Node*)malloc(sizeof(Node));
        playPiles.tail = (Node*)malloc(sizeof(Node));
        playPiles.head->nextPtr = playPiles.tail;
        playPiles.tail->prevPtr = playPiles.head;
        playPiles.tail->nextPtr=NULL;
        playPiles.head->prevPtr=NULL;
        strcpy(playPiles.head->data.color, "head");
        playPiles.head->data.value = -2;
        playPiles.tail->data.value=-5;
        for(int i = 0; i < 2; i++) {
            drawFromDrawPile(playPiles, drawData);
        }
        
        for(int currPlayerIndex = 0; currPlayerIndex<numPlayers; currPlayerIndex++) {
            for(int initialDealAmount = 0; initialDealAmount < 7; initialDealAmount++) {
                drawFromDrawPile(playerHands[currPlayerIndex].dataStorage, drawData);
            }
            true == true;
        }
        // for(int i = 0; i<numPlayers; i++) {
        //     //printf("Printing player %d's cards\n", i+1);
        //     //printList(playerHands[i]);
        // }
        // //printList(discardData);

        while (!roundComplete){
            currPlayer = currPlayer%numPlayers;
            system("clear");
            printf("Now Player %d's turn! Hand the computer to them and press enter! ", currPlayer + 1);
            char randomNothing;
            scanf("%*c%c", &randomNothing);
            system("clear");
            int numCardsLeft = 200;
            while(getLinkedListLength(&playPiles) < 4) {
                drawFromDrawPile(playPiles, drawData);
            }
            Node *nodePlayingOn = playPiles.head->nextPtr; 
            int numCardPlayingOn = getLinkedListLength(&playPiles) - 2;
            int cardsDiscarded;
            Node *tempNext = nodePlayingOn->nextPtr;
            printf("There are %d cards to play on\n", getLinkedListLength(&playPiles) - 2);
            for (int i = 0; i<numCardPlayingOn && numCardsLeft != 0 && nodePlayingOn != NULL; i++) {
                
                int cardsToPull;
                
                numCardsLeft = turns(playerHands[currPlayer].dataStorage, *nodePlayingOn, drawData, playPiles, discardData, &cardsToPull, &cardsDiscarded);
                for(int currPlayerIndex = 0; currPlayerIndex<numPlayers; currPlayerIndex++) {
                    for(int initialDealAmount = 0; initialDealAmount < cardsToPull; initialDealAmount++) {
                        if(currPlayerIndex != currPlayer) {
                            drawFromDrawPile(playerHands[currPlayerIndex].dataStorage, drawData);
                        }
                    }
                    true == true;
                }
                cardsToPull = 0;
                nodePlayingOn = nodePlayingOn->nextPtr;
                if (!(nodePlayingOn == NULL)) {
                    while(nodePlayingOn->data.value < 0) {
                        nodePlayingOn = nodePlayingOn->nextPtr;
                        if(nodePlayingOn == NULL) {
                            break;
                        }
                    }
                }
                
            }

            if(cardsDiscarded == 0) {
                    printf("You didn't play anything! You drew a card, press enter to continue ");
                    drawFromDrawPile(playerHands[currPlayer].dataStorage, drawData);
                    scanf("%c%*c", &randomNothing);
                }
                nodePlayingOn = tempNext;
            /* game code goes here */
            if(!roundComplete) {
                currPlayer++;
            }
            if(numCardsLeft == 0) {
                roundComplete = true;
            }
            
    
            // Rotate around for each turn
            // Sort hands (extra credit but seems ez since we have a node swap)
            // Print hand using print list
            // Manage movement onto the discard and drawing from the draw pile

        }
        for(int i = 0; i<numPlayers; i++) {
            //printf("Printing player %d's cards\n", i+1);
            //printList(playerHands[i]);
        }
        //Game Cleanup goes here
        
        // free every space in memory and vanish every value in the linked lists
        // Prompt to replay, set to true if not going to replay
        for(int handToPrint = 0; handToPrint < numPlayers; handToPrint++) {
            printList(playerHands[handToPrint].dataStorage);
        }
        for(int handToEmpty = 0; handToEmpty<numPlayers; handToEmpty++) {
            emptyList(playerHands[handToEmpty].dataStorage);
        }
        emptyList(drawData);
        emptyList(discardData);
        
        for(int playerIndex = 0; playerIndex<numPlayers; playerIndex++) {
            if(getSumOfHand(playerHands[playerIndex].dataStorage) >= 200) {
                closed = true;
                printf("Player %d Wins!\n", playerIndex+1);
                break;
            }
        }
    }
    return 0;
    //overall cleanup goes here
    // Return 0 at end
    // return 0;
}