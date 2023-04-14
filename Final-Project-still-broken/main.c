#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./linkedListFunctions.h"
#include "./fileStuff.h"


int main() {
    LinkedListData discardData;
    initializeData(discardData);
    FILE* fp = fopen("listOfCards.txt", "r");
    Node discardHeadNode;
    initializeNode(&discardHeadNode, &discardHeadNode, "This is the head of the discard pile\n");
    discardData.head = &discardHeadNode;
    discardData.tail = initializeLinkedListFromFile(discardData, fp);
    strcpy(discardData.tail->data, "This is the tail of the discard pile\n");
    printList(discardData);

    printf("\n\n\n\n");
    printNode(getElementFromIndex(&discardData, 0));
    printNode(getElementFromIndex(&discardData, getLinkedListLength(&discardData) + 1));
    printf("%d\n", getLinkedListLength(&discardData));

    // printf("%d\n", getLinkedListLength(&discardData));
    // LinkedListData drawData;
    // initializeData(drawData);
    // Node drawHeadNode;
    // initializeNode(&drawHeadNode, &drawHeadNode, "This is the head of the draw pile\n");
    // drawData.head = &drawHeadNode;
    // drawData.tail = moveDiscardToDraw(discardData, drawData);
    // printf("\n\n\n");
    // printList(drawData);
}