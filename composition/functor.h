
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

#include <cmath>

namespace foam
{
	namespace composition
	{
		namespace details
		{
			//this functor class is used to enable functor_traits to deduce
			//argument_type and result_type of a polymorphic functor!
			template<typename MayBePolymorphicUnaryFunctor, typename R, typename A>
			struct functor
			{
				MayBePolymorphicUnaryFunctor _unaryFunctor;
				
				functor(MayBePolymorphicUnaryFunctor functor) : _unaryFunctor(functor) {}

				R operator()(A arg) const { return _unaryFunctor(arg); }
			};

			struct take_predicate 
			{ 
				int _count;
				take_predicate(int n) : _count(n) {}

				template<typename T> 
				bool operator()(T const &) 
				{
					return --_count >= 0;
			       	} 
			};
			
			struct skip_antipredicate 
			{ 
				int _count;
				skip_antipredicate(int n) : _count(n) {}

				template<typename T> 
				bool operator()(T const &) 
				{
					return _count < 0 ? true : (--_count < 0 );
			       	} 
			};
			
			template<typename Predicate>
			struct skip_while_antipredicate
			{ 
				Predicate _predicate;
				bool _predicateResult;
				skip_while_antipredicate(Predicate predicate) : _predicate(predicate), _predicateResult(true) {}

				template<typename T> 
				bool operator()(T const &data) 
				{
					if ( !_predicateResult ) return true;
					_predicateResult = _predicate(data);
					return !_predicateResult;
			       	} 
			};

			struct next_prime
			{
				template<typename T>
				T operator()(T prev) const
				{
					for(T i = prev % 2 ? prev+2 : prev + 1;  ; i += 2)
					{
						if ( is_prime(i) ) return i;
					}
				}
				
				template<typename T>
				bool is_prime(T n) const
				{
					if ( n < 2) return false;
					else if ( n == 2 ) return true;
					else if ( !(n % 2) ) return false;

					T m = std::sqrt(n);
					for(T i = 3 ; i <= m ; i+=2)
					{
						if ( !(n % i) ) return false;
					}
					return true;
				}
				
				template<typename T>
				T first(T x) const
				{
					if ( x < 2 ) return 2;
					else if ( is_prime(x)) return x;
					return (*this)(x);
				}
			};

			struct identity_functor
			{
				template<typename T>
				T operator()(T data) const { return data; }
			};
		}
	}
}
