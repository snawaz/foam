
/*
 *
 * (C) Copyright Sarfaraz Nawaz 2013-14, sir_nawaz959@yahoo.com
 *
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt Or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#pragma once

#include <algorithm>
#include <iterator>

namespace foam
{
	namespace extension
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
