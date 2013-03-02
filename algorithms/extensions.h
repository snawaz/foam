
#pragma once

#include <algorithm>
#include <iterator>

namespace foam
{
	namespace extensions
	{
		template<typename InputIterator, typename Container>
		Container& push_back(InputIterator begin, InputIterator end, Container & c)
		{
			std::copy(begin, end, std::back_inserter(c));
			return c;
		}
		template<typename InputIterator, typename Container>
		Container& push_back(InputIterator begin, size_t n, Container & c)
		{
			std::copy_n(begin, n, std::back_inserter(c));
			return c;
		}
	}
}
