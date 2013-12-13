#pragma once

#include <type_traits>

namespace std
{
    template<typename ...> struct tuple;
}

namespace foam { namespace meta
{
    namespace bare
    {
		template<typename T>
		using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type; //or use std::decay, as it removes both cv and const!

		template<typename T, typename U>
		struct is_same : std::is_same<type<T>, type<U>> {};
    }
   
    template<typename ...Types>
    struct typelist;

    namespace detail
    {
	//at
	template<int i, typename ... Types>
	struct at;// { static_assert(sizeof...(Types), "at<> failed : index out of range because `Types` is empty!"); };

	template<typename Head, typename ... Types>
	struct at<0, Head, Types...> { using type = Head; };
	
	template<int i, typename Head, typename ... Rest>
	struct at<i, Head, Rest...> : at<i-1, Rest...> {};
	
	//find
	template<template<typename,typename> class Equality, typename Type, typename ... Types>
	struct find : std::integral_constant<int, -1> {};
	
	template<template<typename,typename> class Equality, typename Type, typename Head, typename ... Rest>
	struct find<Equality, Type, Head, Rest...> 
	    : std::integral_constant<int, Equality<Type, Head>::value?0:find<Equality,Type,Rest...>::value<0?-1:1+find<Equality,Type,Rest...>::value>{};
	
	//unique
	template<template<typename,typename> class Equality, typename...Ts>
    	struct unique { using type = typelist<>; };

    	template<template<typename,typename> class Equality, typename Head, typename ... Rest>
   	struct unique<Equality, Head, Rest...> 
    	{ 
		using rest = typename unique<Equality, Rest...>::type;
		using type = typename std::conditional<rest::template exists<Head, Equality>::value, rest, typename rest::template push_front<Head>::type >::type;
  	};
    	
	//is_sublist_of
	template<template<typename, typename> class Equality, typename TypeList, typename ...Types>
    	struct is_sublist_of : std::true_type {};
	
	template<template<typename, typename> class Equality, typename TypeList, typename Head, typename ...Rest>
    	struct is_sublist_of<Equality, TypeList, Head, Rest...> 
		: std::integral_constant<bool, TypeList::template exists<Head,Equality>::value && is_sublist_of<Equality, TypeList, Rest...>::value> {};
   
        //merge	
	template<typename TypeList1, typename ... Types>
    	struct merge;
    
    	template<typename ...Types1, typename ... Types2>
    	struct merge<typelist<Types1...>, Types2...> { using type = typelist<Types2..., Types1...>; };
    }

    //typelist
    template<typename ...Types>
    struct typelist 
    {
	using self = typelist<Types...>;
	using type = self;

	//size
	const static std::size_t size = sizeof...(Types);

	//push_back
	template<typename Type>
	struct push_back : typelist<Types..., Type> {};
	
	//push_front
	template<typename Type>
	struct push_front : typelist<Type, Types...> {};

	//at
	template<std::size_t i>
	struct at : detail::at<i, Types...> {};

	//find
	template<typename Type, template<typename, typename> class Equality=std::is_same>
	struct find : detail::find<Equality, Type, Types...> {};

	//find_cvr
	template<typename Type>
	struct find_cvr : find<Type, bare::is_same> {};

	//exists
	template<typename Type, template<typename, typename> class Equality=std::is_same>
	struct exists : std::integral_constant<bool, find<Type, Equality>::value >=0 > {};

	//exists_cvr
	template<typename Type>
	struct exists_cvr : exists<Type, bare::is_same> {};

	//unique
	template<template<typename, typename> class Equality=std::is_same>
	struct unique : detail::unique<Equality, Types...> {};

	//unique_cvr
	template<typename Unused=void>
	struct unique_cvr : unique<bare::is_same> {};

	//is_unique
    	template<template<typename, typename> class Equality=std::is_same>
	struct is_unique : std::integral_constant<bool, size == unique<Equality>::type::size> {};
    
	//is_unique_cvr
	template<typename Unused=void>
	struct is_unique_cvr : is_unique<bare::is_same> {};

	//is_sublist_of
    	template<typename TypeList, template<typename, typename> class Equality=std::is_same>
    	struct is_sublist_of : detail::is_sublist_of<Equality, TypeList, Types...> {};

	//is_sublist_of_cvr
    	template<typename TypeList>
    	struct is_sublist_of_cvr : is_sublist_of<TypeList, bare::is_same> {};

	//merge
    	template<typename TypeList>
	struct merge : detail::merge<TypeList, Types...> {};

	//union_list
    	template<typename TypeList>
	struct union_list : merge<TypeList>::type::template unique<> {};

		template<template<typename> class Transformer>
		struct transform : typelist<typename Transformer<Types>::type...> {};

    };

    template<typename Tuple>
    struct to_typelist;
    
    template<typename ... Args>
    struct to_typelist<std::tuple<Args...>> : typelist<Args...> {};

#if 0    
    template<int i, typename TypeList>
    struct type_at : TypeList::template at<i> {};
#else
    template<int Index, typename TypeList>
    struct type_at;

    template<typename Head, typename ... Rest>
    struct type_at<0, typelist<Head, Rest...>>
    {
	using type = Head;
    };

    template<int Index, typename Head, typename ... Rest>
    struct type_at<Index, typelist<Head, Rest...>> : type_at<Index-1, typelist<Rest...>> {};
#endif    

}} // meta # triloq
