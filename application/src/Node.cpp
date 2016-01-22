/**
 * \file   Node.cpp
 *
 * \brief  Definicja klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#include "Node.hpp"
#include "types.hpp"
#include "roll.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>


//=============================================================================
//                              node
//=============================================================================

node::node( unsigned nodes, unsigned n ) : number(n)
{
	unsigned map_size = std::max( (unsigned)10, (unsigned)sqrt(nodes) );	

	x = rollUniform(0, map_size);
	y = rollUniform(0, map_size);

}

unsigned node::get_x() const
{
	return x;
}

unsigned node::get_y() const
{
	return y;
}
unsigned node::getNumber() const
{
	return number;
}


//=============================================================================
//                          node_sparse
//=============================================================================

node_sparse::node_sparse( unsigned nodes, unsigned n ) : node( nodes, n )
{

}

const edge & node_sparse::operator[]( unsigned n ) const
{
	try
	{
		return edges.at(n);
	}
	catch( std::out_of_range e )
	{
		return NULL_EDGE;
	}
}

void node_sparse::addEdge( unsigned target, edge e )
{
	edges[ target ] = e;
	++number;
}

void node_sparse::print() const
{
	for( map_iter it = edges.begin(); it != edges.end(); ++it )
	{
		std::cout << "  " << std::setw(2) << it->first << " [ ";
		it->second.print();
		std::cout << " ]" << std::endl;
	}
}

map_iter node_sparse::begin() const
{
	return edges.begin();
}

map_iter node_sparse::end() const
{
	return edges.end();
}

//=============================================================================
//                           node_dense
//=============================================================================

node_dense::node_dense( unsigned nodes, unsigned n ) : node( nodes, n )
{
	edges = std::vector<edge> (nodes);	
}

const edge & node_dense::operator[]( unsigned n ) const
{
	return edges[n];
}

void node_dense::addEdge( unsigned target, edge e )
{
	edges[ target ] = e;
	++number;
}

void node_dense::print() const
{
	for( unsigned i = 0; i < edges.size(); ++i )
	{
		std::cout << "  " << std::setw(2) << i << " [ ";
		edges[i].print();
		std::cout << " ]" << std::endl;
	}
}
