#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;
    char data[50];
} Node;

typedef struct linkedListData {
    Node* head;
    Node* tail;
} LinkedListData;

void initializeData(LinkedListData data);
void initializeNode(Node *prevNode, Node *toBeInitialized, char *data);
Node *getElementFromIndex(LinkedListData *data, int index);
void insertElementToList(LinkedListData *data, int indexBefore);
void printList(LinkedListData data);
void printNode(Node* nodeToBePrinted);
void shuffle(LinkedListData *data);
int getLinkedListLength(LinkedListData *data);
Node *moveDiscardToDraw(LinkedListData discardData, LinkedListData drawData);
//void swapNodes(LinkedListData *data, int lengthFromHeadToNode1, int lengthFromHeadToNode2);

