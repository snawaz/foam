
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

#include <utility>
#include <type_traits>

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

	//std::result_of<> cannot work with polymorphic functor as it attempts to deduce the argument types
	//which is not possible in case of polymorphic functor!
	//call_result attempts to solve this problem, as it doens't depend on deduction!
	template<typename MaybePolymorphicFunctor, typename ...Args>
	struct call_result
	{
		typedef decltype(std::declval<MaybePolymorphicFunctor>()
				(std::declval<Args>()...)) type;
	};

	template<typename T>
	class is_polymorphic_functor 
	{
		  template <typename F, typename = decltype(&F::operator())>
		  static constexpr bool get(int) { return false; }
		  template <typename>
		  static constexpr bool get(...) { return true; }
		public:
		  static constexpr bool value = get<T>(0);
	};
	

	namespace details
	{
			template<bool, typename F, typename T>
			struct get { typedef typename ::foam::functor_traits<F>::template arg<0>::type type; };

			template<typename F, typename T>
			struct get<true,F,T> { typedef T type; };
	}

	template<typename MaybePolymorphicFunctor, typename Default>
	struct argument_or_default 
	{
		private:
			static const bool polymorphic = is_polymorphic_functor<MaybePolymorphicFunctor>::value;
		public:
			typedef typename details::get<polymorphic, MaybePolymorphicFunctor, Default>::type type;
	};
}
