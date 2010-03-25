#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"
#include "node.h"

namespace libgraph 
{
	template<typename T>
		class search_graph
		{
			public:
				search_graph(graph<int, memory_selector<int, linked_list> > g)
				{
				}

				bool search(node<T> node) const
				{
					return false;
				}
		};

} // namespace libgraph

#endif // SEARCH_H

