

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <string>

#include "pipeline.hpp"
#include "../expressions/expressions.hpp"

template<typename C>
void do_print(std::string tag, C && c)
{
	std::cout << "\n-------------------\n"  << tag << "\n";
	int i=1000;
	for (auto it = c.begin(), end = c.end() ; i && it != end; ++it, --i)
		std::cout << "print => " << *it << std::endl;
}

#define print(arg) do_print(#arg, arg)

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

int main()
{
	using namespace foam::pipeline;
	using snl::expr::expression;

	std::vector<int>  v {1,2,3,4,5,6,7,8,9,10};

	std::string s = "Sarfaraz Nawaz";
	std::cout << "size of vector = " << size(v) << std::endl;
	std::cout << "size of string = " << size(s) << std::endl;

	//print(from(v));
	//print(from(begin(v), end(v) - 5));


	expression<int> e;

	auto pred = [] (int i) { return i % 3 == 0 ; };

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
	//print( from("sarfaraz") | transform( e + 'A' - 'a' ) );
	//print( from("sarfaraz") | take( std::strlen("sarfaraz") ) | transform( e + 'A' - 'a' ) );
	//print( from(std::string("sarfaraz")) | transform( e + 'A' - 'a' ) );
	//print( from({'s', 'a', 'r', 'f', 'a','r','a','z'}) | transform( e + 'A' - 'a' ) );
}
