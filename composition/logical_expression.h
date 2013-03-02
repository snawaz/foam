

#pragma

#include "expression_details.h"
#include "operator.h"

namespace foam
{
	namespace composition
	{
	       	//###########################################################################################################//
		//####################################### operator && (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::logical_and>> 
		operator && (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::logical_and>(left, right);
		}
	}
}
