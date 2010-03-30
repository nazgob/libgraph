#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <list>

#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

#include <boost/shared_ptr.hpp>

#include "node.h"


namespace libgraph
{
	enum memory {linked_list, matrix};

	template<typename T, memory>
		class graph_memory_model
		{
		};

	template<typename T>
		class graph_memory_model<T, linked_list>
		{
			public:
				graph_memory_model<T, linked_list>()
				{
				}

				boost::shared_ptr<node<T> > is_node(const T& value) const
				{
					//std::cout << "searching for value: " << value << std::endl;
					for(typename std::vector<node_ptr>::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if((*it)->value == value)
						{
							//std::cout << "found it!" << std::endl;
							return *it;
						}
					}
					//std::cout << "can't find it!" << std::endl;
					return node_ptr(new node<T>(NULL, true)); // NULL object idiom
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					//std::cout << "add() = " << begin_node << " " << end_node << std::endl;
					if(begin_node == end_node)
					{
						//std::cout << "same node! nothing added!" << std::endl;
						return;
					}

					size_t aId = 0;
					size_t bId = 0;

					node_ptr aTestResult = is_node(begin_node);
					if(aTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(begin_node));
						//std::cout << "adding begin_node with id = " << pNode->id << std::endl;
						aId = pNode->id;
						pNode->null = false;
						storage.push_back(pNode);
						adjectedListsVec.push_back(list_ptr(new std::list<T>));
					}
					else
					{
						//std::cout << "begin_node exists, getting id" << std::endl;
						aId = aTestResult->id;
					}

					node_ptr bTestResult = is_node(end_node);
					if(bTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(end_node));
						//std::cout << "adding end_node with id = " << pNode->id << std::endl;
						bId = pNode->id;
						pNode->null = false;
						storage.push_back(pNode);
						adjectedListsVec.push_back(list_ptr(new std::list<T>));
					}
					else
					{
						//std::cout << "end_node exists, getting id" << std::endl;
						bId = bTestResult->id;
					}

					adjectedListsVec[aId]->push_back(bId);
					adjectedListsVec[aId]->unique();

					adjectedListsVec[bId]->push_back(aId);
					adjectedListsVec[bId]->unique();

					assert(storage.size() == adjectedListsVec.size());
				}	

				size_t size() const
				{
					return storage.size();
				}

				void reserve(size_t size)
				{
					storage.reserve(size);
				}

			protected:
				typedef boost::shared_ptr<node<T> > node_ptr;
				std::vector<node_ptr> storage;

				typedef boost::shared_ptr<std::list<T> > list_ptr;
				std::vector<list_ptr> adjectedListsVec;
		};

	template<typename T>
		class graph_memory_model<T, matrix>
		{
			public:
				graph_memory_model<T, matrix>()
				{
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					assert(false);
				}

				boost::shared_ptr<node<T> > is_node(const T& value) const
				//node<T>* is_node(const T& value) const
				{
					return node_ptr(new node<T>(NULL, true)); // NULL object idiom
				}

				size_t size() const
				{
					return storage.size();
				}

				void reserve(size_t size)
				{
					storage.reserve(size);
					matrix2D.reserve(size); // how to reserve stuff 'inside'? is it possible at all?
				}

			protected:
				std::vector<node<T> > storage;
				std::vector<std::vector<int> > matrix2D;
		};

	template<typename T, typename Memory = graph_memory_model<T, matrix> >
		class graph
		{
			public:
				graph()
				{
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					container.add(begin_node, end_node);
				}

				boost::shared_ptr<node<T> > is_node(const T& value) const
				//node<T>* is_node(const T& value) const
				{
					return container.is_node(value);
				}

				size_t size() const
				{
					return container.size();
				}

				void reserve(size_t size)
				{
					container.reserve(size);
				}

				const Memory& get_memory() const
				{
					return container;
				}

			protected:
				Memory container;
		};
} // namespace libgraph

#endif // GRAPH_H

