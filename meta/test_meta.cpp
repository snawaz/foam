

#include <iostream>

#include <foam/meta/valuelist.h>
#include <foam/meta/algorithm.h>

int main()
{
	typedef foam::meta::generate_valuelist<10>::type valuelist;
	typedef foam::meta::reverse<valuelist>::type reversed_valuelist;
}
