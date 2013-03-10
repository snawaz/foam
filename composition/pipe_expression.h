
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

#include <type_traits>
#include <foam/composition/expression_details.h>
#include <foam/composition/operator.h>

namespace foam
{
	namespace composition
	{
		//###########################################################################################################//
		//####################################### operator | (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::pipe_expression<expression<TLeft>, expression<TRight>>>
		operator | (expression<TLeft> left, expression<TRight> right)
		{
			return details::pipe_expression<expression<TLeft>, expression<TRight>>(left, right);
		}
	}
}
