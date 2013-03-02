
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

#include "istream_reader.h"
#include "../algorithms/algorithm.h"

struct line : std::string
{
	friend std::istream& operator >> (std::istream & ins, line & ln)
	{
		return std::getline(ins, ln);
	}
};

int main()
{
	try
	{
		typedef line item_type;

		//istream_reader<std::string> reader("istream_reader.cpp");
		//snl::streams::istream_reader<line> reader("istream_reader.hpp");
		std::ifstream file("istream_reader.h");
		foam::streams::istream_reader<item_type> reader(file);
		int len1 = 0;
		for(auto x : reader)
		{
			len1 += 1;//x.size();
			//std::cout << x << std::endl;
		}
		reader.reset();
		int len2 = 0;
		for(auto x : reader)
		{
			len2 += 1;//x.size();
			//std::cout << x << std::endl;
		}

		std::cout << "len1 = " << len1 << std::endl;
		std::cout << "len2 = " << len2 << std::endl;

//		auto add =  [](int a, item_type const &l) {return a + 1; };
//		std::cout << "std::accumulate = " << snl::algorithm::accumulate(reader, 0, add) << std::endl;

		reader.reset();
		std::vector<item_type> v = reader.take(10);
		std::vector<item_type> v1 = reader.take(10);
//		std::copy_n(reader.begin(), 10, std::back_inserter(v));
		for ( auto & a : v ) std::cout <<  "a=" << a << std::endl;
		for ( auto & b : v1 ) std::cout << "b=" << b << std::endl;
	
	}
	catch(std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
}
