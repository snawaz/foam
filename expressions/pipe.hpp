

#pragma once

#include <type_traits>
#include "expressions_details.hpp"
#include "operators.hpp"

namespace snl
{
	namespace expr
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
