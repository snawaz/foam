

#include <iostream>

#include "valuelist.h"
#include "algorithm.h"

int main()
{
	typedef foam::meta::generate_valuelist<10>::type valuelist;
	typedef foam::meta::reverse<valuelist>::type reversed_valuelist;
}
