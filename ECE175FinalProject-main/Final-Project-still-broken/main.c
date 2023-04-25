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
            for (int i = 0; i<numCardPlayingOn && numCardsLeft != 0; i++) {
                
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