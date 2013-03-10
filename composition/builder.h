
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
		template<typename PipelineBuilder, template <typename,typename...> class RangeClassTemplate, typename ...Types>
		class composed_pipe_builder
		{
			public:
				composed_pipe_builder(PipelineBuilder builder, std::tuple<Types...> args ) 
					: _builder(builder), _arguments(args) {}

				template<typename Range>
				auto operator()(Range range) -> decltype(std::declval<PipelineBuilder>()(std::declval<RangeClassTemplate<Range, Types...>>()))
				{
					const size_t N = sizeof ...(Types);
					typename ::foam::meta::generate_valuelist<N>::type indices;
					return _builder(build(range, indices));
				}
			private:
				template<typename Range, int ...N>
				auto build(Range range, ::foam::meta::valuelist<N...> const &) -> RangeClassTemplate<Range, Types...>
				{
					return {range, std::get<N>(_arguments)...};
				}
				PipelineBuilder _builder;
				std::tuple<Types...> _arguments;
		};

		template< template <typename,typename...> class RangeClassTemplate, typename ...Types>
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
				auto operator | (PipelineBuilder builder) -> composed_pipe_builder<PipelineBuilder, RangeClassTemplate, Types...>
				{
					return {builder, _arguments};
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
#if 0		
		template<typename PipelineBuilder, template <typename,typename> class RangeClassTemplate, typename UnaryFunctor>
		struct composed_pipe_builder
		{
			PipelineBuilder _builder;
			UnaryFunctor _functor;

			template<typename Range>
			auto operator()(Range range) -> decltype(std::declval<PipelineBuilder>()(std::declval<RangeClassTemplate<Range, UnaryFunctor>>()))
			{
				RangeClassTemplate<Range, UnaryFunctor> new_range {range, _functor};
				return _builder(new_range);
			}
		};

		template< template <typename,typename> class RangeClassTemplate, typename UnaryFunctor>
		struct pipe_builder
		{
			UnaryFunctor _functor;
			
			template<typename Range>
			auto operator()(Range range) -> RangeClassTemplate<Range, UnaryFunctor>
			{
				return {range, _functor};
			}

			template<typename PipelineBuilder>
			auto operator | (PipelineBuilder builder) -> composed_pipe_builder<PipelineBuilder, RangeClassTemplate, UnaryFunctor>
			{
				return {builder, _functor};
			}
		};
#endif
	}
}
