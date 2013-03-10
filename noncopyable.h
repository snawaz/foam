
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

namespace foam
{
	class noncopyable
	{
		protected:
			noncopyable() {}
			noncopyable(noncopyable &&) = default;
			noncopyable& operator=(noncopyable &&) = default;
		private:
			noncopyable(noncopyable const& ) = delete;
			noncopyable& operator=(noncopyable const& ) = delete;

	};
}
