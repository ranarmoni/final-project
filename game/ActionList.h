




struct Node {
	GameBoard data;
	struct Node* next;
	struct Node* prev;
};

struct ActionList {
	struct Node* curr;
};

typedef struct Node node;
typedef struct ActionList ActionList;



