#include <stdio.h>
#include <stdlib.h>


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
    fscanf(fp, "%s\n", lineFromFile);
    while(!feof(fp)) {
        if(strcmp("\n", lineFromFile) != 0) {
            prev->nextPtr = toBeNext;
            toBeNext->nextPtr = NULL;
            toBeNext -> prevPtr = prev;
            strcpy(toBeNext -> data.string, lineFromFile);
            fscanf(fp, "%s\n", lineFromFile);
            prev = toBeNext;
            toBeNext = (Node*)malloc(sizeof(Node));
        }
    }
    prev->nextPtr = toBeNext;
    toBeNext->nextPtr = NULL;
    toBeNext -> prevPtr = prev;
    strcpy(toBeNext -> data.string, lineFromFile);
    fgets(lineFromFile, 50, fp);
    prev = toBeNext;
    toBeNext = (Node*)malloc(sizeof(Node));
    toBeNext->prevPtr = prev;
    prev->nextPtr = toBeNext;
    fclose(fp);
    fp = fopen("listOfCards.txt", "r");
    return toBeNext;
}