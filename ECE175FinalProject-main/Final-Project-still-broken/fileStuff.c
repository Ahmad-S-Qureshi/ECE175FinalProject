#include <stdio.h>
#include <stdlib.h>

// // Unused, for debugging to make sure every card was accounted for
// int getNumCards (FILE* fp) {
//     char line[50];
//     int numLines = 0;
//     while (fscanf(fp, "%s", line) != EOF){
//         numLines++;
//     }
//     fclose(fp);
//     fp = fopen("listOfCards.txt", "r");
//     return numLines;
// }

// Grabs every line assuming form int value space string color
Node *initializeLinkedListFromFile(LinkedListData data, FILE *fp) {
    // Prepares an empty node to fill in with details
    Node *toBeNext = (Node*)malloc(sizeof(Node));

    // Every the previous node is set to be the head, initialized elsewhere
    Node *prev = data.head;

    // A string to hold the color values
    char color[10];

    // An int to hold card number value (Wilds set to be zero)
    int value; 

    char nothing[20];

    // Reads in a link
    fscanf(fp, "%s %d %s\n", color, &value, nothing);
    if (value == 11) {
        value = 0;
    }
    if(strcmp(color, "black") ==0) {
        strcpy(color, "Wild");
    } else if (strcmp(color, "yellow") == 0) {
        strcpy(color, "Yellow");
    } else if (strcmp(color, "blue") == 0) { 
        strcpy(color, "Blue");
    } else if (strcmp(color, "green") == 0) { 
        strcpy(color, "Green");
    } else if (strcmp(color, "red") == 0) { 
        strcpy(color, "Red");
    }


    // Continually reads lines and makes nodes until the line is Tail
    while(!feof(fp)) {

        // Ensures a line has something in it
        if(strcmp("\n", color) != 0) {
            if (value == 11) {
                value = 0;
            }
            if(strcmp(color, "black") ==0) {
                strcpy(color, "Wild");
            } else if (strcmp(color, "yellow") == 0) {
                strcpy(color, "Yellow");
            } else if (strcmp(color, "blue") == 0) { 
                strcpy(color, "Blue");
            } else if (strcmp(color, "green") == 0) { 
                strcpy(color, "Green");
            } else if (strcmp(color, "red") == 0) { 
                strcpy(color, "Red");
    }

            // Makes the previous node point to the new one to be formed
            prev->nextPtr = toBeNext;

            // Makes sure the next pointer is null (unnesscesary but worth doing)
            toBeNext->nextPtr = NULL;

            // Makes the new node point to the last node
            toBeNext -> prevPtr = prev;

            // Writes data in
            strcpy(toBeNext -> data.color, color);
            toBeNext->data.value=value;

            // Grabs next line
            fscanf(fp, "%s %d %s\n", color, &value, nothing);

            // Iterates prev and makes a new node to insert
            prev = toBeNext;
            toBeNext = (Node*)malloc(sizeof(Node));
        }
    }
    // Initializes tail node
    toBeNext->prevPtr = prev;
    prev->nextPtr = toBeNext;
    toBeNext->nextPtr=NULL;

    // Rewinds file
    fclose(fp);
    fp = fopen("listOfCards.txt", "r");

    // Returns tail for later use
    return toBeNext;
}