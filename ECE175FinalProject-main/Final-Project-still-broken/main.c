#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structDefinitions.c"
#include "./linkedListFunctions.c"
#include "./fileStuff.c"


int main() {
    //Vector List of LinkedListData's to be Implemented

    LinkedListData discardData;
    initializeData(discardData);
    FILE* fp = fopen("listOfCards.txt", "r");
    Node discardHeadNode;
    initializeNode(&discardHeadNode, &discardHeadNode, "This is the head of the discard pile");
    discardData.head = &discardHeadNode;
    discardData.tail = initializeLinkedListFromFile(discardData, fp);
    strcpy((discardData.tail)->data.string, "This is the tail of the discard pile");

    printf("Printing LinkedList Forward\n");
    printList(discardData);

    printf("\nNow backwards:\n");
    printListBackwards(discardData);

    printf("\n\n\n\n");

    printNode(getElementFromIndex(&discardData, 0));
    printNode(getElementFromIndex(&discardData, getLinkedListLength(&discardData)-1));

    printf("%d\n", getLinkedListLength(&discardData));
    
    LinkedListData drawData;
    initializeData(drawData);
    Node drawHeadNode;
    initializeNode(&drawHeadNode, &drawHeadNode, "This is the head of the draw pile");
    drawData.head = &drawHeadNode;
    drawData.tail = moveDiscardToDraw(discardData, drawData);
    printf("\n\n\n");
    printList(drawData);
    
    printf("\n\n\nNow shuffled\n");
    shuffle(&drawData);
    printList(drawData);

    printf("\n\n\nNow shuffled again\n");
    shuffle(&drawData);
    printList(drawData);
}