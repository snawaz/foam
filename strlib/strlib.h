
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

#include <foam/strlib/string_builder.h>
#include <foam/strlib/format.h>

namespace foam
{
	namespace strlib
	{
		std::string ltrim(std::string s);
		std::string rtrim(std::string s);
		std::string trim(std::string s);

		bool startswith(std::string const & prefix, std::string const & str);
		bool endswith(std::string const & suffix, std::string const & str);

	} 

} 
