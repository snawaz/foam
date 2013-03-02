
#pragma once

#include <type_traits>
#include <tuple>

namespace snl
{
	namespace meta
	{
		template<typename ...T>
		struct typelist : std::integral_constant<size_t, sizeof...(T)> 
		{
			template<int i>
			struct get
			{
				private:
					constexpr static bool in_range = 0 <= i && i < sizeof ...(T);
					static_assert(in_range, "the index i to typelist::get<i> is out of range.");
					constexpr static int j = in_range ? i : 0;
				public:
					typedef typename std::tuple_element<j, std::tuple<T...>>::type type;
			};
		};

	} //namespace meta

} //namespace snl
