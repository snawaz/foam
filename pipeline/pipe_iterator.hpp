

#pragma once

#include <utility>
#include <stdexcept>

namespace foam
{
	namespace pipeline
	{
		template<typename Pipe, typename Iterator>
		class pipe_iterator 
		{
			Pipe     * _pipe;
			Iterator   _iterator;
		public:
			
			typedef pipe_iterator<Pipe, Iterator>     self_type;
			typedef Pipe                              pipe_type;
			typedef Iterator                          iterator_type;
			typedef typename Pipe::value_type         value_type;

			pipe_iterator(Pipe * pipe, Iterator iterator) 
				: _pipe(pipe), _iterator(iterator) {}

			pipe_iterator& operator++()     //pre-increment
			{
				_iterator = _pipe->next(_iterator);
				return *this;
			}
			pipe_iterator operator++(int)  //post-increment
			{
				auto old = (*this);
				++(*this);
				return old;
			}
			value_type operator*() 
			{
				return _pipe->value(_iterator);
			}
			bool operator != (pipe_iterator const & other ) const
			{
				if ( _pipe != other._pipe )
					throw std::logic_error("the pipe_iterator pair doesn't belong to same underlying pipe instance.");
				return _iterator != other._iterator;
			}
			bool operator == (pipe_iterator const & other) const 
			{
				return !(*this != other);
			}
		};

	}
}
