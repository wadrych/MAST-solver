#pragma once

typedef struct Node {
	int value;
	Node* parent;
	Node* brother;
	Node* son;
} node;

typedef struct QueueElement {
	Node* node;
	QueueElement* next;
	QueueElement* previous;
} queue_element;

class NodeQueue {
public:
	NodeQueue();
	~NodeQueue();
	void Push(Node* node);
	Node* Pop();
	bool IsEmpty() const;
private:
	QueueElement* lastElement;
	QueueElement* firstElement;

};

