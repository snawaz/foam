
#pragma once

#include <iterator>
#include <utility>
#include <type_traits>

#include "container_traits.hpp"
#include "pipe_iterator.hpp"

namespace foam
{
	namespace pipeline
	{
		template<typename Pipe, typename Predicate>
		class filter_pipe
		{
			public:
				typedef filter_pipe<Pipe, Predicate>          self_type;
				typedef typename Pipe::oiterator              iiterator;
				typedef pipe_iterator<self_type, iiterator>       oiterator;
			        typedef decltype(*std::declval<iiterator>())            raw_type;
				typedef typename std::remove_reference<raw_type>::type  value_type;

				filter_pipe(Pipe pipe, Predicate predicate) 
					: _pipe(pipe), _predicate(predicate) 
				{
				}

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
				friend oiterator;
				iiterator ibegin()
				{
					using std::begin;
					auto it = begin(_pipe);
					for(auto eop = iend(); it != eop && !_predicate(*it) ;  ++it);
					return it;
				}
				iiterator iend()
				{
					using std::end;
					return end(_pipe);
				}
				iiterator next (iiterator it) 
				{
					auto eop = iend();
					for(++it; it != eop && !_predicate(*it) ; ++it);
					return it;
			       	}
				value_type value(iiterator it)	
				{
					return *it;
				}
			private:
				Predicate _predicate;
				Pipe _pipe;

		};

		template<typename Pipe, typename UnaryTransformer>
		class transform_pipe
		{
			public:
				typedef transform_pipe<Pipe, UnaryTransformer> self_type;
				typedef typename Pipe::oiterator               iiterator;
				typedef pipe_iterator<self_type, iiterator>    oiterator;
			        typedef decltype(*std::declval<iiterator>())            raw_type;
				typedef typename std::remove_reference<raw_type>::type  value_type;

				transform_pipe(Pipe pipe, UnaryTransformer transformer) 
					: _pipe(pipe), _transformer(transformer) 
				{
				}

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
				friend oiterator;
				iiterator ibegin()
				{
					using std::begin;
					return begin(_pipe);
				}
				iiterator iend()
				{
					using std::end;
					return end(_pipe);
				}
				iiterator next (iiterator it) 
				{
					return ++it;
			       	}
				value_type value(iiterator it)	
				{
					return _transformer(*it);
				}
			private:
				UnaryTransformer _transformer;
				Pipe _pipe;

		};

		template<typename Pipe, typename Predicate>
		class take_pipe
		{
			struct iiterator_wrapper
			{
				typedef typename Pipe::oiterator                                  iiterator;
				typedef decltype(*std::declval<iiterator>())                      raw_type;
				typedef typename std::remove_reference<raw_type>::type            value_type;

				iiterator value;
				Predicate predicate;

				bool operator==(iiterator_wrapper const & other) const { return value == other.value; }
				bool operator!=(iiterator_wrapper const & other) const { return value != other.value; }
				bool operator==(iiterator const & other) const { return value == other; }
				bool operator!=(iiterator const & other) const { return value != other; }

				iiterator_wrapper& operator++() { ++value; return *this; }
				value_type operator * () { return *value; }
			};
			public:
				typedef take_pipe<Pipe, Predicate>                     self_type;
				typedef iiterator_wrapper                              iiterator;
				typedef pipe_iterator<self_type, iiterator>            oiterator;
			        typedef typename iiterator_wrapper::raw_type           raw_type;
			        typedef typename iiterator_wrapper::value_type         value_type;

				take_pipe(Pipe pipe, Predicate predicate) 
					: _pipe(pipe), _predicate(predicate) 
				{
				}

				oiterator begin() 
				{
					using std::begin;
				       	return { this, ibegin() };
				}
				oiterator end()  
				{ 
					using std::end;
					return { this, iend() };   
				}
				template<typename PipelineBuilder>
				auto operator | (PipelineBuilder builder) -> decltype(std::declval<PipelineBuilder>()(std::declval<self_type>()))
				{
					return builder(*this);
				}
			private:
				friend oiterator;
				iiterator ibegin()
				{
					using std::begin;
					iiterator it { begin(_pipe), _predicate };
					if ( it != iend() && it.predicate(*it)) //_predicate(*it)) 
						return it;
					return iend();
				}
				iiterator iend()
				{
					using std::end;
					return {end(_pipe), _predicate};
				}
				iiterator next (iiterator it) 
				{
					++it;
					return it == iend() ? iend() : (it.predicate(*it) ? it : iend());
			       	}
				value_type value(iiterator it)	
				{
					return *it;
				}
			private:
				Predicate _predicate;
				Pipe _pipe;

		};
	}
}

