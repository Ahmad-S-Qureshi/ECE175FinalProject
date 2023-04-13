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
    strcpy(discardData.tail->data, "\nThis is the tail of the discard pile");
    printList(discardData);
    printf("%d\n", getLinkedListLength(&discardData));
    LinkedListData drawData;
    initializeData(drawData);
    Node drawHeadNode;
    initializeNode(&drawHeadNode, &drawHeadNode, "This is the head of the draw pile\n");
    drawData.head = &drawHeadNode;
    drawData.tail = moveDiscardToDraw(discardData, drawData);
    printf("\n\n\n");
    printList(drawData);
}