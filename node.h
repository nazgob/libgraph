#ifndef NODE_H
#define NODE_H

namespace libgraph
{
	template<typename T>
		class node 
		{
			public:
				explicit node(const T& input) : value(input), id(0) // does this explicit works / is neccesery?
			{
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
		};
} // namespace libgraph

#endif // NODE_H

