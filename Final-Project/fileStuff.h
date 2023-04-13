#include <stdio.h>
//#include "./linkedListFunctions.h"


int getNumCards (FILE* fp) {
    char line[50];
    int numLines = 0;
    while (fscanf(fp, "%s", line) != EOF){
        numLines++;
    }
    fclose(fp);
    fp = fopen("listOfCards.txt", "r");
    return numLines;
}

Node *initializeLinkedListFromFile(LinkedListData data, FILE *fp) {
    Node *toBeNext = (Node*)malloc(sizeof(Node));
    Node *prev = data.head;
    char lineFromFile[50];
    fgets(lineFromFile, 50, fp);
    while(!feof(fp)) {
        prev->nextPtr = toBeNext;
        toBeNext->nextPtr = NULL;
        toBeNext -> prevPtr = prev;
        strcpy(toBeNext -> data, lineFromFile);
        fgets(lineFromFile, 50, fp);
        toBeNext = (Node*)malloc(sizeof(Node));
    }
    return toBeNext;
}