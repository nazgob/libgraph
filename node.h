#ifndef NODE_H
#define NODE_H

namespace libgraph
{
	template<typename T>
		class node 
		{
			public:
				node(const T& input, bool nullity = false) : value(input)
			{
				if(false == nullity)
				{
					id = counter++; // counting from 0 is handy in C++
					//std::cout << "creating node with id = " << id << std::endl;
				}
				else
				{
					null = true;
				}
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

				bool is_null() const
				{
					return null;
				}

				T value;
				size_t id;
				bool null;
			private:
				node& operator = (const node& other) {}
				node(const node& other) {}

				static size_t counter;
		};

	template<typename T>
		size_t node<T>::counter = 0;

} // namespace libgraph

#endif // NODE_H

