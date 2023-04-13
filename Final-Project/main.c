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
    char headData[50];
    fgets(headData, 50, fp);
    initializeNode(&headNode, &headNode, headData);
    data.head = &headNode;
    data.tail = initializeLinkedListFromFile(data, fp);
    printList(data);
}