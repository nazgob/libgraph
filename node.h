#ifndef NODE_H
#define NODE_H

namespace libgraph
{
	template<typename T>
		class node 
		{
			public:
				node(const T& input) : value(input)
			{
				id = counter++; // counting from 0 is handy in C++
			}
				static void reset()
				{
					counter = 0;
				}

				bool operator==(const node<T>& n) const
				{
					return (value == n.value) && (id == n.id);
				}

				bool operator!=(const node<T>& n) const
				{
					return (value != n.value) || (id != n.id);
				}

				T value;
				size_t id;
			private:
				static size_t counter;
		};

	template<typename T>
	size_t node<T>::counter = 0;
} // namespace libgraph

#endif // NODE_H

