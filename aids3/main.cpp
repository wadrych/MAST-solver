#include "TreeBuilder.h"
#include "MASTSolver.h"

RootedTree** create_trees(int amount_of_trees);

int main() {
	int amount_of_trees = 0;
	std::cin >> amount_of_trees;
	
	RootedTree** forest = create_trees(amount_of_trees);

	

	for(int i = 0; i < amount_of_trees;i++) {
		for(int j=i+1; j<amount_of_trees;j++) {
			MASTSolver mast_solver(forest[i], forest[j]);
			mast_solver.Run();
		}
		
	}


	
	for(int i=0; i<amount_of_trees; i++) {
		delete forest[i];
		forest[i] = nullptr;
	}
	delete[] forest;
	forest = nullptr;
	
	return 0;
}

RootedTree** create_trees(int amount_of_trees) {
	RootedTree** new_forest = new RootedTree*[amount_of_trees];
	
	for(int i=0;i<amount_of_trees;i++) {
		TreeBuilder tree_builder;
		new_forest[i] = tree_builder.BuildTree();
	}

	return new_forest;
}



