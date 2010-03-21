#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <list>
#include <utility>

#include <boost/lambda/lambda.hpp>
//using namespace boost::lambda;

#include "node.h"

namespace advcpp
{
	enum memory {linked_list, matrix};

	template<typename T, memory>
		class memory_selector
		{
			public:
				void boom()
				{
					// std::cout << "boom" << std::endl;
				}
		};

	//typedef std::pair<node<int>, std::list<int> > node_list_pair;
	template<typename T>
		class node_list_pair // idiom to have templated typedef
		{
			public:
				typedef std::pair<node<T>, std::list<T> > type;
		};

	template<typename T>
		bool operator==(const typename node_list_pair<T>::type & lhs, const typename node_list_pair<T>::type & rhs)
		{
			//std::cout << "comparing pairs = " << lhs.first.id << " " << rhs.first.id << std::endl;
			return lhs.first.id == rhs.first.id;
		}

	template<typename T>
		class memory_selector<T, linked_list>
		{
			public:
				void boom()
				{
					// std::cout << "boom linked_list" << std::endl;
				}
				void add(node<T>& input_node)
				{
					std::list<T> new_list;
					storage.push_back(std::make_pair(input_node, new_list)); 
				}
				void remove(node<T>& input_node)
				{
					std::list<T> tmp_list;
					typename node_list_pair<T>::type tmp_pair(input_node, tmp_list);
					typename node_list_pair<T>::type tmp_pair2(input_node, tmp_list);

					storage.erase(std::remove_if(storage.begin(), storage.end(), boost::lambda::_1 == tmp_pair), storage.end());
				}
				size_t size() const
				{
					return storage.size();
				}
			protected:
				std::vector<typename node_list_pair<T>::type > storage;
		};

	template<typename T>
		class memory_selector<T, matrix>
		{
			public:
				void boom()
				{
					// std::cout << "boom matrix" << std::endl;
				}
				void add(node<T>& input_node)
				{
					storage.push_back(input_node);
				}
				void remove(node<T>& input_node)
				{
					storage.erase(std::remove(storage.begin(), storage.end(), input_node), storage.end());
				}
				size_t size() const
				{
					return storage.size();
				}
			protected:
				std::vector<node<T> > storage;
		};

	template<typename T, typename Memory = memory_selector<T, matrix> >
		class graph
		{
			public:
				graph()
				{
					containter.boom();
				}

				void add(node<T>& input_node) // add node
				{
					containter.add(input_node);
				}

				void add(node<T>& begin_node, node<T>& end_node) // add arc
				{
				}

				void remove(node<T>& input_node) // remove node
				{
					containter.remove(input_node);
				}

				void remove(node<T>& input_node, node<T>& end_node) // remove arc
				{
				}

				size_t size() const
				{
					return containter.size();
				}

			protected:
				Memory containter;
		};
} // namespace advcpp

#endif // GRAPH_H

