

#include <iostream>
#include "function.h"

void f(int a) { std::cout << "void f()" << a << std::endl; }
void g(int a) { std::cout << "void g()" << a << std::endl; }
int h(int a) { std::cout << "void h()" << a << std::endl; return 0; }

typedef foam::functional::multifunction<void(int)> event;
typedef event::argument_types args;
typedef event::remover_type remover_type;

void caller(event e)
{
	std::cout << (bool) e << std::endl;
}
auto safe_call = [] (remover_type & r)
{
	try { r(); }
	catch(std::exception const & e) { std::cout << e.what() << std::endl; }
};
void call(remover_type r)
{
	std::cout << "\ninside call\n";
	safe_call(r);
}
int main()
{
	try
	{

		event e;
//		args::get<3>::type i = 0;

		auto rf = e.add(f);
		auto rg = e.add(g);
		auto rh = e.add(h);
	
		//caller(std::move(e));
		std::cout << (bool) e << std::endl;

		//e.add(std::function<void(int)>(f));
	
		auto removers = e.add_many(h,g,f);

		e(10); std::cout <<"\n";
		safe_call(rf);
		e(12); std::cout <<"\n";
		safe_call(rf);
		e(14); std::cout <<"\n";
		safe_call(rf);

		for(auto && r : removers) r();

		auto  x = std::move(rf);

		e(16); std::cout <<"\n";
		safe_call(rf);
		e(18); std::cout <<"\n";
		safe_call(rf);
		e(20); std::cout <<"\n";
		safe_call(rf);

		call(std::move(x));
	}
	catch(std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
