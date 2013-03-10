
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
		//####################################### operator + (left, right) ##########################################//
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::add>> 
		operator+(TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::add>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::add>> 
		operator+(expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::add>(left, right);
		}
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::add>> 
		operator+(expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::add>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator - (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::subtract>> 
		operator - (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::subtract>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::subtract>> 
		operator - (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::subtract>(left, right);
		}
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::subtract>> 
		operator - (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::subtract>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator * (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::multiply>> 
		operator * (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::multiply>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::multiply>> 
		operator * (expression<TLeft> left, TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::multiply>(left, right);
		}
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::multiply>> 
		operator * (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::multiply>(left, right);
		}

                //###########################################################################################################//
		//####################################### operator / (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::divide>> 
		operator / (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::divide>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::divide>> 
		operator / (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::divide>(left, right);
		}
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::divide>> 
		operator / (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::divide>(left, right);
		}
                
		//###########################################################################################################//
		//####################################### operator % (left, right) ##########################################//

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::modulus>> 
		operator % (TLeft left,  expression<TRight> right)
		{
			return details::binary_expression<details::literal<TLeft>, expression<TRight>, operators::modulus>(left, right);
		}

		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::modulus>> 
		operator % (expression<TLeft> left,  TRight right)
		{
			return details::binary_expression<expression<TLeft>, details::literal<TRight>, operators::modulus>(left, right);
		}
	
		template<typename TLeft, typename TRight>
		expression<details::binary_expression<expression<TLeft>, expression<TRight>, operators::modulus>> 
		operator % (expression<TLeft> left,  expression<TRight> right)
		{
			return details::binary_expression<expression<TLeft>, expression<TRight>, operators::modulus>(left, right);
		}
	}
}
