
#pragma once

#include <type_traits>
#include "expressions_details.hpp"
#include "operators.hpp"

namespace snl
{
	namespace expr
	{

                //###########################################################################################################//
		//####################################### operator > (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::gt>> 
		operator > (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::gt>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::gt>> 
		operator > (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::gt>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::gt>> 
		operator > (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::gt>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator >= (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::gteq>> 
		operator >= (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::gteq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::gteq>> 
		operator >= (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::gteq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::gteq>> 
		operator >= (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::gteq>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator == (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::eq>> 
		operator == (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::eq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::eq>> 
		operator == (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::eq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::eq>> 
		operator == (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::eq>(left, right);
		}
                
		//###########################################################################################################//
		//####################################### operator != (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::ne>> 
		operator != (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::ne>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::ne>> 
		operator != (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::ne>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::ne>> 
		operator != (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::ne>(left, right);
		}


                //###########################################################################################################//
		//####################################### operator < (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::lt>> 
		operator < (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::lt>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::lt>> 
		operator < (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::lt>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::lt>> 
		operator < (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::lt>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator <= (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::lteq>> 
		operator <= (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::lteq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::lteq>> 
		operator <= (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::lteq>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::lteq>> 
		operator <= (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::lteq>(left, right);
		}


	}
}
