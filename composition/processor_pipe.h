
#pragma once

#include <type_traits>
#include <memory>
#include <functional>

#include "processor_range.h"
#include "processor_single.h"
#include "builder.h"
#include "functor.h"
#include "operator.h"

namespace foam
{
	namespace composition
	{
#if 1		
		//accumulate (1 parameter)
		template<typename Accumulator>
		auto accumulate(Accumulator a) -> accumulate_single_1<Accumulator>
		{
			return {a};
		}

		//accumulate (2 parameters)
		template<typename Accumulator, typename AccumulatorResult>
		auto accumulate(Accumulator a,AccumulatorResult initialValue) -> accumulate_single_2<Accumulator,AccumulatorResult>
		{
			return {a, initialValue};
		}

		//accumulate (3 parameters)
		template<typename Accumulator, typename AccumulatorResult, typename ResultSelector>
		auto accumulate(Accumulator a,AccumulatorResult initialValue,ResultSelector s) -> accumulate_single_3<Accumulator,AccumulatorResult,ResultSelector>
		{
			return {a, initialValue, s};
		}

#endif		
		//filter
		template<typename Predicate>
		auto filter(Predicate predicate) -> pipe_builder<filter_range, Predicate>
		{
			return { predicate };
		}

#if 1
		//skip
		auto skip(int count) -> decltype(filter(details::skip_antipredicate(0)))
		{
			return filter(details::skip_antipredicate(count));	
		}
		
		//skip_while
		template<typename Predicate>
		auto skip_while(Predicate predicate) -> decltype(filter(details::skip_while_antipredicate<Predicate>(predicate)))
		{
			return filter(details::skip_while_antipredicate<Predicate>(predicate));	
		}
		
		//transform
		template<typename UnaryTransformer>
		auto transform(UnaryTransformer transformer) -> pipe_builder<transform_range, UnaryTransformer>
		{
			return { transformer };
		}

		
		//sum (0-parameter)
		auto sum() -> decltype(accumulate(::foam::operators::add()))
		{
			return accumulate(::foam::operators::add());
		}
		
		//sum (1-parameter)
		template<typename Selector>
		auto sum(Selector selector) -> decltype( transform(selector) | sum() )
		{
			return transform(selector) | sum();
		}

		//take
		auto take(int count) -> pipe_builder<take_range,  details::take_predicate>
		{
			return { details::take_predicate(count) };
		}

		//take_while
		template<typename Predicate>
		auto take_while(Predicate predicate) -> pipe_builder<take_range, Predicate>
		{
			return { predicate };
		}

		//sort
		auto sort() -> pipe_builder<order_range, details::identity_functor, ::foam::operators::lt>
		{
			return { details::identity_functor(), ::foam::operators::lt() };
		}

		//sort (Comparator)
		template<typename Comparator>
		auto sort(Comparator comparator) -> pipe_builder<order_range, details::identity_functor, Comparator>
		{
			return { details::identity_functor(), comparator };
		}

		//order_by (Selector)
		template<typename Selector>
		auto order_by(Selector selector) -> pipe_builder<order_range, Selector, ::foam::operators::lt>
		{
			return { selector, ::foam::operators::lt() };
		}
		
		//order_by_descending (Selector)
		template<typename Selector>
		auto order_by_descending(Selector selector) -> pipe_builder<order_range, Selector, ::foam::operators::gt>
		{
			return { selector, ::foam::operators::gt() };
		}

		//reverse
		auto reverse() -> pipe_builder<reverse_range>
		{
			return pipe_builder<reverse_range>();
		}
#endif 		
	}
}
