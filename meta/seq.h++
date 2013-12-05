
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

		template<int ... N>
		struct seq
		{
			using type = seq<N...>;

			static const std::size_t size = sizeof ... (N);

			template<int I>
			struct push_back : seq<N..., I> {};

		};
		
		template<int N>
		struct genseq : genseq<N-1>::type::template push_back<N-1> {};

		template<>
		struct genseq<0> : seq<> {};

		template<int N>
		using genseq_t = typename genseq<N>::type;

		template<typename ...Ts>
		using make_seq = genseq_t<sizeof...(Ts)>;

		template<int ... N>
		struct sum : std::integral_constant<int, 0> {};

		template<int I, int ... N>
		struct sum<I, N...> : std::integral_constant<int, I + sum<N...>::value> {};
	}

} 
