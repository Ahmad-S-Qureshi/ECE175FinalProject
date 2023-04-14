typedef struct nodeData{
    char string[50];
} NodeData;


typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;
    NodeData data;
} Node;

typedef struct linkedListData {
    Node* head;
    Node* tail;
} LinkedListData;
