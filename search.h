#ifndef SEARCH_H
#define SEARCH_H

#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

#include <boost/shared_ptr.hpp>
//#include <boost/lambda/lambda.hpp>

#include "types.h"
#include "graph.h"
#include "node.h"

namespace libgraph 
{
	template<class T>
		class queue_adapter // stack has top() method but queue has front()...
		{
			public:
				queue_adapter()
				{
				}
				
				T& top() 
				{
					queue_with_top.front();
				}

				void pop()
				{
					queue_with_top.pop();
				}

				bool empty() const
				{
					return queue_with_top.empty();
				}

				void push(const T& e) 
				{
					queue_with_top.push(e);
				}

			private:
				std::queue<T> queue_with_top;
		};

	template<typename T, typename search_memory_model, typename searchable_graph_memory_model>
		class search_graph
		{
			public:
				search_graph(const list_graph& g)
				{
					storage = g.get_memory().storage;
					adjectedListsVec = g.get_memory().adjectedListsVec;
				}

				bool search(T root_node_value, T seeked_value_node)
				{
					goal = seeked_value_node;
					for(typename std::vector<node_ptr>::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if((*it)->value == seeked_value_node)
						{
							return true;	
						}

						if((*it)->value == root_node_value)
						{
							if(visitDFS(*it) == true)
							{
								return true;
							}
						}
					}
					reset();
					return false;
				}

				void display_search_path() const
				{
					std::copy(search_path.begin(), search_path.end(), std::ostream_iterator<T>(std::cout, " -> "));
					std::cout << std::endl;
				}

				void reset()
				{
					closed.clear();
					search_path.clear();

					while (!open.empty())
					{
						open.pop(); // stack does not have a clear method...
					}

					search_path.clear();
				}

			protected:

				bool visitDFS(boost::shared_ptr<node<T> > node) 
				{
					search_status = false;
					if(closed.find(node->id) == closed.end())
					{
						open.push(node->id);
					}
					while(!open.empty())
					{
						search_path.push_back(node->id);
						closed.insert(node->id);
						if(node->value == goal)
						{
							search_status = true;
							return true;
						}
						std::list<T> tmp_list = *(adjectedListsVec[node->id].get());
						for(typename std::list<T>::const_iterator it = tmp_list.begin(); it != tmp_list.end(); ++it)
						{
							if(closed.find(*it) == closed.end())
							{
								open.push(*it);
							}
						}
						size_t tmp_id = open.top();
						open.pop();

						if(search_status == true) return true;

						visitDFS(storage[tmp_id]);
					}

					if(search_status == true) return true;
				}

			private:
				typedef boost::shared_ptr<node<T> > node_ptr;
				std::vector<node_ptr> storage;

				typedef boost::shared_ptr<std::list<T> > list_ptr;
				std::vector<list_ptr> adjectedListsVec;

				bool search_status;
				T goal;
				std::set<T> closed;
				search_memory_model open;
				std::vector<T> search_path;
		};

} // namespace libgraph

#endif // SEARCH_H

