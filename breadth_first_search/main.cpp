#include <iostream>
#include <queue>
#include <algorithm>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"

/**
 * TODO: send execlog to stderr.
 */
int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin);
	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/* Breadth First Search Algorithm */
	std::queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);
	bool visited[maze.m()][maze.n()]; std::fill(*visited, *visited + maze.m()*maze.n(), false);

	while (!L.empty())
	{
		graph::path p = L.front(); L.pop();
		graph::node& x = p.last_node(); /*EXECLOG/ std::cerr << "goto " << x.i() << "," << x.j() << "\n"; /*/

		if (x == target)
		{
			std::cout << p << "\n";
			return 0;
		}

		if (!visited[x.i()][x.j()])
		{
			visited[x.i()][x.j()] = true;
			for (graph::node& y : graph.adjacent_nodes(x))
				if (!visited[y.i()][y.j()])
				{
					graph::path new_path(p); new_path.add_node(y);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	return 0;
}
