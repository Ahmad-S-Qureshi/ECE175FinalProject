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
    Node headNode;
    initializeNode(&headNode, &headNode, "This is the head\n");
    data.head = &headNode;
    data.tail = initializeLinkedListFromFile(data, fp);
    strcpy(data.tail->data, "\nThis is the tail");
    printList(data);
}