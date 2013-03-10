
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
