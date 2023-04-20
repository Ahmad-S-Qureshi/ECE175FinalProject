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
    char color[10];
    int value; 
    fscanf(fp, "%d %s\n", &value, color);
    while(strcmp(color, "Tail") != 0) {
        if(strcmp("\n", color) != 0) {
            prev->nextPtr = toBeNext;
            toBeNext->nextPtr = NULL;
            toBeNext -> prevPtr = prev;
            strcpy(toBeNext -> data.color, color);
            toBeNext->data.value=value;
            fscanf(fp, "%d %s\n", &value, color);
            prev = toBeNext;
            toBeNext = (Node*)malloc(sizeof(Node));
        }
    }
    toBeNext->prevPtr = prev;
    prev->nextPtr = toBeNext;
    toBeNext->nextPtr=NULL;
    fclose(fp);
    fp = fopen("listOfCards.txt", "r");
    return toBeNext;
}