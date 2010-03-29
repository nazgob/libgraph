#ifndef SEARCH_H
#define SEARCH_H

#include "types.h"
#include "graph.h"
#include "node.h"

#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

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
					list_graph_memory_model model = searchable_graph.get_memory();

					// for every node in collection from graph g
					for(list_graph_memory_model::const_iterator it = model.begin(); it != model.end(); ++it)
					{
						// if node is on not on visited list
						if(std::find_if(visited.begin(), visited.end(), boost::lambda::_1 == node.value) == visited.end())
						{
							// visit DFS
							visitDFS(*it);
						}
					}
					return false;
				}

			protected:
				void visitDFS(const typename node_list_pair<T>::type& input)
				{
					// mark node in visited vector as visited
					visited.push_back(input.first.value);
														
					// add its neighbours to storage
					std::list<T> list = input.second;
					storage.resize(storage.size() + list.size());
					std::copy(list.begin(), list.end(), storage.begin()); //copy only unique!
			
					// pop element from storage

					//visitDFS
				}

			private:
				std::vector<T> visited;
				std::vector<T> storage; // stack or fifo
				list_graph searchable_graph;
		};

} // namespace libgraph

#endif // SEARCH_H

