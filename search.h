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
	template<typename T, typename search_memory_model, typename searchable_graph_memory_model>
		class search_graph
		{
			public:
				search_graph(const list_graph& g)
			{
				storage = g.get_memory().storage;
				adjectedListsVec = g.get_memory().adjectedListsVec;
			}

				bool search(T start_node_value, T seeked_value)
				{
					goal = seeked_value;
					for(typename std::vector<node_ptr>::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						std::cout << std::endl;
						std::cout << "searching for goal, got = " << (*it)->value << std::endl;
						if(visitDFS(*it) == true)
						{
							std::cout <<  "got true, returning with glory!" << std::endl;
							return true;
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
					if(closed.find(node->id) == closed.end())
					{
						std::cout << "node->id not in closed list = " << node->id << std::endl;
						closed.insert(node->id);
						search_path.push_back(node->id);

						if(node->value == goal)
						{
							std::cout << "found goal! node-> value == " <<  node->value << std::endl;
							return true;
						}

						std::list<T> tmp_list = *(adjectedListsVec[node->id].get());
						for(typename std::list<T>::const_iterator it = tmp_list.begin(); it != tmp_list.end(); ++it)
						{
							std::cout << "inserting adj_list ids to stack!" << std::endl;
							open.push(*it);
						}
						
						size_t tmp_id = open.top();
						open.pop();

						visitDFS(storage[tmp_id]);
					}

					std::cout << "node->id is on closed list = " << node->id << std::endl;
					return false;
				}

			private:
				typedef boost::shared_ptr<node<T> > node_ptr;
				std::vector<node_ptr> storage;

				typedef boost::shared_ptr<std::list<T> > list_ptr;
				std::vector<list_ptr> adjectedListsVec;

				T goal;
				std::set<T> closed;
				std::stack<T> open; // stack or fifo, to be injected as type
				std::vector<T> search_path;
		};

} // namespace libgraph

#endif // SEARCH_H

