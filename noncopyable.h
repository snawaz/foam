
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
