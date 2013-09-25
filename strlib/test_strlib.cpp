
#include <iostream>

#include <foam/strlib/strlib.h>

#include <cstdio>

int main()
{
	try
	{
		using foam::strlib::print;
		using foam::strlib::ltrim;
		using foam::strlib::rtrim;
		using foam::strlib::trim;
		using foam::strlib::startswith;
		using foam::strlib::endswith;
		using foam::strlib::string_builder;

		string_builder sb;
		sb.write("\n", "Sarfaraz", "Nawaz", 100, "Done");
		std::cout << sb.to_string() << std::endl;

		std::cout << "|" << ltrim(" \t\r\n   ltrim    testing     ") << "|" << std::endl;
		std::cout << "|" << rtrim("      rtrim    testing \t\r\n    ") << "|" << std::endl;
		std::cout << "|" << trim("   \t\r\n   trim    testing   \t\r\n  ") << "|" << std::endl;

		std::cout << startswith(".txt", "file.txt") << std::endl;
		std::cout << startswith("file", "file.txt") << std::endl;
		std::cout << startswith("", "file.txt") << std::endl;
		std::cout << startswith(".txt", "") << std::endl;
		std::cout << startswith("", "") << std::endl;
		std::cout << endswith(".txt", "file.txt") << std::endl;
		std::cout << endswith("file", "file.txt") << std::endl;
		std::cout << endswith("", "file.txt") << std::endl;
		std::cout << endswith(".txt", "") << std::endl;
		std::cout << endswith("", "") << std::endl;

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
