
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

#include <type_traits>

namespace foam
{
	namespace meta
	{
		template<int ...N>
		struct valuelist : std::integral_constant<size_t, sizeof...(N)> {} ;

		//usage: generate_valuelist<5>::type gives valuelist<0,1,2,3,4>
		template<int N>
		struct generate_valuelist
		{
		  	private:	
				template<int I, int ...Is>
				struct gen : gen<I-1, I-1, Is...> {};

				template<int ...Is>
				struct gen<0, Is...>
				{
					typedef valuelist<Is...> type;
				};
			public:
				typedef typename gen<N>::type type;
		};

	}

} 
