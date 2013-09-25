
/*
 *
 * (C) Copyright Sarfaraz Nawaz 2013-14, sir_nawaz959@yahoo.com
 *
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt Or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <foam/strlib/strlib.h>

namespace foam
{
	namespace strlib
	{
		std::string ltrim(std::string s)
		{
			s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), static_cast<int(*)(int)>(std::isspace)));
			return s;
		}
		std::string rtrim(std::string s)
		{
			s.erase(std::find_if_not(s.rbegin(), s.rend(), static_cast<int(*)(int)>(std::isspace)).base(), s.end());
			return s;
		}
		std::string trim(std::string s)
		{
			return ltrim(rtrim(std::move(s)));
		}
		bool startswith(std::string const & prefix, std::string const & str)
		{
			if(prefix.size() > str.size()) 
				return false;
			return std::equal(prefix.begin(), prefix.end(), str.begin());
		}
		bool endswith(std::string const & suffix, std::string const & str)
		{
			if(suffix.size() > str.size()) 
				return false;
			return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
		}
	} 

} 
