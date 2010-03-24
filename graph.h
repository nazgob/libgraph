#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <utility>
#include <cassert>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "node.h"

namespace advcpp
{
	enum memory {linked_list, matrix};

	template<typename T, memory>
		class memory_selector
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
		class memory_selector<T, linked_list>
		{
			public:
				memory_selector<T, linked_list>() : id(0)
				{
				}

				void add(node<T>& input_node) // add node
				{
					if(!is_node(input_node.value))
					{
						input_node.id = id++;
						std::list<T> new_list;
						storage.push_back(std::make_pair(input_node, new_list));
					}
				}

				void remove(node<T>& input_node) // remove node
				{
					std::list<T> tmp_list;
					typename node_list_pair<T>::type tmp_pair(input_node, tmp_list);

					storage.erase(std::remove_if(storage.begin(), storage.end(), boost::lambda::_1 == tmp_pair), storage.end());
				}

				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
					//std::cout << std::endl << std::endl << std::endl;
					//std::cout << "got begin_node.id = " << begin_node.id << std::endl;
					//std::cout << "got end_node.id = " << end_node.id << std::endl;

					size_t begin_id = begin_node.id;
					size_t end_id = end_node.id;
				
					bool is_begin_node = is_node(begin_node.value);
					bool is_end_node = is_node(end_node.value);
				
					//std::cout << "is_begin_node = " << is_begin_node << std::endl;
					//std::cout << "is_end_node = " << is_end_node << std::endl;

					if(!is_begin_node)
					{
						//std::cout << "inserting begin_node!" << std::endl;
						add(begin_node);
						begin_id++;
					}
					else
					{
						begin_id = get_node_id(begin_node.value);
					}
					if(!is_end_node)
					{
						//std::cout << "inserting end_node!" << std::endl;
						add(end_node);
						end_id++;
					}
					else
					{
						end_node.id = get_node_id(end_node.value);
					}

					storage.at(begin_id).second.push_back(end_id);
					storage.at(end_id).second.push_back(begin_id);
				}

				void remove(node<T>& begin_node, node<T>& end_node) // remove arc
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

					assert(false); // TODO: do not allow to ask get_node_id for not existing nodes
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
				size_t id;
		};

	template<typename T>
		class memory_selector<T, matrix>
		{
			public:
				memory_selector<T, matrix>() : id(0)
				{
				}

				void add(node<T>& input_node) // add node
				{

					if(!is_node(input_node.value))
					{
						input_node.id = id++;
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

				void remove(node<T>& input_node) // remove node
				{
					storage.erase(std::remove(storage.begin(), storage.end(), input_node), storage.end());
					//TODO: what to do with matrix2D? mark deleted row with 0 or some logiacal flag?
				}


				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
					begin_node.id = id++;
					end_node.id = id++;

					// TODO: ids are messed up seriously / check adding existing nodes as arcs
					size_t begin_id = begin_node.id;
					size_t end_id = end_node.id;

					add(begin_node);
					add(end_node);

					matrix2D.at(begin_id).at(end_id) = 1; // perhaps some clever enum?
					matrix2D.at(end_id).at(begin_id) = 1; // perhaps some clever enum?
				}

				void remove(node<T>& begin_node, node<T>& end_node) // remove arc
				{

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
				size_t id;
		};

	template<typename T, typename Memory = memory_selector<T, matrix> >
		class graph
		{
			public:
				graph()// : id(0)
				{
				}

				void add(node<T>& input_node) // add node
				{
					//input_node.id = id++;
					containter.add(input_node);
				}
				
				void remove(node<T>& input_node) // remove node
				{
					containter.remove(input_node);
				}

				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
					if(begin_node == end_node)
					{
						// pass
						return;
					}

					//begin_node.id = id++;
					//end_node.id = id++;
					containter.add(begin_node, end_node);
				}

				void remove(node<T>& begin_node, node<T>& end_node) // remove arc
				{
					containter.remove(begin_node, end_node);
				}

				/*node<T> get_node(const T& value) const
				{
					return containter.get_node(value);
				}*/

				size_t size() const
				{
					return containter.size();
				}

				void reserve(size_t size)
				{
					containter.reserve(size);
				}


			protected:
				//size_t id;
				Memory containter;
		};
} // namespace advcpp

#endif // GRAPH_H

