
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

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <tuple>
#include <algorithm>

#include <foam/algorithm/algorithm.h>
#include <foam/meta/valuelist.h>
#include <foam/strlib/string_builder.h>

namespace foam
{
	namespace strlib
	{
		struct format_exception : std::invalid_argument
		{
			format_exception(std::string const & message) : std::invalid_argument(message) {}
		};
		
		inline std::string format(char const *fmtstring)
		{
		    return fmtstring;
		}

		template<typename ...Args>
		std::string format(char const *fmtstring, Args const & ...args)
		{
			const int nargs = sizeof...(Args);
			std::string strs[] { string_builder(args)... };
			std::string result;
			auto s = fmtstring;
			auto parse_int = [&](std::string const & delim, std::string const & prev)
			{
				int i=0;
				int neg = 1;
				if ( !prev.empty() && *s == '-' ) { neg = -1; ++s; }
				while ( std::isdigit(*s) ) 
				{
					i = i * 10 + *s - '0';
					++s;
					if ( !*s )
						throw format_exception("format string unexpectedly ends.");
				}
				i = i * neg;
				if (algorithm::none_of(delim, [&](char c) {return c == *s; }))
				{
					string_builder sb("Malformatted format string. ");
					if ( *s == '\n' )
						sb << "Unexpected character '\\n' after {";
					else
						sb << "Unexpected character '" << *s <<"' after {";
					if ( prev.empty() )
						throw format_exception(sb << i  << "." );
					else
						throw format_exception(sb <<  prev << "," << i << "." );
				}
				return i;		
			};
			auto parse = [&]
			{
				int i = parse_int(",}", "");
				int w = *s == ',' ? (++s, parse_int("}", string_builder() << i )) : 0;
				return std::make_tuple(i,w);
			};
			while(s && *s)
			{
				switch(*s)
				{
					case '{':
					{
						++s;
						if ( *s == '{' )
						{
							result += '{';
						}
						else if ( std::isdigit(*s) )
						{
							auto tuple = parse();
							int  i = std::get<0>(tuple);
							int  w = std::get<1>(tuple);
							if ( i >= nargs )
							{
								std::string msg;
								if ( w )
							       		msg = format("Index of {{{0},{1}}} in the format string is out of range.", i,w);
								else
							       		msg = format("Index of {{{0}}} in the format string is out of range.", i);

							       	msg += format(" Maximum allowed index is {{{0}[,alignment]}}.", nargs-1);
								throw std::out_of_range(msg);
							}
							auto const & v = strs[i];
							if ( w < 0 )
							{
								w = -w - static_cast<int>(v.size());
								result += v + std::string(w > 0 ? w : 0, ' ');
							}
							else
							{
								w = w - static_cast<int>(v.size());
								result += std::string(w > 0 ? w : 0, ' ') + v;
							}
	
						}
						else
						{
							throw format_exception("Format string is malformatted.");
						}
					}
					break;
					case '}':
					{
						++s;
						if ( *s == '}' )
							result += '}';
					}
					break;
				default:
					result += *s;
				}
				if ( !*s ) break;
				++s;
			}
			return result;
		}

		template<typename ...Args>
		std::ostream& print(std::ostream & out, char const * fmtstring, Args const & ...args)
		{
			return out << format(fmtstring, args...);
		}
		
		template<typename ...Args>
		std::ostream& print(char const * fmtstring, Args const & ...args)
		{
			return print(std::cout, fmtstring, args...);
		}

	} 

} 
