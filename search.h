#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "node.h"
#include "types.h"

#include <queue>
#include <stack>
#include <vector>

namespace libgraph 
{	
	template<typename T, typename search_memory_model, typename searchable_graph_memory_model>
		class search_graph
		{
			//friend class graph_memory_model<int, linked_list>;

			public:
				search_graph(const list_graph& g) : searchable_graph(g)
				{
				}

				bool search(node<T> node)
				{
					// for every node in collection from graph g
					// if node is on not on visited list
					// visit DFS
					
					list_graph_memory_model model = searchable_graph.get_memory();

					//for(list_graph_memory_model::const_iterator it = model.begin(); it != model.end(); ++it)
					{

					}

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
				list_graph searchable_graph;
		};

} // namespace libgraph

#endif // SEARCH_H

