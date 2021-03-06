#define BOOST_TEST_MODULE libgraph main_tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include <queue>
#include <stack>
#include <vector>

#include "node.hpp"
#include "graph.hpp"
#include "search.hpp"
#include "types.hpp"

using namespace libgraph;

BOOST_AUTO_TEST_CASE(InstantiateDifferentGraphs)
{
  graph<long> g;
  graph<int, graph_memory_model<int, list> > l;
  graph<double, graph_memory_model<double, matrix> > m;

  BOOST_REQUIRE_EQUAL(g.size(), 0);
  BOOST_REQUIRE_EQUAL(l.size(), 0);
  BOOST_REQUIRE_EQUAL(m.size(), 0);
}

BOOST_AUTO_TEST_CASE(QueueAdapterTest)
{
  queue_adapter<int> q;
  BOOST_REQUIRE(q.empty() == true);
  q.push(1);
  q.push(2);
  q.push(3);
  BOOST_REQUIRE(q.empty() == false);
  BOOST_REQUIRE_EQUAL(q.top(), 1);

  q.pop();
  BOOST_REQUIRE_EQUAL(q.top(), 2);

  q.pop();
  BOOST_REQUIRE_EQUAL(q.top(), 3);

  q.pop();
  BOOST_REQUIRE(q.empty() == true);
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

BOOST_AUTO_TEST_CASE(LinkedListMemoryModelTest)
{
  node<int>::reset();

  graph_memory_model<int, list> m;
  BOOST_REQUIRE_EQUAL(m.size(), 0);

  m.add(1, 2);
  BOOST_REQUIRE_EQUAL(m.size(), 2);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.size(), 2);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.at(0)->size(), 1);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.at(1)->size(), 1);


  m.add(2, 3);
  BOOST_REQUIRE_EQUAL(m.size(), 3);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.size(), 3);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.at(0)->size(), 1);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.at(1)->size(), 2);
  BOOST_REQUIRE_EQUAL(m.adjectedListsVec.at(2)->size(), 1);
}

BOOST_AUTO_TEST_CASE(MatrixMemoryModelTest)
{
  node<int>::reset();

  const size_t fixed_matix_size = 3;
  graph_memory_model<int, matrix> m(fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.size(), 0);
  BOOST_REQUIRE_EQUAL(m.matrix2D.size(), fixed_matix_size);

  m.add(1, 2);
  BOOST_REQUIRE_EQUAL(m.size(), 2);
  BOOST_REQUIRE_EQUAL(m.matrix2D.size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).size(), fixed_matix_size);

  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(0), 0); // 1
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(0), 1); // 2
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(0), 0); // 3
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(1), 1); // 4
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(1), 0); // 5
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(1), 0); // 6
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(2), 0); // 7
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(2), 0); // 8
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(2), 0); // 9

  m.add(2, 3);
  BOOST_REQUIRE_EQUAL(m.size(), 3);
  BOOST_REQUIRE_EQUAL(m.matrix2D.size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).size(), fixed_matix_size);
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).size(), fixed_matix_size);

  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(0), 0); // 1
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(0), 1); // 2
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(0), 0); // 3
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(1), 1); // 4
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(1), 0); // 5
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(1), 1); // 6
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(0).at(2), 0); // 7
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(1).at(2), 1); // 8
  BOOST_REQUIRE_EQUAL(m.matrix2D.at(2).at(2), 0); // 9
}

BOOST_AUTO_TEST_CASE(DepthFirstSearchTest_List)
{
  node<int>::reset();

  list_graph g;

  BOOST_REQUIRE_EQUAL(g.size(), 0);

  // circle graph
  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 4);
  g.add(4, 5);
  g.add(5, 1);
  BOOST_REQUIRE_EQUAL(g.size(), 5);

  search_graph<int, std::stack<int>, list_graph_internal_model> s(g);

  BOOST_REQUIRE(s.search(1, 10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, 7) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, -5) == false);
  s.reset();

  BOOST_REQUIRE(s.search(0, -10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(10, 100) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, 1) == true);
  s.reset();

  BOOST_REQUIRE(s.search(1, 2) == true);
  s.reset();

  BOOST_REQUIRE(s.search(5, 3) == true);
  s.reset();

  BOOST_REQUIRE(s.search(2, 4) == true);
  s.reset();

  BOOST_REQUIRE(s.search(3, 5) == true);
  s.reset();
}

