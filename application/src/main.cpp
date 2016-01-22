/**
 * \file   main.cpp
 *
 * \brief  Plik główny projektu
 *
 * \author Andrzej Roguski
 */

#include <iostream>
#include <iomanip>
#include <ctime>

#include "Pathfinder.hpp"
#include "roll.hpp"

clock_t test( unsigned size, bool dense )
{
	std::cout << std::endl << "TESTING" << std::endl;

	std::cout << "Size == " << size << ", dense == " << std::boolalpha << dense << std::endl;

	std::cout << "Generating a graph... " << std::endl;
	graph g = graph( size, dense );
	std::cout << "Done." << std::endl;

	pathfinder p = pathfinder( &g );

	std::forward_list<unsigned> l;

	hours_t h;
	
	unsigned start = rollUniform(0, size - 1);
	unsigned end   = rollUniform(0, size - 1);

	clock_t c_start = std::clock();
	p.find_path(start, end, l, h);
	clock_t time = std::clock() - c_start;

	std::cout << "Path:" << std::endl;

	while( !l.empty() )
	{
		std::cout << "  " << l.front();
		l.pop_front();
	}
	std::cout << std::endl;
	std::cout << "Hour: " << (unsigned)h << std::endl;

	return time;
}

void test( unsigned * test_array, const unsigned size )
{
	clock_t times_dense [size];
	clock_t times_sparse [size];

	for( unsigned i = 0; i < size ; ++i )
		times_sparse[i] = test( test_array[i], false );


	for( unsigned i = 0; i < size ; ++i )
		times_dense[i] = test( test_array[i], true );

	std::cout << std::endl;
	std::cout << "       Dense Graphs"<< std::endl;
	std::cout << "|     n     |   t[ms]   |" << std::endl;
	std::cout << "-------------------------" << std::endl;
	
	for( unsigned i = 0; i < size ; ++i )
		std::cout << "|" << std::setw(10) << test_array[i] << " | " << std::setw(10) << (double)times_dense[i] / CLOCKS_PER_SEC * 1000.0 << "|" << std::endl;

	std::cout << std::endl;
	std::cout << "      Sparse Graphs"<< std::endl;
	std::cout << "|     n     |   t[ms]   |" << std::endl;
	std::cout << "-------------------------" << std::endl;
	
	for( unsigned i = 0; i < size ; ++i )
		std::cout << "|" << std::setw(10) << test_array[i] << " | " << std::setw(10) << (double)times_sparse[i] / CLOCKS_PER_SEC * 1000.0 << "|" << std::endl;

}

void test_big()
{
	unsigned test_array [] = 
	{
		10,
		20,
		50,
		100,
		200,
		500,
		1000,
		2000,
		5000,
	};
	test( test_array, 9 );
}

void test_lin()
{
	unsigned test_array [] = 
	{
		100,
		200,
		300,
		400,
		500,
		600,
		700,
		800,
		900,
		1000,
		1100,
		1200,
		1300,
		1400,
		1500,
		1600,
		1700,
		1800,
		1900,
		2000,
		2100,
		2200,
		2300,
		2400,
		2500,
		2600,
		2700,
		2800,
		2900,
		3000,

	};
	test( test_array, 30 );
}


int main ( int argc, char ** argv )
{
	test_big();

	test_lin();


	return 0;
}
