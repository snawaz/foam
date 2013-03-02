

#pragma once

#include <type_traits>

namespace foam
{
	namespace alias
	{
		//nested aliases
		template<typename T>
		using type = typename T::type;

		template<typename T>
		using iterator = typename T::iterator;
		
		template<typename T>
		using const_iterator = typename T::const_iterator;

		template<typename T>
		using value_type = typename T::value_type;


		//full-fledged aliases!
		template<typename T, std::size_t Len = sizeof(T) >
		using aligned_storage = type<std::aligned_storage<Len, std::alignment_of<T>::value>>;
	}
}
