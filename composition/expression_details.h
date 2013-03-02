
#pragma once

#include <type_traits>
#include <tuple>
#include <functional>

namespace foam
{
	namespace composition
	{
		namespace details
		{
			template<typename T>
			struct literal
			{
				T _data;
				literal(T data): _data(data) {}

				template<typename U>
				T operator()(U /*value*/ ) const { return _data; }
			};
		
			/*	
			template<typename TOperand, typename TUnaryOperator>
			struct unary_expression
			{
				TOperand _operand

				unary_expression(TOperand operand) : _operand(operand) {}

				template<typename T>
				auto operator()(T value) -> decltype(TUnaryOperator::apply(_operand(value)))
				{
					return TUnaryOperator::apply(_operand(value));
				}
			};
			*/

			template<typename TLeft, typename TRight, typename TBinaryOperator>
			struct binary_expression
			{
				TLeft _left;
				TRight _right;

				binary_expression(TLeft left, TRight right) : _left(left), _right(right) {}

				template<typename T>
				auto operator()(T value) const -> decltype(TBinaryOperator()(_left(value), _right(value)))
				{
					return TBinaryOperator()(_left(value), _right(value));
				}
			};

			template<typename TLeft, typename TRight>
			struct pipe_expression
			{
				TLeft _left;
				TRight _right;

				pipe_expression(TLeft left, TRight right) : _left(left), _right(right) {}

				template<typename T>
				auto operator()(T value) const -> decltype(_right(_left(value)))
				{
					return _right(_left(value));
				}
			};

			template<typename TArithmetic>
			struct variable
			{
				template<typename T>
				TArithmetic operator()(T value) const
				{
					return static_cast<TArithmetic>(value);
				}		
			};
		}

		template<typename T>
		struct expression
		{
			typedef typename std::conditional<std::is_arithmetic<T>::value, details::variable<T>, T>::type TExpr;
			
			TExpr _expr;
			expression(TExpr expr = TExpr()) : _expr(expr) {}
			
			template<typename U>
			auto operator()(U value) const -> decltype(_expr(value))
			{
				return _expr(value);
			}
		};
	

		//###########################################################################################################//
		//######################################### member expression ###############################################//

		
		template<typename MemberPointer>
		auto member(MemberPointer m) -> expression<decltype(std::mem_fn(m))>
		{
			return std::mem_fn(m);
		}
	
		constexpr struct member_invoker
		{
			template<typename T>
			auto operator() (T arg) const -> decltype(member(arg))
			{
			     return member(arg);
			}
			template<typename ...T>
			auto operator() (T ...args) const -> decltype(std::make_tuple(member(args)...))
			{
				auto tuple = std::make_tuple(member(args)...);
				return tuple;
			}
		}_m{};
	}
}
