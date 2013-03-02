
#pragma once

#include <iterator>
#include <utility>
#include <type_traits>

#include "utility.hpp"
#include "container_traits.hpp"
#include "pipe_iterator.hpp"
#include "../optional.hpp"

namespace foam
{
	namespace pipeline
	{
		template<typename Pipe>
		class from_pipe 
		{
			public:	
				typedef from_pipe<Pipe>                                      self_type;
				typedef typename container_traits<Pipe>::iiterator           iiterator;
				typedef pipe_iterator<self_type, iiterator>                  oiterator;
			        typedef decltype(*std::declval<iiterator>())                 raw_type;
				typedef typename std::remove_reference<raw_type>::type       value_type;

				from_pipe(Pipe * pipe)
				       	: _pipe(pipe) {}

				oiterator begin() 
				{
				       	return { this, ibegin() }; 
				}
				oiterator end()
				{
				       	return { this, iend() };   
				}

				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> decltype(std::declval<PipelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}

			private:
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
				friend oiterator;

				iiterator next(iiterator it)
				{
					return ++it;
				}
				value_type value(iiterator it)	
				{
					return *it;
				}
			private:
				Pipe *_pipe;
		};
		
		template<typename UnaryGenerator>
		class generate_pipe
		{
			typedef functor_traits<UnaryGenerator> generator_traits;
			public:	
				typedef generate_pipe<UnaryGenerator>                     self_type;
				typedef typename generator_traits::result_type            result_type;
				typedef result_type                                       arg_type;
				typedef optional<result_type>                             iiterator;
				typedef pipe_iterator<self_type, iiterator>               oiterator;
				typedef result_type                                       value_type;

				generate_pipe(arg_type start, UnaryGenerator generator)
				       	: _start(start), _generator(generator) {}

				oiterator begin() 
				{
					using std::begin;
				       	return { this, iiterator(_start) }; 
				}
				oiterator end()
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
				
				friend oiterator;

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

