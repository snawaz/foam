

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <string>

#include <foam/strlib/strlib.h>
#include <foam/composition/pipeline.h>
#include <foam/composition/expression.h>
#include <foam/composition/utility.h>

template<typename C>
void do_print(std::string pplinestr, C && c)
{
	std::cout << "\n-------------------\n"  << pplinestr << "\n";
//	int i=1000;
//	for (auto it = c.begin(), end = c.end() ; i && it != end; ++it, --i)
//		std::cout << "print => " << *it << std::endl;
	
	for (auto const & item : c)
		std::cout << "print => " << item << std::endl;
}

template<typename S>
void do_print_single(std::string pplinestr, S s)
{
	std::cout <<  pplinestr << " => " << s << std::endl;
}


#define print(arg) do_print(#arg, arg)
#define print_single(s) do_print_single(#s, s)

constexpr struct size_tag
{
	template<typename C>
	size_t operator()(C const & c) const
	{
		auto size = &C::size;
		return (c.*size)();
	}
}size {} ;

bool fun(int i ) { return i % 3 == 0; }

struct customer
{
	int id;
	std::string name;
};
std::ostream & operator << ( std::ostream & out, customer const & c)
{
	return out << "customer {" << c.id << "," << c.name << "}";
}

struct nonpolymorphic1 { void operator()(int) {} };
template<typename T> struct nonpolymorphic2 { void operator()(T) {} };
template<typename T, typename U> struct nonpolymorphic3 { void operator()(T,U) {} };

struct polymorphic1 { template<typename T> void operator()(T) {} };
struct polymorphic2 { template<typename T> void operator()(int, T) {} };
struct polymorphic3 { template<typename T, typename U> void operator()(T, U) {} };

int main()
{
	using namespace foam::composition;

	std::vector<int>  v {1,2,3,4,5,6,7,8,9,10};

	std::string s = "Sarfaraz Nawaz";
	std::cout << "size of vector = " << size(v) << std::endl;
	std::cout << "size of string = " << size(s) << std::endl;

	//print(from(v));
	//print(from(begin(v), end(v) - 5));


	expression<int> e;

	print ( from ( v )  | filter ( e % 2 == 0 ) );
	auto u = v;

#if 1
	auto results = from(v) | filter( e % 2 == 0 ) | transform( e * -10 ) ;//| sort ;
	print(results);
//	v[4] = 100;
//	print(results);
	auto c = v;
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.end(), c.begin(), c.end());
	print(results); 

	print( results | transform( e * -20 ) | take_while( e < 2000 ) );
	
	
	print ( generate(10, [](int i) { return i + 5; } ) | take (3) );
	print ( generate(10, e + 3 ) | take (4) );
	print ( arithmetic_sequence(10, 2 ) | take(4) );
	print ( geometric_sequence(10, 2 ) | take(4) );
	print ( range(0, 5) | transform ( e * e) );
	print ( range(5,0) );
	print ( repeat(0, 5) );
	print ( prime_sequence(0) | take(15) );
	print ( prime_sequence(67778) | take(15) );
	print ( prime_sequence(67778) | take_while( e < 67978 ) );
	print ( prime_range(788,878) );
	auto x = ( prime_sequence(0) | take(15) );
	print ( x ) ; print ( x );
	print ( range(1,20) | skip(10) );
	print ( range(1,20) | skip_while( e < 15 ));
	auto y = range(1,20) | skip_while( e < 15 );
	print ( y ) ; print ( y ) ;
	
	auto create_customer = [](int i) { return customer{ i, ::foam::strlib::format("name{0}", i * 100 )}; };

	print ( range(1, 5) | transform (create_customer) );
	print ( range(1, 5) | transform (create_customer) | transform( [](customer c) { return c.name; } ) );

	print_single ( range( 1, 101 ) | accumulate([](int r, int i) {return r + i;}) );
	print_single ( range( 1, 101 ) | accumulate([](int r, int i) {return r + i;}, 0) );
	print_single ( range( 1, 101 ) | accumulate([](int r, int i) {return r + i;}, 0, create_customer) );

	auto xsum = transform( [](int i) { return i * 1.512; } ) | sum();
	
	print_single ( range(1, 101) | sum() ) ;
	print_single ( range(1, 101) | sum( e * -1 ) ) ;
	print_single ( range(1, 101) | xsum );
	print_single ( range(1, 10) | transform(create_customer) | sum ([](customer const & c) { return c.id; }) ) ;
	print_single ( range(1, 10) | transform(create_customer) | sum ([](customer const & c) { return c.name; }) ) ;

	print_single ( range(1, 101) | transform( e * -1) | sum ( e * -1 ) ) ;
	print_single ( range((int)'A', (int)('Z' + 1) ) | accumulate( [](std::string s, int i) { return s + (char) i; }, "alphabets:" ) ) ;
	print_single ( range((int)'A', (int)('Z' + 1) ) | accumulate( [](std::string s, int i) { return s + (char) i; }, std::string("alphabets:") ) ) ;
	//print_single ( range((char)'A', (char)('Z' + 1) ) | sum( std::string("alphabets:") ) ) ;


	std::vector<int> w { 1010, 91, 82, 74,91, 91, 623, 53, 91, 14, 13,14, 82, 74, 12, 123 };
	//std::vector<int> w { 10, 91, 82, 74, 91, 623, 53, 14, 13, 74, 12, 123 };
	//std::vector<int> w { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	print ( from(w) );
	print ( from(w) | sort() );
	print ( from(w) | sort( [](int a, int b) { return a > b; } ) );
	print ( from(w) | order_by( e ) );
	print ( from(w) | order_by_descending( e ) );
	print ( range(1,10) | order_by_descending( e ) );
	print ( from(w) | reverse() );
	print ( from(w) | take(5) | reverse() );
	print ( from(w) | reverse() | take(5) );
	print ( from(w) | reverse() | take_while( e > 70 ) );
	//print ( range(10,0) | transform ( e * 10 ) | order_by() );
#endif 

	//print ( range((char)'A', (char)('Z' + 1) ) ); //| sum( std::string("alphabets:") ) ) ;
	//print_single ( range('A', 'Z' + 1 ) | sum<std::string>( "alphabets:" ) ) ;

#if 0
	print_single (( foam::is_one_arg_polymorphic_functor<nonpolymorphic1>::value )) ;
	print_single (( foam::is_one_arg_polymorphic_functor<nonpolymorphic2<int>>::value )) ;
	print_single (( foam::is_one_arg_polymorphic_functor<nonpolymorphic3<int,short>>::value )) ;
	print_single (( foam::is_one_arg_polymorphic_functor<polymorphic1>::value )) ;
	print_single (( foam::is_one_arg_polymorphic_functor<polymorphic2>::value )) ;
	print_single (( foam::is_one_arg_polymorphic_functor<polymorphic3>::value )) ;
#endif 

	//print( from("sarfaraz") | transform( e + 'A' - 'a' ) );
	//print( from("sarfaraz") | take( std::strlen("sarfaraz") ) | transform( e + 'A' - 'a' ) );
	//print( from(std::string("sarfaraz")) | transform( e + 'A' - 'a' ) );
	//print( from({'s', 'a', 'r', 'f', 'a','r','a','z'}) | transform( e + 'A' - 'a' ) );
}
