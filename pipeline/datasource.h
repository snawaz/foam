
#pragma once

#include <type_traits>
#include <memory>
#include <cmath>

#include "pipe_operators.hpp"
#include "source_pipe.hpp"
#include "builder.hpp"
#include "functors.hpp"
#include "../expressions/expressions.hpp"

namespace foam
{
	namespace pipeline
	{
		//from 
		template<typename Iterable>
		auto from(Iterable & c) -> from_pipe<Iterable>
		{
			return from_pipe<Iterable>(&c);
		}

		//template<typename T>
		//auto from(std::initializer_list<T> const & c) -> from_pipe<std::initializer_list<T> const>
		//{
		//	return from_pipe<std::initializer_list<T> const>(&c);
		//}

		//template<typename Iterable>
		//auto from(Iterable const & c) -> from_pipe<Iterable const>
		//{
		//	return from_pipe<Iterable const>(&c);
		//}

		//template<typename Iterable>
		//auto from(Iterable && c) -> from_pipe<Iterable>
		//{
		//	return from_pipe<Iterable>(&c);
		//}
		
		//generate (infinity)
		template<typename T, typename UnaryGenerator>
		auto generate(T start, UnaryGenerator generator) -> generate_pipe<details::functor<UnaryGenerator, T, T>>
		{
			return {start, details::functor<UnaryGenerator, T, T>(generator) };
		}
		
		//arithmetic_sequence (infinity)
		template<typename T>
		auto arithmetic_sequence(T start, T difference) -> decltype(generate(start, snl::expr::expression<T>() + difference ))
		{
			return generate(start, snl::expr::expression<T>() + difference );
		}

		//geometric_sequence (infinity)
		template<typename T>
		auto geometric_sequence(T start, T ratio) -> decltype(generate(start, snl::expr::expression<T>() * ratio ))
		{
			return generate(start, snl::expr::expression<T>() * ratio );
		}
	
		//prime_sequence
		template<typename T>
		auto prime_sequence(T start) -> decltype(generate(start, details::next_prime() ))
		{
			details::next_prime p{};
			return generate(p.first(start), p);
		}

		//prime_range 
		template<typename T>
		auto prime_range(T start, T end) -> decltype(prime_sequence(start) | take_while( snl::expr::expression<T>() < end ))
		{
			return prime_sequence(start) | take_while( snl::expr::expression<T>() < end );
		}

		//range [start, end)
		template<typename T>
		auto range(T start, T end) -> decltype(arithmetic_sequence(0, 0) | take(0)) 
		{
			return arithmetic_sequence(start, end > start ? 1 : -1 ) | take( std::abs(end - start) );
		}
		
		//repeat
		template<typename T>
		auto repeat(T value, int count) -> decltype(arithmetic_sequence(0, 0) | take(0)) 
		{
			return arithmetic_sequence(value, 0) | take(count);
		}
	}
}
