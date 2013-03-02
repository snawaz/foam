
#pragma once

#include <type_traits>
#include <memory>
#include <functional>

#include "operator_pipe.hpp"
#include "builder.hpp"
#include "functors.hpp"

namespace foam
{
	namespace pipeline
	{
		//filter
		template<typename Predicate>
		auto filter(Predicate predicate) -> pipe_builder<filter_pipe, Predicate>
		{
			return { predicate };
		}

		//transform
		template<typename UnaryTransformer>
		auto transform(UnaryTransformer transformer) -> pipe_builder<transform_pipe, UnaryTransformer>
		{
			return { transformer };
		}

		//take
		auto take(int count) -> pipe_builder<take_pipe,  details::take_predicate>
		{
			return { details::take_predicate(count) };
		}

		//take_while
		template<typename Predicate>
		auto take_while(Predicate predicate) -> pipe_builder<take_pipe, Predicate>
		{
			return { predicate };
		}

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
	}
}
