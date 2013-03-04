

#pragma once

#include <utility>
#include <type_traits>

#include "utility.h"

namespace foam
{
	namespace composition
	{
		template<typename Accumulator>
		struct accumulate_single_1
		{
			Accumulator       _accumulator;
			
			template<typename Range>
			auto operator()(Range range) -> typename Range::value_type
			{
				auto value = typename Range::value_type();
				for(auto it =  range.begin(), end = range.end(); it != end ; ++it)
				{
					value = _accumulator(value, *it);
				}
				return value;
			}
		};
		
		template<typename Accumulator, typename AccumulatorSeed>
		struct accumulate_single_2
		{
			typedef typename ::foam::argument_or_default<Accumulator, AccumulatorSeed>::type result_type;

			Accumulator       _accumulator;
			AccumulatorSeed   _seed;
			
			template<typename Range>
			auto operator()(Range range) -> result_type //typename ::foam::functor_traits<Accumulator>::template arg<0>::type
			{
				//typedef typename ::foam::functor_traits<Accumulator>::template arg<0>::type result_type;
				result_type value = _seed; //make copy!
				for(auto it =  range.begin(), end = range.end(); it != end ; ++it)
				{
					value = _accumulator(value, *it);
				}
				return value;
			}
		};

		template<typename Accumulator, typename AccumulatorResult, typename ResultSelector>
		struct accumulate_single_3 
		{
			Accumulator       _accumulator;
			AccumulatorResult _initialValue;
			ResultSelector    _resultSelector;
		
			template<typename Range>
			auto operator()(Range range) -> typename call_result<ResultSelector,AccumulatorResult>::type
			{
				auto value = _initialValue;
				for(auto it =  range.begin(), end = range.end(); it != end ; ++it)
				{
					value = _accumulator(value, *it);
				}
				return _resultSelector(value);
			}
		};
	}
}
