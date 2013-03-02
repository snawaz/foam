
#pragma once

#include <iterator>
#include <utility>
#include <type_traits>

#include "utility.h"
#include "container_traits.h"
#include "range_iterator.h"
#include "../optional.hpp"

namespace foam
{
	namespace pipeline
	{
		template<typename Range>
		class from_range 
		{
				typedef from_range<Range>                                     self_type;
				typedef typename container_traits<Range>::iterator            iiterator;
			public:	
				typedef range_iterator<self_type, iiterator>                  iterator;
				typedef typename container_traits<Range>::value_type          value_type;

				from_range(Range * pipe)
				       	: _pipe(pipe) {}

				iterator begin() 
				{
				       	return { this, ibegin() }; 
				}
				iterator end()
				{
				       	return { this, iend() };   
				}

				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> decltype(std::declval<PipelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}

			private:
				friend iterator;

				iiterator ibegin() 
				{
					using std::begin;
					return begin(*_pipe);
				}
				iiterator iend() 
				{
					using std::end;
					return end(*_pipe);
				}

				iiterator next(iiterator it)
				{
					return ++it;
				}
				value_type value(iiterator it)	
				{
					return *it;
				}
			private:
				Range *_pipe;
		};
		
		template<typename UnaryGenerator>
		class generate_range
		{
				typedef generate_range<UnaryGenerator>                        self_type;
				typedef typename functor_traits<UnaryGenerator>::result_type  result_type;
				typedef result_type                                           arg_type;
				typedef optional<result_type>                                 iiterator;
			public:	
				typedef range_iterator<self_type, iiterator>                  iterator;
				typedef result_type                                           value_type;

				generate_range(arg_type start, UnaryGenerator generator)
				       	: _start(start), _generator(generator) {}

				iterator begin() 
				{
					using std::begin;
				       	return { this, iiterator(_start) }; 
				}
				iterator end()
				{
					using std::end;
				       	return { this, iiterator() };   
				}

				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> decltype(std::declval<PipelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				
				friend iterator;

				iiterator next(iiterator it)
				{
					it.value() = _generator(it.value());
					return it;
				}
				value_type value(iiterator it)	
				{
					return it.value();
				}
			private:
				UnaryGenerator _generator;
				arg_type       _start;
		};
	}
}
