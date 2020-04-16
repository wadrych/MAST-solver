#pragma once
#include "NodeQueue.h"

typedef struct TreeDTO {
	Node* root;
	Node** internalNodes;
	int amountOfLeaves;
	int amountOfInternalNodes;
} tree_dto;

class RootedTree {
public:
	RootedTree(TreeDTO tree);
	~RootedTree();
	

	int* OccurrencesOfNumberInInternalNodes(int number);
	int GetAmountOfInternalNodes() const;
	int GetAmountOfLeaves() const;
	Node* GetFirstSonOfNode(int number) const;
	Node* GetNodeOfIndex(int index) const;
private:
	Node* root;
	Node** internalNodes;
	int amountOfInternalNodes;
	int amountOfLeaves;
	void DeleteNode(Node* node);

};

