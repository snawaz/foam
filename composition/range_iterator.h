
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

#include <utility>
#include <stdexcept>
#include <type_traits>
#include <foam/alias.h>

namespace foam
{
	namespace composition
	{
		template<typename Range, typename Iterator>
		class range_iterator 
		{
		public:
			
			typedef range_iterator<Range, Iterator>     self_type;
			typedef Range                               range_type;
			typedef Iterator                            iterator_type;
			//typedef typename Range::value_type          value_type;
			//
			typedef typename std::remove_reference<
				typename Range::value_type>::type  value_type;
			//typedef alias::type<std::remove_reference<std::alias::value_type<Range>>>          value_type;

			range_iterator(Range * range, Iterator iterator) 
				: _range(range), _iterator(iterator), _valid_value(false) {}

			range_iterator& operator++()     //pre-increment
			{
				//_iterator = _range->next(_iterator);

				Iterator it(_range->next(_iterator));               //copy

				new (&_iterator) Iterator(std::move(it));           //reconstruct using copy-constructor, 
				                                                    //as copy-assignment is deleted for Iterator,
				                                                    //as copy-assignment is deleted for lambdas 
										    //which could be a member of Iterator.
				_valid_value = false;										
				return *this;
			}
			range_iterator operator++(int)  //post-increment
			{
				auto old = (*this);
				++(*this);
				_valid_value = false;										
				return old;
			}
			value_type operator*() 
			{
				if ( !_valid_value )
				{
					_value = _range->value(_iterator);
					_valid_value = true;
				}
				return _value;
			}
			bool operator != (range_iterator const & other ) const
			{
				if ( _range != other._range )
					throw std::logic_error("the range_iterator pair doesn't belong to same underlying range instance.");
				return _iterator != other._iterator;
			}
			bool operator == (range_iterator const & other) const 
			{
				return !(*this != other);
			}
		private:
			Range      * _range;
			Iterator    _iterator;
			bool        _valid_value;
			value_type  _value;
		};

	}
}
