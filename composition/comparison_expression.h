
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
