#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "node.h"

#include <queue>
#include <stack>
#include <vector>

namespace libgraph 
{	
	template<typename T, typename search_memory_model, typename graph_memory_model>
		class search_graph
		{
			public:
				search_graph(const graph<int, memory_selector<int, linked_list> >& g) : searchable_graph(g)
			{
			}

				bool search(node<T> node)
				{
					// for every node in collection from graph g
					// if node is on not on visited list
					// visit DFS
					graph_memory_model model = searchable_graph.get_memory();

					/*for(typename graph_memory_model::const_iterator it = model.begin(); it != model.end(); ++it)
					{

					}*/

					return false;
				}

			protected:
				void visitDFS(node<T> node)
				{
					// mark node in visited vector as visited
					// add its neightbours to storage
					// visitDFS();
				}

			private:
				std::vector<T> visited;
				std::vector<T> storage; // stack or fifo
				graph<int, memory_selector<int, linked_list> > searchable_graph;
		};

} // namespace libgraph

#endif // SEARCH_H

