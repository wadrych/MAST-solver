#include "NodeQueue.h"

NodeQueue::NodeQueue() {
	lastElement = nullptr;
	firstElement = nullptr;
}

void NodeQueue::Push(Node* node) {
	QueueElement* new_element = new QueueElement;
	new_element->node = node;
	new_element->previous = nullptr;
	
	if(IsEmpty()) {
		firstElement = new_element;
		new_element->next = nullptr;
	}
	else {
		lastElement->previous = new_element;
		new_element->next = lastElement;
	}
	
	lastElement = new_element;
}

bool NodeQueue::IsEmpty() const {
	return lastElement == nullptr && firstElement == nullptr;
}

Node* NodeQueue::Pop() {
	if(firstElement!=nullptr) {
		Node* node = firstElement->node;
		
		QueueElement* to_delete = firstElement;
		firstElement = firstElement->previous;
		if(firstElement != nullptr) firstElement->next = nullptr;
		if(firstElement == nullptr) lastElement = nullptr;
		delete to_delete;

		return node;
	}
	else {
		return nullptr;
	}
}

NodeQueue::~NodeQueue() {
	while(lastElement != nullptr) {
		lastElement = lastElement->next;
		delete lastElement->previous;
		lastElement->previous = nullptr;
	}
	delete lastElement;
	lastElement = nullptr;
}
