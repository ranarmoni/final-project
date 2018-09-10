
int undo(ActionList *list);
int redo(ActionList *list);
void addNewNode(ActionList *list);
void reset(ActionList *list);
ActionList* initList();



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



