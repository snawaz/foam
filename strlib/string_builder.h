
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

#include <string>
#include <sstream>

#include <foam/algorithm/algorithm.h>
#include <foam/meta/valuelist.h>

namespace foam
{
	namespace strlib
	{
		class string_builder
		{
			std::ostringstream _oss;
			struct sink { template<typename ... T> sink ( T&& ... ) {} };
		public:
			string_builder() {}

			template<typename T>
			string_builder(T && data) { _oss << data; }

			template<typename T>
			string_builder & operator << ( T && data)
			{
				_oss << data;
				return *this;
			}

			template<typename ...Params>
			string_builder & write(std::string const & separator, Params && ... args)
			{
				typedef typename meta::generate_valuelist<sizeof...(Params)>::type valuelist;
				write_impl(separator, valuelist(), std::forward<Params>(args)...);
				return *this;
			}

			operator std::string() const { return _oss.str(); }

			std::string to_string() const { return _oss.str(); }

		private:
			template<int ...N, typename ...Params>
			void write_impl(std::string const & separator, meta::valuelist<N...>, Params && ... args)
			{
				const std::string empty;
				constexpr int last = sizeof...(Params) - 1 ;
				sink { ( _oss << args << (N < last ? separator : empty) )...};
			}
		};
	} 

} 
