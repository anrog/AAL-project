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
#include <cmath>

#include "Pathfinder.hpp"
#include "roll.hpp"
#include "debug.hpp"

clock_t test( unsigned size, bool dense, std::string filename = "" )
{
	graph * g;

	if( filename == "" )
	{
		std::cout << std::endl << "TESTING" << std::endl;

		std::cout << "Size == " << size << ", dense == " << std::boolalpha << dense << std::endl;

		std::cout << "Generating a graph... " << std::endl;
		
		g = new graph( size, dense );
	}
	else
		g = new graph( filename );

	DBG_DO( g->print() );

	if( filename == "" )
		std::cout << "Done." << std::endl;

	pathfinder p = pathfinder( g );

	std::forward_list<unsigned> l;

	hours_t h;
	
	unsigned start;
	unsigned end;

	if( filename == "" )
	{
		start = rollUniform(0, g->size() - 1);
		end = rollUniform(0, g->size() - 1);
	}
	else
	{
		start = 0;
		end = g->size() - 1;
	}

	clock_t c_start = std::clock();
	p.find_path(start, end, l, h);
	clock_t time = std::clock() - c_start;

	std::cout << "Path:" << std::endl;

	std::cout << "  " << start;

	while( !l.empty() )
	{
		std::cout << "  " << l.front();
		l.pop_front();
	}

	std::cout << std::endl;
	std::cout << "Hour: " << (unsigned)h << std::endl;

	delete g;

	return time;
}

void test( unsigned * test_array, const unsigned size )
{
	clock_t * times_dense = new clock_t [size];
	clock_t * times_sparse = new clock_t [size];

	double * q_dense = new double [size];
	double * q_sparse = new double [size];

	unsigned mediana = ( (size + 1) >> 1 ) - 1;

	for( unsigned i = 0; i < size ; ++i )
		times_sparse[i] = test( test_array[i], false );


	for( unsigned i = 0; i < size; ++i )
		times_dense[i] = test( test_array[i], true );

	for( unsigned i = 0; i < size; ++i )
	       q_dense[i] = ( (double)times_dense[i] * test_array[mediana] * test_array[mediana] * log2(test_array[mediana])) 
		          / ( test_array[i] * test_array[i] * log2(test_array[i]) * (double)times_dense[mediana] );

	for( unsigned i = 0; i < size; ++i )
	       q_sparse[i] = ( (double)times_sparse[i] * test_array[mediana] * log2(test_array[mediana])) 
		          / ( test_array[i] * log2(test_array[i]) * (double)times_sparse[mediana] );

	std::cout << std::endl;
	std::cout << "             Dense Graphs"<< std::endl;
	std::cout << " |     n     |   t[ms]   |     q     |" << std::endl;
	std::cout << " -------------------------------------" << std::endl;
	
	for( unsigned i = 0; i < size ; ++i )
		std::cout << " |" << std::setw(10) << test_array[i] 
			  << " |" << std::setw(10) << (double)times_dense[i] / CLOCKS_PER_SEC * 1000.0 
			  << " |" << std::setw(10) << q_dense[i]
			  << " |" << std::endl;

	std::cout << std::endl;
	std::cout << "             Sparse Graphs"<< std::endl;
	std::cout << " |     n     |   t[ms]   |     q     |" << std::endl;
	std::cout << " -------------------------------------" << std::endl;
	
	for( unsigned i = 0; i < size ; ++i )
		std::cout << " |" << std::setw(10) << test_array[i] 
			  << " |" << std::setw(10) << (double)times_sparse[i] / CLOCKS_PER_SEC * 1000.0 
			  << " |" << std::setw(10) << q_sparse[i]
			  << " |" << std::endl;

	delete [] times_dense;
	delete [] times_sparse;
	delete [] q_dense;
	delete [] q_sparse;
}


void test_range( unsigned min, unsigned max, unsigned count )
{
	unsigned * array = new unsigned [count];

	if( count == 1 )
		array[0] = min;

	else
	{
		unsigned step = ( max - min ) / (count - 1);


		unsigned number = min;

		for( unsigned i = 0; i < count; ++i)
		{
			array[i] = number;
			number += step;
		}
	}

	test( array, count );

	delete [] array;
}


void help()
{
	std::cout << "Opcje:" << std::endl
	          << "    -f nazwa_pliku     - wczytaj graf z pliku nazwa_pliku" << std::endl
	          << "    -t min max num     - generuj num grafów o liczbie wierzchołków między min a max" << std::endl;
}

void t( char ** argv )
{
	if( std::string( argv[1] ) == "-t" )
	{
		int min;
		int max;
		int num;
		
		try
		{
			min = std::stoi( argv[2] );
			max = std::stoi( argv[3] );
			num = std::stoi( argv[4] );

			if( min < 1 || max < 1 || num < 1 )
			{
				std::cout << "[ERR] Błędny argument: liczba niedodatnia" << std::endl;
				exit(1);
			}

			if( num > max - min + 1 )
			{
				std::cout << "[ERR] Błędny argument: zadana liczba grafów nie mieści się w przedziale" << std::endl;
				exit(1);
			}

			if( min > max )
			{
				std::cout << "[ERR] Błędny argument: min > max" << std::endl;
				exit(1);
			}

			if( (unsigned)max > GRAPH_MAX_SIZE )
			{
				std::cout << "[ERR] Błędny argument: max większe niż dopuszczlny limit (" << GRAPH_MAX_SIZE << ")" << std::endl;
				exit(1);
			}
		}
		catch( std::invalid_argument e )
		{
			std::cout << "[ERR] Błędny argument: oczekiwane liczby dodatnie" << std::endl;
			exit(1);
		}

		test_range( min, max, num );
	}
	else
		help();

}

void f( char ** argv )
{
	if( std::string( argv[1] ) == "-f" )
	{
		test(0, 0, std::string( argv[2] ) );
	}
	else
		help();

}

int main ( int argc, char ** argv )
{
	switch(argc)
	{
		case 3:
			f( argv );
			break;
		case 5:
			t( argv );
			break;
		default:
			help();
	}

	return 0;
}
