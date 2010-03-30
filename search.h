#ifndef SEARCH_H
#define SEARCH_H

#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>

#include "types.h"
#include "graph.h"
#include "node.h"

namespace libgraph 
{	
	template<typename T, typename search_memory_model, typename searchable_graph_memory_model>
		class search_graph
		{
			public:
				search_graph(const list_graph& g) : searchable_graph(g)
			{
			}

				bool search(T start_node_value, T seeked_value)
				{
					return false;
				}

			protected:

				bool visitDFS(boost::shared_ptr<node<T> > node) 
				{

				}

			private:
				std::vector<T> visited;
				std::vector<T> storage; // stack or fifo
				list_graph searchable_graph;
		};

} // namespace libgraph

#endif // SEARCH_H

