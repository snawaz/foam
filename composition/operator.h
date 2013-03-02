
#pragma once

#include <stdexcept>

namespace foam
{
	namespace operators
	{
		//###################################################################################//
		//############################## Arithmetic Operators ###############################//

		struct add
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t + u )
			{ 
				return t + u; 
			}
		};
		struct subtract
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t - u )
			{ 
				return t - u; 
			}
		};
		struct multiply
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t * u )
			{ 
				return t * u; 
			}
		};
		struct divide
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t / u )
			{ 
				if ( u == 0 ) 
				{
					throw std::domain_error("Illegal right operand. foam::operators::divide::operator() cannot divide by zero.");
				}
				return t / u; 
			}
		};
		struct modulus
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t % u )
			{ 
				if ( u == 0 ) 
				{
					throw std::domain_error("Illegal right operand. foam::operators::modulus::operator() cannot apply modulus by zero.");
				}
				return t % u; 
			}
		};
		//###################################################################################//
		//############################## Comparison Operators ###############################//

		struct gt 
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t > u )
			{
				return t > u;
			}
		};

		struct gteq
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t >= u )
			{
				return t >= u;
			}
		};

		struct eq
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t == u )
			{
				return t == u;
			}
		};
		
		struct ne
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t != u )
			{
				return t != u;
			}
		};

		struct lt
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t < u )
			{
				return t < u;
			}
		};

		struct lteq
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t <= u )
			{
				return t <= u;
			}
		};
		
		//###########################################################################################//
		//################################## Logical Operators ###################################//
		
		struct logical_and
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t && u )
			{
				return t && u;
			}
		};

		struct logical_or
		{
			template<typename T, typename U>
			auto operator()(T t, U u) -> decltype( t || u )
			{
				return t || u;
			}
		};

		struct logical_not
		{
			template<typename T>
			auto operator()(T t) -> decltype( !t )
			{
				return !t;
			}
		};
	}
}
