#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "structDefinitions.c"
#include "linkedListFunctions.c"
#include "fileStuff.c"


int main() {
    srand((int)time(NULL));
    bool closed = false;
    int i=0;
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
    for(int i = 0; i<numPlayers; i++) {
        printList(playerHands[i].dataStorage);
        printf("Player %d initialized\n", i + 1);
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
        FILE* fp = fopen("listOfCards.txt", "r");
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
        for(int currPlayerIndex = 0; currPlayerIndex<numPlayers; currPlayerIndex++) {
            for(int initialDealAmount = 0; initialDealAmount < 7; initialDealAmount++) {
                drawFromDrawPile(playerHands[currPlayerIndex].dataStorage, drawData);
            }
        }
        // for(int i = 0; i<numPlayers; i++) {
        //     //printf("Printing player %d's cards\n", i+1);
        //     //printList(playerHands[i]);
        // }
        // //printList(discardData);

        while (!roundComplete){
            
            /* game code goes here */
            int numCardsLeft = turn();
            roundComplete = true;
            
    
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
            if(sumHand(playerHands[playerIndex]) >= 200) {
                closed = true;
                printf("Player %d Wins!\n", playerIndex+1);
                break;
            }
        }
        i++;
    }
    return 0;
    //overall cleanup goes here
    // Return 0 at end
    // return 0;

    //Vector List of LinkedListData's or a dynamically allocated array to be Implemented

    LinkedListData discardData;
    initializeData(discardData);
    FILE* fp = fopen("listOfCards.txt", "r");
    Node discardHeadNode;
    initializeNode(&discardHeadNode, &discardHeadNode, "head discard", -2);
    discardData.head = &discardHeadNode;
    discardData.tail = initializeLinkedListFromFile(discardData, fp);
    strcpy((discardData.tail)->data.color, "tail discard");
    discardData.tail->data.value = -5;

    // printf("Printing LinkedList Forward\n");
    printList(discardData);

    // printf("\nNow backwards:\n");
    // printListBackwards(discardData);
    // printf("A total of %d cards\n", getLinkedListLength(&discardData));

    // printf("\n\n\n\n");

    //printNode(getElementFromIndex(&discardData, 0));
    //printNode(getElementFromIndex(&discardData, getLinkedListLength(&discardData)-1));

    

    
    
    // printf("\n\n\nNow shuffled\n");
    // shuffle(&drawData);
    // printList(drawData);
    // printf("A total of %d cards", getLinkedListLength(&drawData));
    

    // printf("\n\n\nNow shuffled again\n");
    // shuffle(&drawData);
    // printList(drawData);
    // printf("A total of %d cards\n", getLinkedListLength(&drawData));
    

    // printList(drawData);
    // printf("\n\n\nNow moving first val in draw to discard\n");
    // moveNode(&drawData, &discardData, drawData.head->nextPtr);
    // printList(drawData);
    // printList(discardData);
}