#include "Graph.h"
#include <iostream>
#include <vector>
#include <memory>


int main(int argc, char* argv[]) {
	gdwg::Graph<int, int> g{};

	for (int count = 0; count < 5; ++count) {
		g.addNode(count);
	}
	
	for (g.begin(); !g.end(); g.next()) {
		std::cout << g.value() << std::endl;
	}
	
	return 0;
}