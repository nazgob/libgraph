#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <list>

#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "node.h"


namespace libgraph
{
	enum memory {linked_list, matrix};

	template<typename T, memory>
		class graph_memory_model
		{
		};

	template<typename T>
		class node_list_pair // idiom to have templated typedef
		{
			public:
				typedef std::pair<node<T>, std::list<T> > type;
		};

	template<typename T>
		class vector_containter // idiom to have templated typedef
		{
			public:
				typedef std::vector<typename node_list_pair<T>::type > type;
		};


	template<typename T>
		bool operator==(const typename node_list_pair<T>::type & lhs, const typename node_list_pair<T>::type & rhs)
		{
			return lhs.first.value == rhs.first.value;
		}

	template<typename T>
		class graph_memory_model<T, linked_list>
		{
			public:
				graph_memory_model<T, linked_list>()
				{
				}

				void add(node<T>& input_node) // add node
				{

				}

				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{

				}

				bool is_node(const T& value) const
				{
					for(typename vector_containter<T>::type::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if(it->first.value == value)
						{
							return true;
						}
					}
					return false;
				}

				T get_node_id(const T& value) const
				{
					for(typename vector_containter<T>::type::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if(it->first.value == value)
						{
							return it->first.id;
						}
					}
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
				typename vector_containter<T>::type storage;
		};

	template<typename T>
		class graph_memory_model<T, matrix>
		{
			public:
				graph_memory_model<T, matrix>()
				{
				}

				void add(node<T>& input_node) // add node
				{

					if(!is_node(input_node.value))
					{
						//input_node.id = id++;
						storage.push_back(input_node);
						std::vector<int> row(matrix2D.size());
						matrix2D.push_back(row);

						for(std::vector<std::vector<int> >::iterator it = matrix2D.begin();
								it != matrix2D.end();
								++it)
						{
							(*it).push_back(0);
						}

						// TODO: make propper tests for that and get rid of this assert
						assert(storage.size() == matrix2D.size());
						for(std::vector<std::vector<int> >::iterator it = matrix2D.begin();
								it != matrix2D.end();
								++it)
						{
							assert((*it).size() == storage.size());
						}
					}

				}


				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
					//begin_node.id = id++;
					//end_node.id = id++;

					// TODO: ids are messed up seriously / check adding existing nodes as arcs
					//size_t begin_id = begin_node.id;
					//size_t end_id = end_node.id;

					add(begin_node);
					add(end_node);

					//matrix2D.at(begin_id).at(end_id) = 1; // perhaps some clever enum?
					//matrix2D.at(end_id).at(begin_id) = 1; // perhaps some clever enum?
				}

				bool is_node(const T& value) const
				{
					for(typename std::vector<node<T> >::const_iterator it = storage.begin(); it != storage.end(); ++it)
					{
						if(it->value == value)
						{
							return true;
						}
					}
					return false;
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

				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
					if(begin_node == end_node)
					{
						// pass
						return;
					}

					containter.add(begin_node, end_node);
				}

				size_t size() const
				{
					return containter.size();
				}

				void reserve(size_t size)
				{
					containter.reserve(size);
				}

				const Memory& get_memory() const
				{
					return containter;
				}

			protected:
				Memory containter;
		};
} // namespace libgraph

#endif // GRAPH_H

