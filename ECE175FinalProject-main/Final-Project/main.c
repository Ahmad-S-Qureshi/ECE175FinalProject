#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./linkedListFunctions.h"
#include "./fileStuff.h"


int main() {
    LinkedListData data;
    initializeData(data);
    FILE* fp = fopen("listOfCards.txt", "r");
<<<<<<< HEAD
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
=======
    Node headNode;
    initializeNode(&headNode, &headNode, "This is the head\n");
    data.head = &headNode;
    data.tail = initializeLinkedListFromFile(data, fp);
    strcpy(data.tail->data, "\nThis is the tail");
    printList(data);
    printf("%d\n", getLinkedListLength(&data));
    swapNodes(&data, 2, 6);
    printf("\n\n\n");
    printList(data);
>>>>>>> parent of 838837a (epic)
}