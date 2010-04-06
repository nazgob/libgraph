#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <list>

#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>
#include <exception>
#include <boost/shared_ptr.hpp>

#include "node.h"


namespace libgraph
{
	enum memory {linked_list, matrix}; // TODO: rename linked_list to list

	const size_t default_matrix_size = 10;

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
					for(typename std::vector<node_ptr>::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if((*it)->value == value)
						{
							return *it;
						}
					}
					return node_ptr(new node<T>(NULL, true)); // NULL object idiom
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					if(begin_node == end_node)
					{
						return;
					}

					size_t aId = 0;
					size_t bId = 0;

					node_ptr aTestResult = is_node(begin_node);
					if(aTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(begin_node));
						aId = pNode->id;
						pNode->null = false;
						storage.push_back(pNode);
						adjectedListsVec.push_back(list_ptr(new std::list<T>));
					}
					else
					{
						aId = aTestResult->id;
					}

					node_ptr bTestResult = is_node(end_node);
					if(bTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(end_node));
						bId = pNode->id;
						pNode->null = false;
						storage.push_back(pNode);
						adjectedListsVec.push_back(list_ptr(new std::list<T>));
					}
					else
					{
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

				typedef boost::shared_ptr<node<T> > node_ptr;
				std::vector<node_ptr> storage;

				typedef boost::shared_ptr<std::list<T> > list_ptr;
				std::vector<list_ptr> adjectedListsVec;
		};

	template<typename T>
		class graph_memory_model<T, matrix>
		{
			public:

				graph_memory_model<T, matrix>() : matrix_size(default_matrix_size)
				{
					initialize_matrix();
				}

				graph_memory_model<T, matrix>(size_t fixed_matrix_size) : matrix_size(fixed_matrix_size)
				{
					if(fixed_matrix_size < 2) // minimum to get one arc into graph
					{
						throw std::invalid_argument("matrix must be minimum 2 rows / cols strong!");
					}
					initialize_matrix();
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					if(begin_node == end_node)
					{
						return;
					}

					size_t aId = 0;
					size_t bId = 0;

					node_ptr aTestResult = is_node(begin_node);
					if(aTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(begin_node));
						aId = pNode->id;
						pNode->null = false;
						if(pNode->id > matrix_size)
						{
							std::ostringstream msg;
							msg << "node id " << pNode->id << " is greater than maximum matrix size " << matrix_size << "!";
							throw std::invalid_argument(msg.str()); // TODO: add test for that
						}
						storage.push_back(pNode);
					}
					else
					{
						aId = aTestResult->id;
					}

					node_ptr bTestResult = is_node(end_node);
					if(bTestResult.get()->is_null())
					{
						node_ptr pNode = node_ptr(new node<T>(end_node));
						bId = pNode->id;
						pNode->null = false;
						if(pNode->id >matrix_size)
						{
							std::ostringstream msg;
							msg << "node id " << pNode->id << " is greater than maximum matrix size " << matrix_size << "!";
							throw std::invalid_argument(msg.str()); // TODO: add test for that
						}
						storage.push_back(pNode);
					}
					else
					{
						bId = bTestResult->id;
					}
					matrix2D.at(aId).at(bId) = 1;
					matrix2D.at(bId).at(aId) = 1;
				}

				boost::shared_ptr<node<T> > is_node(const T& value) const
				{
					for(typename std::vector<node_ptr>::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if((*it)->value == value)
						{
							return *it;
						}
					}
					return node_ptr(new node<T>(NULL, true)); // NULL object idiom
				}

				size_t size() const
				{
					return storage.size();
				}

				void reserve(size_t size)
				{
					storage.reserve(size);
				}

				typedef boost::shared_ptr<node<T> > node_ptr;
				std::vector<node_ptr> storage;
				
				std::vector<std::vector<int> > matrix2D;
				const size_t matrix_size;
			protected:

				void initialize_matrix()
				{
					for(size_t i = 0; i < matrix_size; ++i)
					{
						matrix2D.push_back(std::vector<int>(matrix_size, 0));
					}
					assert(matrix2D.size() == matrix_size);
					assert(matrix2D[0].size() == matrix_size);
				}
		};

	template<typename T, typename Memory = graph_memory_model<T, matrix> >
		class graph
		{
			public:
				graph()
				{
				}

				graph(size_t size) : fixed_size(size), container(fixed_size)
				{
				}

				void add(const T& begin_node, const T& end_node) // add arc
				{
					container.add(begin_node, end_node);
				}

				boost::shared_ptr<node<T> > is_node(const T& value) const
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
				size_t fixed_size;
				Memory container;
		};
} // namespace libgraph

#endif // GRAPH_H

