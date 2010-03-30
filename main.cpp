#define BOOST_TEST_MODULE libgraph main_tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include "node.h"
#include "graph.h"
//#include "search.h"
#include "types.h"

//#include <queue>
#include <stack>
#include <vector>

using namespace libgraph;

BOOST_AUTO_TEST_CASE(InstantiateDifferentGraphs)
{
	graph<long> g;
	graph<int, graph_memory_model<int, linked_list> > l;
	graph<double, graph_memory_model<double, matrix> > m;

	BOOST_REQUIRE_EQUAL(g.size(), 0);
	BOOST_REQUIRE_EQUAL(l.size(), 0);
	BOOST_REQUIRE_EQUAL(m.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(NodesEqualityTest, T, nodes_types)
{
	node<T>::reset(); // this is why statics / globals are bad from testablity POV.

	node<T> n1(1);
	node<T> n2(1);
	BOOST_REQUIRE(n1 != n2);

	node<T> n3(2);
	BOOST_REQUIRE(n1 != n3);
	BOOST_REQUIRE(n1 == n1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(NodesIdTest, T, nodes_types)
{
	node<T>::reset();

	node<T> n1(1);
	node<T> n2(2);
	node<T> n3(3);
	BOOST_REQUIRE_EQUAL(n1.id, 0);
	BOOST_REQUIRE_EQUAL(n2.id, 1);
	BOOST_REQUIRE_EQUAL(n3.id, 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddArcTest, T, graph_types)
{
	node<int>::reset();

	T g;
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(1, 2);
	BOOST_REQUIRE_EQUAL(g.size(), 2);

	g.add(2, 3);
	BOOST_REQUIRE_EQUAL(g.size(), 3);

	g.add(3, 2);
	BOOST_REQUIRE_EQUAL(g.size(), 3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(AddSameValuesAsArcTest, T, graph_types)
{
	node<int>::reset();

	T g;
	BOOST_REQUIRE_EQUAL(g.size(), 0);

	g.add(1, 1);
	BOOST_REQUIRE_EQUAL(g.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(IsNodeTest, T, graph_types)
{
	node<int>::reset();

	T g;
	BOOST_REQUIRE_EQUAL(g.size(), 0);
	g.add(1, 2);
	g.add(2, 3);
	g.add(3, 1);
	BOOST_REQUIRE_EQUAL(g.size(), 3);

	BOOST_REQUIRE(g.is_node(1).get()->is_null() == false);
	BOOST_REQUIRE(g.is_node(2).get()->is_null() == false);
	BOOST_REQUIRE(g.is_node(3).get()->is_null() == false);

	BOOST_REQUIRE(g.is_node(5).get()->is_null() == true);
	BOOST_REQUIRE(g.is_node(6).get()->is_null() == true);
	BOOST_REQUIRE(g.is_node(7).get()->is_null() == true);
}

//BOOST_AUTO_TEST_CASE_TEMPLATE(DepthFirstSearchTest, T, graph_types)
/*BOOST_AUTO_TEST_CASE(DepthFirstSearchTest)
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

search_graph<int, std::stack<int>, list_graph_memory_model > s(g);
s.search(n1);

node<T>::reset();
}*/

