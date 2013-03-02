

#pragma once

#include <utility>
#include <stdexcept>

namespace foam
{
	namespace pipeline
	{
		template<typename Range, typename Iterator>
		class range_iterator 
		{
			Range     * _range;
			Iterator   _iterator;
		public:
			
			typedef range_iterator<Range, Iterator>     self_type;
			typedef Range                              pipe_type;
			typedef Iterator                          iterator_type;
			typedef typename Range::value_type         value_type;

			range_iterator(Range * pipe, Iterator iterator) 
				: _range(pipe), _iterator(iterator) {}

			range_iterator& operator++()     //pre-increment
			{
				_iterator = _range->next(_iterator);
				return *this;
			}
			range_iterator operator++(int)  //post-increment
			{
				auto old = (*this);
				++(*this);
				return old;
			}
			value_type operator*() 
			{
				return _range->value(_iterator);
			}
			bool operator != (range_iterator const & other ) const
			{
				if ( _range != other._range )
					throw std::logic_error("the range_iterator pair doesn't belong to same underlying pipe instance.");
				return _iterator != other._iterator;
			}
			bool operator == (range_iterator const & other) const 
			{
				return !(*this != other);
			}
		};

	}
}
