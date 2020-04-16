#include "TreeBuilder.h"

TreeBuilder::TreeBuilder() {
	amountOfInternalNodes = 0;
	insertAs = insert_as::brother;
	recentlyCreatedElement = nullptr;
	root = nullptr;
	currentIndex = 0;
	amountOfLeaves = 0;
	internalNodes = nullptr;
}

RootedTree* TreeBuilder::BuildTree() {
	std::cin >> newickTree;

	for(currentIndex = 0; currentIndex < newickTree.length(); currentIndex++) {
		DecideWhatToDoNext();
	}

	IndexInternalNodes();

	return new RootedTree(TreeDTO{root, internalNodes, amountOfLeaves, amountOfInternalNodes});
}

void TreeBuilder::DecideWhatToDoNext() {
	const char command = newickTree[currentIndex];

	switch(command) {
	case '(':
		HandleNewInternalNode();
		break;
	case ',':
		AppendNextElementAsBrother();
		break;
	case ')':
		GoToParentOfCurrentElement();
		break;
	case ';':
		break;
	default:
		AppendPossibleLeaf();
		break;
	}
}

void TreeBuilder::HandleNewInternalNode() {
	Node* parent = nullptr;
	Node* new_internal_node = nullptr;
	
	if(!IsFirstElement()) {
		parent = recentlyCreatedElement->parent;
	}
	if(InsertAsSon()) {
		parent = recentlyCreatedElement;
	}

	new_internal_node = CreateNewInternalNode(parent);

	if(!IsFirstElement()) {
		if(InsertAsSon()) recentlyCreatedElement->son = new_internal_node;
		else recentlyCreatedElement->brother = new_internal_node;
	}

	recentlyCreatedElement = new_internal_node;
	insertAs = insert_as::son;
	amountOfInternalNodes++;
}


Node* TreeBuilder::CreateNewInternalNode(Node* parent) {
	Node* new_internal_node = new Node;

	new_internal_node->parent = parent;
	new_internal_node->value = 0;
	new_internal_node->son = nullptr;
	new_internal_node->brother = nullptr;
	
	if(IsFirstElement()) root = new_internal_node;

	return new_internal_node;
}

bool TreeBuilder::IsFirstElement() const {
	return currentIndex == 0;
}

bool TreeBuilder::InsertAsSon() const {
	return insertAs == insert_as::son;
}

void TreeBuilder::AppendNextElementAsBrother() {
	insertAs = insert_as::brother;
}

void TreeBuilder::GoToParentOfCurrentElement() {
	recentlyCreatedElement = recentlyCreatedElement->parent;
}

void TreeBuilder::AppendPossibleLeaf() {
	const int i = currentIndex;

	if(IsDigit(i)) {
		int value = GetValue();

		Node* parent = nullptr;
		Node* new_leaf = nullptr;
		 
		if(InsertAsSon()) {
			parent = recentlyCreatedElement;
		}
		else {
			parent = recentlyCreatedElement->parent;
		}
		
		new_leaf = CreatePossibleLeaf(parent, value);

		if(InsertAsSon()) recentlyCreatedElement->son = new_leaf;
		else recentlyCreatedElement->brother = new_leaf;

		recentlyCreatedElement = new_leaf;
		insertAs = insert_as::brother;
		amountOfLeaves++;
	}
}

bool TreeBuilder::IsDigit(int index) const {
	return (newickTree[index] >= '0' && newickTree[index] <= '9');
}

int TreeBuilder::GetValue()
{
	size_t i = currentIndex;
	int value_length = 0;
	double value = 0;

	while(IsDigit(i)) {
		value *= int(pow(10, value_length));
		value += (newickTree[i] - '0');

		value_length++;
		if(i != currentIndex) currentIndex++;
		i++;
	}

	return value;
}

Node* TreeBuilder::CreatePossibleLeaf(Node* parent, int value) {
	Node* new_leaf = new Node;

	new_leaf->parent = parent;
	new_leaf->brother = nullptr;
	new_leaf->son = nullptr;
	new_leaf->value = value;

	return new_leaf;
}

void TreeBuilder::IndexInternalNodes() {
	NodeQueue queue;

	internalNodes = new Node * [amountOfInternalNodes];

	int indexOfNextInternalNode = amountOfInternalNodes;

	queue.Push(root);

	while(!queue.IsEmpty()) {
		Node* node = queue.Pop();
		Node* son = node->son;
		while(son != nullptr) {
			queue.Push(son);
			son = son->brother;
		}
		if(IsInternalNode(node)) {
			node->value =  amountOfLeaves + indexOfNextInternalNode--;
			internalNodes[indexOfNextInternalNode] = node;
		}
	}
}

bool TreeBuilder::IsInternalNode(Node* node) const {
	return node->value < 1 || node->value > amountOfLeaves;
}
