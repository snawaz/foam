

#include <iostream>
#include "valuelist.hpp"
#include "algorithm.hpp"

int main()
{
	typedef snl::meta::generate_valuelist<10>::type valuelist;
	typedef snl::meta::reverse<valuelist>::type reversed_valuelist;
}
