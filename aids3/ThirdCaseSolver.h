#pragma once
#include "NodeQueue.h"

enum class axis {
	ox,
	oy
};

typedef struct ComparedElement {
	int amount;
	axis axis;
	Node* element;
	Node** sons;
} compared_element;

class ThirdCaseSolver {
public:
	ThirdCaseSolver(Node* node1, Node* node2, int** array);
	~ThirdCaseSolver();

	int GetMax();
private:
	int* taken;
	int** array;
	int max = 0;
	ComparedElement* positionSons;
	ComparedElement* permutationSons;

	static int CountSons(Node* node);
	void CreateElementsToCompare(Node* node1, Node* node2);
	void SetSmallerParentAsPosition();
	void CreateTakenArray();
	void GeneratePermutationsAndChooseMax(int counter);
	int CreateSum() const;
	bool IsFree(int number) const;
	Node** GetSonsArray(Node* node, int size);
	bool IsPermutationCreated(int counter) const;
};


