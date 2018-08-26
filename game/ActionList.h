




struct Node {
	GameBoard *board;
	struct Node* next;
	struct Node* prev;
};

struct ActionList{
	Node *curr;
	Node *first;
};

typedef struct Node node;
typedef struct ActionList ActionList;



