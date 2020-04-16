#pragma once
#include "RootedTree.h"
#include <iostream>
#include "ThirdCaseSolver.h"

class MASTSolver {
public:
	MASTSolver(RootedTree* first_tree, RootedTree* second_tree);
	~MASTSolver();

	void Run();
	
private:
	RootedTree* firstTree;
	RootedTree* secondTree;
	int** array;
	int* taken;
	int max;
	int dimensionX;
	int dimensionY;

	int CheckFirstCase(int AX, int BX) const;
	int CheckSecondCase(int AX, int BX) const;
	int ChooseMaxOfThreeCases(int i, int j);
	void CreateArrayAndPopulateWithZeros();
	void CreateConnectionsForSecondTree();
	void CreateConnectionsForFirstTree();
	void FindConnectionsForInternalNodes();
};

