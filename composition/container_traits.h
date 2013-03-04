

#pragma once

namespace foam
{
	namespace composition
	{
		template<typename Container>
		struct container_traits
		{
			typedef typename Container::const_iterator iterator;
			typedef typename Container::value_type     value_type;
		};

		template<typename T, int N>
		struct container_traits<T[N]>
		{
			typedef T const* iterator;
			typedef T        value_type;
		};
	}
}
