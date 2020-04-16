#include "ThirdCaseSolver.h"

ThirdCaseSolver::ThirdCaseSolver(Node* node1, Node* node2, int** array)
	: array(array) {
	max = 0;
	positionSons = nullptr;
	permutationSons = nullptr;

	CreateElementsToCompare(node1, node2);
	SetSmallerParentAsPosition();
	CreateTakenArray();
}

void ThirdCaseSolver::CreateElementsToCompare(Node* node1, Node* node2) {
	positionSons = new ComparedElement;
	permutationSons = new ComparedElement;

	positionSons->element = node1;
	positionSons->amount = CountSons(node1);
	positionSons->axis = axis::ox;
	positionSons->sons = GetSonsArray(node1, positionSons->amount);
	
	permutationSons->element = node2;
	permutationSons->amount = CountSons(node2);
	permutationSons->axis = axis::oy;
	permutationSons->sons = GetSonsArray(node2, permutationSons->amount);
}

	int ThirdCaseSolver::CountSons(Node* node) {
	Node* son = node->son;
	int counter = 0;

	while(son != nullptr) {
		counter++;
		son = son->brother;
	}

	return counter;
}

Node** ThirdCaseSolver::GetSonsArray(Node* node, int size) {
	Node** node_array = new Node * [size];
	Node* son = node->son;
	int i = 0;

	while(son != nullptr) {
		node_array[i] = son;
		son = son->brother;
		i++;
	}

	return node_array;
}

void ThirdCaseSolver::SetSmallerParentAsPosition() {
	if(positionSons->amount > permutationSons->amount) {
		ComparedElement* tmp = positionSons;
		positionSons = permutationSons;
		permutationSons = tmp;
	}
}

void ThirdCaseSolver::CreateTakenArray() {
	int size = positionSons->amount;
	taken = new int[size];

	for(int i = 0; i < size; i++) {
		taken[i] = -1;
	}
}

ThirdCaseSolver::~ThirdCaseSolver() {
	delete[] taken;
	taken = nullptr;

	delete[] positionSons->sons;
	positionSons->sons = nullptr;
	delete positionSons;
	positionSons = nullptr;
	
	delete[] permutationSons->sons;
	permutationSons->sons = nullptr;
	delete permutationSons;
	permutationSons = nullptr;
}

int ThirdCaseSolver::GetMax() {
	int counter = 0;
	
	GeneratePermutationsAndChooseMax(counter);

	return max;
}

void ThirdCaseSolver::GeneratePermutationsAndChooseMax(int counter) {
	for(int i = 0; i < permutationSons->amount; i++) {
		if(IsFree(i)) {
			taken[counter] = i;

			if(IsPermutationCreated(counter)) {
				
				int sum = CreateSum();
				if(sum > max) max = sum;
			}
			else {
				GeneratePermutationsAndChooseMax(counter + 1);
			}
			
			taken[counter] = -1;
		}
	}
}

bool ThirdCaseSolver::IsFree(int number) const {
	for(int i = 0; i < positionSons->amount; i++) {
		if(taken[i] == number) 
			return false;
	}
	
	return true;
}

bool ThirdCaseSolver::IsPermutationCreated(int counter) const {
	return counter == positionSons->amount - 1;
}

int ThirdCaseSolver::CreateSum() const {
	int sum = 0;

	Node* position_son = positionSons->sons[0];
	Node** variation_sons = permutationSons->sons;

	for(int i = 0; i < positionSons->amount; i++) {
		int variations_son = taken[i];
		int offset = 1;
		int val1 = position_son->value - offset;
		int val2 = variation_sons[variations_son]->value - offset;
		
		if(positionSons->axis == axis::ox) 
			sum += array[val1][val2];
		else 
			sum += array[val2][val1];
		
		position_son = position_son->brother;
	}

	return sum;
}
