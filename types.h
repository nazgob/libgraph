#ifndef TYPES_H
#define TYPE_H

#include <boost/mpl/list.hpp>

#include "node.h"
#include "graph.h"
#include "search.h"

namespace libgraph 
{

	typedef graph<int, graph_memory_model<int, linked_list> > list_graph;
	typedef graph<int, graph_memory_model<int, matrix> > matrix_graph;

	typedef graph_memory_model<int, linked_list> list_graph_memory_model;
	typedef graph_memory_model<int, matrix> matrix_graph_memory_model;

	// boost::mpl::list-s are for BOOST_AUTO_TEST_CASE_TEMPLATE
	typedef boost::mpl::list<int, double, size_t> nodes_types;
	typedef boost::mpl::list<matrix_graph, list_graph> graph_types;
	typedef boost::mpl::list<graph_memory_model<int, linked_list>, graph_memory_model<int, matrix> > memory_models;
	//typedef boost::mpl::list<std::stack<int>, queue_adapter<int> > search_structures; // TODO: ???

} // namespace libgraph 

#endif // TYPES_H

