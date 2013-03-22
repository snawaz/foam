
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

#include <tuple>

#include  <foam/meta/valuelist.h>

namespace foam
{
	namespace composition
	{
		template<typename PipelineBuilderCurrent, typename PipelineBuilderNext>
		class builder_composer
		{
			public:
				builder_composer(PipelineBuilderCurrent current, PipelineBuilderNext next) 
					: _current(current), _next(next) {}

				template<typename Range>
				auto operator()(Range range) -> decltype(std::declval<PipelineBuilderNext>()(std::declval<PipelineBuilderCurrent>()(range)))
				{
					return _next(_current(range));
				}
				template<typename PipelineBuilderOther>
				auto operator | (PipelineBuilderOther builder) -> 
				builder_composer<builder_composer<PipelineBuilderCurrent,PipelineBuilderNext>, PipelineBuilderOther>
				{
					return { *this, builder};
				}
			private:
				PipelineBuilderCurrent _current;
				PipelineBuilderNext _next;
		};

		template< template<typename, typename...> class RangeClassTemplate, typename ...Types>
		class pipe_builder
		{
			public:
				
				pipe_builder(Types ...args) : _arguments(args...) {} //: _arguments(std::make_tuple(args)...) {}

				template<typename Range>
				auto operator()(Range range) -> RangeClassTemplate<Range, Types...>
				{
					const size_t N = sizeof ...(Types);
					typename ::foam::meta::generate_valuelist<N>::type indices;
					return build(range, indices);
				}

				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> builder_composer<pipe_builder<RangeClassTemplate, Types...>, PipelineBuilder>
				{
					return {*this, builder};
				}
			private:
				template<typename Range, int ...N>
				auto build(Range range, ::foam::meta::valuelist<N...> const &) -> RangeClassTemplate<Range, Types...>
				{
					return {range, std::get<N>(_arguments)...};
				}
			private:
				std::tuple<Types...> _arguments;
		};
	}
}
