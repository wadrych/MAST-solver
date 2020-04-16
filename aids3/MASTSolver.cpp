#include "MASTSolver.h"
#include "TreeBuilder.h"

MASTSolver::MASTSolver(RootedTree* first_tree, RootedTree* second_tree)
	: firstTree(first_tree), secondTree(second_tree) {
	max = 0;
	dimensionX = secondTree->GetAmountOfInternalNodes() + secondTree->GetAmountOfLeaves();
	dimensionY = firstTree->GetAmountOfInternalNodes() + firstTree->GetAmountOfLeaves();
	taken = nullptr;
	array = nullptr;
}

void MASTSolver::Run() {
	CreateArrayAndPopulateWithZeros();
	CreateConnectionsForFirstTree();
	CreateConnectionsForSecondTree();
	FindConnectionsForInternalNodes();

	std::cout << firstTree->GetAmountOfLeaves() - max<<std::endl;
}

void MASTSolver::CreateArrayAndPopulateWithZeros() {
	array = new int* [dimensionY];
	for(int i = 0; i < dimensionY; i++) {
		array[i] = new int[dimensionX];
		for(int j=0;j<dimensionX;j++) {
			array[i][j] = 0;
		}
	}
}

void MASTSolver::CreateConnectionsForSecondTree() {
	for(int i = 0; i < firstTree->GetAmountOfLeaves(); i++) {
		int* table = secondTree->OccurrencesOfNumberInInternalNodes(i + 1);
		for(int j = 0; j < dimensionX; j++) {
			if(table[j] == 1) {
				array[i][j] = 1;
			}
		}
		delete[] table;
		table = nullptr;
	}
}

void MASTSolver::CreateConnectionsForFirstTree() {
	for(int i = 0; i < secondTree->GetAmountOfLeaves(); i++) {
		int* table = firstTree->OccurrencesOfNumberInInternalNodes(i + 1);
		for(int j = firstTree->GetAmountOfLeaves(); j < dimensionY; j++) {
			if(table[j] == 1) {
				array[j][i] = 1;
			}
		}
		delete[] table;
		table = nullptr;
	}
}

void MASTSolver::FindConnectionsForInternalNodes() {
	for(int i = firstTree->GetAmountOfLeaves(); i < dimensionY; i++) {
		for(int j = secondTree->GetAmountOfLeaves(); j < dimensionX; j++) {
			int max_of_three = 0;
			
			max_of_three = ChooseMaxOfThreeCases(i, j);
			array[i][j] = max_of_three;
			if(max_of_three > max) max = max_of_three;
		}
	}
}

int MASTSolver::ChooseMaxOfThreeCases(int i, int j) {
	int max_of_three = 0;
	
	int s1 = CheckFirstCase(i, j);
	if(s1 > max_of_three) max_of_three = s1;
	
	int s2 = CheckSecondCase(i, j);
	if(s2 > max_of_three) max_of_three = s2;


	ThirdCaseSolver third_case_solver(firstTree->GetNodeOfIndex(i), secondTree->GetNodeOfIndex(j), array);
	int s3 = third_case_solver.GetMax();
	if(s3 > max_of_three) max_of_three = s3;
	
	return max_of_three;
}


MASTSolver::~MASTSolver() {
	const int dimension_y = firstTree->GetAmountOfInternalNodes() + firstTree->GetAmountOfLeaves();
	for(int i = 0; i < dimension_y; i++) {
		delete array[i];
		array[i] = nullptr;
	}
	delete[] array;
	array = nullptr;
}

int MASTSolver::CheckFirstCase(int AX, int BX) const {
	Node* son = secondTree->GetFirstSonOfNode(BX);
	int local_max = 0;
	while(son != nullptr) {
		int val = array[AX][son->value-1];
		if(val > local_max) local_max = val;
		
		son = son->brother;
	}

	return local_max;
}

int MASTSolver::CheckSecondCase(int AX, int BX) const {
	Node* son = firstTree->GetFirstSonOfNode(AX);
	int local_max = 0;
	while(son != nullptr) {
		int val = array[son->value-1][BX];
		if(val > local_max) local_max = val;

		son = son->brother;
	}

	return local_max;
}