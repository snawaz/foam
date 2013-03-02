
#include <iostream>
#include "strlib.hpp"
#include <cstdio>
int main()
{
	try
	{
		using snl::strlib::print;
		using snl::strlib::string_builder;

		string_builder sb;
		sb.write("\n", "Sarfaraz", "Nawaz", 100, "Done");
		std::cout << sb.to_string() << std::endl;

		std::printf("|%10s|\n", "NAWAZ");
		std::printf("|%-10s|\n", "NAWAZ");
//		print("{1}\n", "Sarfaraz", "Nawaz");
		print("|{0,10}|\n", "Sarfaraz");
		print("|{0,-10}|\n", "Sarfaraz");
		print("my name is {2,10} {1}. {0} and {1}", "Sarfaraz", "Nawaz");
	}
	catch(std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
}
