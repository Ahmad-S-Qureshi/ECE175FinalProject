#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structDefinitions.c"
#include "linkedListFunctions.c"
#include "fileStuff.c"


int main() {
    //Vector List of LinkedListData's or a dynamically allocated array to be Implemented

    LinkedListData discardData;
    initializeData(discardData);
    FILE* fp = fopen("listOfCards.txt", "r");
    Node discardHeadNode;
    initializeNode(&discardHeadNode, &discardHeadNode, "head discard", -2);
    discardData.head = &discardHeadNode;
    discardData.tail = initializeLinkedListFromFile(discardData, fp);
    strcpy((discardData.tail)->data.color, "tail dicard");
    discardData.tail->data.value = -5;

    // printf("Printing LinkedList Forward\n");
    // printList(discardData);

    //printf("\nNow backwards:\n");
    //printListBackwards(discardData);

    printf("\n\n\n\n");

    //printNode(getElementFromIndex(&discardData, 0));
    //printNode(getElementFromIndex(&discardData, getLinkedListLength(&discardData)-1));

    //printf("%d\n", getLinkedListLength(&discardData));
    
    LinkedListData drawData;
    initializeData(drawData);
    Node drawHeadNode;
    initializeNode(&drawHeadNode, &drawHeadNode, "head draw", -2);
    drawData.head = &drawHeadNode;
    drawData.tail = moveDiscardToDraw(discardData, drawData);
    //printf("\n\n\n");
    //printList(drawData);
    
    // printf("\n\n\nNow shuffled\n");
    // shuffle(&drawData);
    // //printList(drawData);

    // printf("\n\n\nNow shuffled again\n");
    // shuffle(&drawData);
    // printList(drawData);

    printList(drawData);
    printf("\n\n\nNow moving first val in draw to discard\n");
    moveNode(&drawData, &discardData, drawData.head->nextPtr);
    printList(drawData);
    printList(discardData);
}