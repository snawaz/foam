
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
#include <utility>

#include <foam/algorithm/algorithm.h>
#include <foam/meta/valuelist.h>

namespace foam
{
	namespace overload
	{
		namespace detail
		{
			struct fallback { template<typename ... T> fallback(T && ...) {} };
		}
		//preferences to enforce total order of unordered overloads
		using _1st_preference = int&&;
		using _2nd_preference = int const&&;
		using _3rd_preference = int const volatile&&;
		using _4th_preference = int const &;

		//when all preferences fail, choose fallback as fallback.
		using fallback = detail::fallback;

		//pass resolver() as argument to overloaded function.
		using resolver = int;
	}
	namespace strlib
	{
		namespace detail
		{
			template<typename T>
			auto build(std::ostream & out, T && data, overload::_1st_preference) -> decltype(out << data, out)
			{
				out << data;
				return out;
			}
			template<typename T>
			auto build(std::ostream & out, T && data, overload::_2nd_preference) -> decltype(data.print(out), out)
			{
				data.print(out);
				return out;
			}
			template<typename T>
			auto build(std::ostream & out, T && data, overload::_3rd_preference) -> decltype(out << data.to_string(), out)
			{
				out << data.to_string();
				return out;
			}
		}
		class string_builder
		{
			std::ostringstream _oss;
			struct sink { template<typename ... T> sink ( T&& ... ) {} };
		public:
			string_builder() {}

			template<typename T>
			string_builder(T && data) 
			{
				detail::build(_oss, std::forward<T>(data), overload::resolver());
			}
			
			template<typename ...Params>
			string_builder(std::string const & separator, Params && ... args)
			{
				write(separator, std::forward<Params>(args)...);
			}

			template<typename T>
			string_builder & operator << ( T && data)
			{
				detail::build(_oss, std::forward<T>(data), overload::resolver());
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
				sink{ (detail::build(_oss, args, overload::resolver()) <<(N < last ? separator : empty))... };
			}
		};
	} 

} 
