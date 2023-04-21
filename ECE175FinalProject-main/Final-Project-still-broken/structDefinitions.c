typedef struct card_s {
    char color[10];
    int value;
    char action[15];
    struct card_s *pt;
} card;


typedef struct node {
    struct node *prevPtr;
    struct node *nextPtr;
    card data;
} Node;

typedef struct linkedListData {
    Node* head;
    Node* tail;
} LinkedListData;

typedef struct playerHand {
    LinkedListData dataStorage;
    int score;
} PlayerHand;
