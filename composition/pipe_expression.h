

#pragma once

#include <type_traits>
#include "expression_details.h"
#include "operator.h"

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
