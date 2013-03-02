

#pragma

#include <type_traits>

#include "../alias.h"

namespace foam
{
	namespace pipeline
	{
		template<typename Iterator, typename State>
		struct iterator_wrapper
		{
			typedef Iterator                                                 iterator;
			typedef decltype(*std::declval<iterator>())                      dereference_type;
			typedef alias::type<std::remove_cv<
				alias::type<std::remove_reference<dereference_type>>>>   value_type;

			iterator value;
			State    state;

			bool operator==(iterator_wrapper const & wrapper) const { return value == wrapper.value; }
			bool operator!=(iterator_wrapper const & wrapper) const { return value != wrapper.value; }
			bool operator==(iterator const & other) const { return value == other; }
			bool operator!=(iterator const & other) const { return value != other; }

			iterator_wrapper& operator++() { ++value; return *this; }
			value_type operator * () { return *value; }
		};
	}
}
