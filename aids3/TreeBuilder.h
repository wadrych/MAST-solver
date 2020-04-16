#pragma once
#include "RootedTree.h"
#include "NodeQueue.h"
#include <string>
#include <iostream>

enum class insert_as {
	son,
	brother
};

class TreeBuilder {
public:
	TreeBuilder();

	RootedTree* BuildTree();
private:
	Node* root;
	Node* recentlyCreatedElement;
	int amountOfInternalNodes;
	std::string newickTree;
	insert_as insertAs;
	size_t currentIndex;
	int amountOfLeaves;
	Node** internalNodes;

	void GoToParentOfCurrentElement();
	void AppendPossibleLeaf();
	void HandleNewInternalNode();
	void DecideWhatToDoNext();
	bool IsFirstElement() const;
	Node* CreateNewInternalNode(Node* parent);
	void AppendNextElementAsBrother();
	Node* CreatePossibleLeaf(Node* parent, int value);

	void IndexInternalNodes();
	int GetValue();
	
	bool InsertAsSon() const;
	bool IsDigit(int index) const;
	bool IsInternalNode(Node* node) const;
};

