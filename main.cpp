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
typedef graph<int> default_graph;

typedef boost::mpl::list<int, double, size_t> nodes_types;
typedef boost::mpl::list<default_graph, matrix_graph, list_graph> graph_types;

BOOST_AUTO_TEST_CASE(InstantiateDifferentGraphs)
{
	graph<long> g;
	graph<int, memory_selector<int, linked_list> > g1;
	graph<double, memory_selector<double, matrix> > g2;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(NodesEqualityTest, T, nodes_types)
{
	T n1(1);
    T n2(1);
	BOOST_REQUIRE(n1 == n2);

	T n3(2);
	BOOST_REQUIRE(n1 != n3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddRemoveNodesTest, T, graph_types)
{
	node<int> n1(1);
	node<int> n2(2);
	node<int> n3(3);

	T g;
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

