
#pragma once

namespace foam
{
	//functor traits
	template <typename T>
	struct functor_traits : functor_traits<decltype(&T::operator())>
	{};
	
	template <typename C, typename R, typename... A>
	struct functor_traits<R(C::*)(A...) const> : functor_traits<R(C::*)(A...)>
	{};
	
	template <typename C, typename R, typename... A>
	struct functor_traits<R(C::*)(A...)>
	{
		enum { arity = sizeof...(A) };
		
		typedef R result_type;

		template <size_t i>
		struct arg
		{
			typedef typename std::tuple_element<i, std::tuple<A...>>::type type;
		};
	};

	//template<>
	//implement polymorphic functor traits
}
