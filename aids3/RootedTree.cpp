#include "RootedTree.h"

RootedTree::RootedTree(TreeDTO tree)
	: root(tree.root), internalNodes(tree.internalNodes),
      amountOfInternalNodes(tree.amountOfInternalNodes), amountOfLeaves(tree.amountOfLeaves) {
}

RootedTree::~RootedTree() {
	delete[] internalNodes;
	internalNodes = nullptr;
	
	DeleteNode(root);
}

void RootedTree::DeleteNode(Node* node) {
	if(node->brother != nullptr) {
		DeleteNode(node->brother);
	}
	if(node->son != nullptr) {
		DeleteNode(node->son);
	}

	Node* parent = node->parent;
	if(parent != nullptr) {
		if(parent->son == node) {
			parent->son = nullptr;
		}
		else {
			Node* son = parent->son;
			while(son->brother != node) {
				son = son->brother;
			}
			son->brother = nullptr;
		}
	}
	
	delete node;
	node = nullptr;
}

int* RootedTree::OccurrencesOfNumberInInternalNodes(int number) {
	NodeQueue queue;
	int* internalNodesArray = new int[amountOfLeaves + amountOfInternalNodes];
	for(int i = 0; i < amountOfInternalNodes + amountOfLeaves; i++) internalNodesArray[i] = 0;
	
	queue.Push(root);

	while(!queue.IsEmpty()) {
		Node* node = queue.Pop();
		Node* son = node->son;
		while(son != nullptr) {
			queue.Push(son);
			son = son->brother;
		}
		if(node->value == number) {
			Node* tmp = node;
			while(tmp != root) {
				internalNodesArray[tmp->value-1] = 1;
				tmp = tmp->parent;
			}
			internalNodesArray[root->value-1] = 1;
		}
	}

	return internalNodesArray;
}

int RootedTree::GetAmountOfInternalNodes() const {
	return amountOfInternalNodes;
}

int RootedTree::GetAmountOfLeaves() const {
	return amountOfLeaves;
}

Node* RootedTree::GetFirstSonOfNode(int number) const {
	return internalNodes[number - amountOfLeaves]->son;
}

Node* RootedTree::GetNodeOfIndex(int index) const {
	return internalNodes[index - amountOfLeaves];
}
