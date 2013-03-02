
#pragma once

#include <stdexcept>

namespace snl
{
	namespace operators
	{
		//###################################################################################//
		//############################## Arithmetic Operators ###############################//

		struct add
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t + u )
			{ 
				return t + u; 
			}
		};
		struct subtract
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t - u )
			{ 
				return t - u; 
			}
		};
		struct multiply
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t * u )
			{ 
				return t * u; 
			}
		};
		struct divide
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t / u )
			{ 
				if ( u == 0 ) 
				{
					throw std::domain_error("Illegal right operand. snl::operators::divide::apply() cannot divide by zero.");
				}
				return t / u; 
			}
		};
		struct modulus
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t % u )
			{ 
				if ( u == 0 ) 
				{
					throw std::domain_error("Illegal right operand. snl::operators::modulus::apply() cannot apply modulus by zero.");
				}
				return t % u; 
			}
		};
		//###################################################################################//
		//############################## Comparison Operators ###############################//

		struct gt 
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t > u )
			{
				return t > u;
			}
		};

		struct gteq
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t >= u )
			{
				return t >= u;
			}
		};

		struct eq
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t == u )
			{
				return t == u;
			}
		};
		
		struct ne
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t != u )
			{
				return t != u;
			}
		};

		struct lt
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t < u )
			{
				return t < u;
			}
		};

		struct lteq
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t <= u )
			{
				return t <= u;
			}
		};
		
		//###########################################################################################//
		//################################## Logical Operators ###################################//
		
		struct logical_and
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t && u )
			{
				return t && u;
			}
		};

		struct logical_or
		{
			template<typename T, typename U>
			static auto apply(T t, U u) -> decltype( t || u )
			{
				return t || u;
			}
		};

		struct logical_not
		{
			template<typename T>
			static auto apply(T t) -> decltype( !t )
			{
				return !t;
			}
		};
	}
}
