#ifndef NODE_H
#define NODE_H

namespace advcpp
{
	template<typename T>
		class node 
		{
			public:
				explicit node(const T& input) : value(input), id(0) // does this explicit works / is neccesery?
			{
				id = ++nextId;
			}

				bool operator==(const node<T>& n) const
				{
					return value == n.value;
				}

				bool operator!=(const node<T>& n) const
				{
					return value != n.value;
				}

				T value;
				size_t id;

			protected:
				static int nextId;
		};

	template<typename T> int node<T>::nextId = 0;
}

#endif // NODE_H