BOOST_AUTO_TEST_CASE(DepthFirstSearchTest_Matrix)
{
  node<int>::reset();

  matrix_graph g(5);
  BOOST_REQUIRE_EQUAL(g.size(), 0);

  // circle graph
  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 4);
  g.add(4, 5);
  g.add(5, 1);
  BOOST_REQUIRE_EQUAL(g.size(), 5);

  search_graph<int, std::stack<int>, matrix_graph_internal_model> s(g);

  BOOST_REQUIRE(s.search(1, 10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, 7) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, -5) == false);
  s.reset();

  BOOST_REQUIRE(s.search(0, -10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(10, 100) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, 1) == true);
  s.reset();

  BOOST_REQUIRE(s.search(1, 2) == true);
  s.reset();

  BOOST_REQUIRE(s.search(5, 3) == true);
  s.reset();

  BOOST_REQUIRE(s.search(2, 4) == true);
  s.reset();

  BOOST_REQUIRE(s.search(3, 5) == true);
  s.reset();
}

BOOST_AUTO_TEST_CASE(BreadFirstSearchTest_List)
{
  node<int>::reset();

  list_graph g;
  BOOST_REQUIRE_EQUAL(g.size(), 0);

  // circle graph
  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 4);
  g.add(4, 5);
  g.add(5, 1);
  BOOST_REQUIRE_EQUAL(g.size(), 5);

  search_graph<int, queue_adapter<int>, list_graph_internal_model > s(g);
  BOOST_REQUIRE(s.search(2, 10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, 7) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, -5) == false);
  s.reset();

  BOOST_REQUIRE(s.search(7, -10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(50, 100) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, 1) == true);
  s.reset();

  BOOST_REQUIRE(s.search(1, 2) == true);
  s.reset();

  BOOST_REQUIRE(s.search(5, 3) == true);
  s.reset();

  BOOST_REQUIRE(s.search(2, 4) == true);
  s.reset();

  BOOST_REQUIRE(s.search(3, 5) == true);
  s.reset();
}

BOOST_AUTO_TEST_CASE(BreadFirstSearchTest_Matrix)
{
  node<int>::reset();

  matrix_graph g(5);
  BOOST_REQUIRE_EQUAL(g.size(), 0);

  // circle graph
  g.add(1, 2);
  g.add(2, 3);
  g.add(3, 4);
  g.add(4, 5);
  g.add(5, 1);
  BOOST_REQUIRE_EQUAL(g.size(), 5);

  search_graph<int, queue_adapter<int>, matrix_graph_internal_model > s(g);
  BOOST_REQUIRE(s.search(2, 10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, 7) == false);
  s.reset();

  BOOST_REQUIRE(s.search(3, -5) == false);
  s.reset();

  BOOST_REQUIRE(s.search(7, -10) == false);
  s.reset();

  BOOST_REQUIRE(s.search(50, 100) == false);
  s.reset();

  BOOST_REQUIRE(s.search(1, 1) == true);
  s.reset();

  BOOST_REQUIRE(s.search(1, 2) == true);
  s.reset();

  BOOST_REQUIRE(s.search(5, 3) == true);
  s.reset();

  BOOST_REQUIRE(s.search(2, 4) == true);
  s.reset();

  BOOST_REQUIRE(s.search(3, 5) == true);
  s.reset();
}

BOOST_AUTO_TEST_CASE(work_in_progress)
{
  node<int>::reset();
  list_graph lg;
  matrix_graph mg;

  search_graph<int, std::stack<int>, list_graph_internal_model> l(lg);
  search_graph<int, std::stack<int>, matrix_graph_internal_model> m(mg);

  abstract_memory_model<int, list> amm;
}

