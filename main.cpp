#define BOOST_TEST_MODULE graph main_tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "graph.h"
#include "node.h"

#include <vector>

using namespace advcpp;

typedef graph<int, memory_selector<int, linked_list> > list_graph;
typedef graph<int, memory_selector<int, matrix> > matrix_graph;

typedef boost::mpl::list<int, double, size_t> nodes_types;
typedef boost::mpl::list<matrix_graph, list_graph> graph_types;

BOOST_AUTO_TEST_CASE(InstantiateDifferentGraphs)
{
	graph<long> g;
	graph<int, memory_selector<int, linked_list> > g1;
	graph<double, memory_selector<double, matrix> > g2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(NodesEqualityTest, T, nodes_types)
{
	node<T> n1(1);
    node<T> n2(1);
	BOOST_REQUIRE(n1 == n2);

	node<T> n3(2);
	BOOST_REQUIRE(n1 != n3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(NodesIdTest, T, nodes_types)
{
	// node id has sense only when node is added to the graph
	node<T> n(1);
	BOOST_REQUIRE_EQUAL(n.id, 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddRemoveNodesTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(2);
	node<int> n3(3);

	T g;
	g.reserve(3);
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(n1);
	BOOST_REQUIRE_EQUAL(g.size(), 1);

	g.add(n2);
	BOOST_REQUIRE_EQUAL(g.size(), 2);

	g.add(n3);
	BOOST_REQUIRE_EQUAL(g.size(), 3);

	g.remove(n1);
	BOOST_REQUIRE_EQUAL(g.size(), 2);

	g.remove(n2);
	BOOST_REQUIRE_EQUAL(g.size(), 1);

	g.remove(n3);
	BOOST_REQUIRE_EQUAL(g.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(FindNodeTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(2);
	node<int> n3(3);

	//T g;
	list_graph g;
	g.reserve(3);

	g.add(n1);
	g.add(n2);
	g.add(n3);

	BOOST_REQUIRE_EQUAL(g.get_node(3).value, 3);
	BOOST_REQUIRE_EQUAL(g.get_node(2).value, 2);
	BOOST_REQUIRE_EQUAL(g.get_node(1).value, 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddDuplicateNodesTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(1);
	node<int> n3(1);

	T g;
	g.reserve(3);
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(n1);
	BOOST_REQUIRE_EQUAL(g.size(), 1);
	g.add(n2);
	g.add(n3);
	BOOST_REQUIRE_EQUAL(g.size(), 1);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(AddArcTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(2);

	T g;
	g.reserve(2);
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(n1, n2);
	BOOST_REQUIRE_EQUAL(g.size(), 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddSameNodeAsArcTest, T, graph_types)
{
	node<int> n(1);

	T g;
	g.reserve(2);
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(n, n);
	BOOST_REQUIRE_EQUAL(g.size(), 0);
}

/*BOOST_AUTO_TEST_CASE_TEMPLATE(DepthFirstSearchTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(2);
	node<int> n3(3);
	node<int> n4(4);
	node<int> n5(5);

	//T g;
	list_graph g;
	g.reserve(5);
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	// circle graph
	g.add(n1, n2);
	g.add(n2, n3);
	g.add(n3, n4);
	g.add(n4, n5);
	g.add(n5, n1);

	BOOST_REQUIRE_EQUAL(g.size(), 5);
}*/


