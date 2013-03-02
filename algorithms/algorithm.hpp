
#pragma once

#include <algorithm>


namespace foam
{
	namespace algorithm
	{
		template<typename Container, typename UnaryPredicate>
		bool all_of(Container const & c, UnaryPredicate p)
		{
			using std::begin;
			using std::end;
			return std::all_of(begin(c), end(c), p);
		}
		template<typename Container, typename UnaryPredicate>
		bool any_of(Container const & c, UnaryPredicate p)
		{
			using std::begin;
			using std::end;
			return std::any_of(begin(c), end(c), p);
		}
		template<typename Container, typename UnaryPredicate>
		bool none_of(Container const & c, UnaryPredicate p)
		{
			using std::begin;
			using std::end;
			return std::none_of(begin(c), end(c), p);
		}

		template<typename Container, typename T>
		T accumulate(Container const & c, T initialValue)
		{
			using std::begin;
			using std::end;
			return std::accumulate(begin(c), end(c), initialValue);
		}

		template<typename Container, typename T, typename BinaryOperation>
		T accumulate(Container const & c, T initialValue, BinaryOperation op)
		{
			using std::begin;
			using std::end;
			return std::accumulate(begin(c), end(c), initialValue, op);
		}

		template<typename Container, typename OutputIterator>
		void copy(Container const & c, OutputIterator out)
		{
			using std::begin;
			using std::end;
			std::copy(begin(c), end(c), out);
		}
		template<typename Container, typename OutputIterator>
		void copy_n(Container const & c, size_t n, OutputIterator out)
		{
			using std::begin;
			std::copy_n(begin(c), n, out);
		}


	} //namespace algorithm

} //namespace snl
