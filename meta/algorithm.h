
#pragma once

#include <type_traits>
#include "valuelist.h"
#include "typelist.h"

namespace foam
{
	namespace meta
	{
		//usage: reverse<valuelist<0,1,2,3,4>>::type gives valuelist<4,3,2,1,0> 
		template<typename valuelist_or_typelist>
		struct reverse
		{
			private:
				template<typename>
				struct reverse_impl;

				template<int ... Ns>
				struct reverse_impl<valuelist<Ns...>>
				{
					private:
						template<typename, typename>
						struct rev;

						template<int I, int ...Is, int ...Rs>
						struct rev<valuelist<I, Is...>, valuelist<Rs...>> : rev<valuelist<Is...>, valuelist<I,Rs...>> {};

						template<int ...Rs>
						struct rev<valuelist<>, valuelist<Rs...>> 
						{
							typedef valuelist<Rs...> type;
						};
					public:
						typedef typename rev<valuelist<Ns...>, valuelist<>>::type type;

				};
			public:
				typedef typename reverse_impl<valuelist_or_typelist>::type type; 
		};

	} 

} 
