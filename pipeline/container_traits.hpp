

#pragma once

namespace foam
{
	namespace pipeline
	{
		template<typename Container>
		struct container_traits
		{
			typedef typename Container::value_type     value_type;
			typedef typename Container::const_iterator iiterator;
		};

		template<typename T, int N>
		struct container_traits<T[N]>
		{
			typedef T        value_type;
			typedef T const* iiterator;
		};
	}
}
