/**
 * \file   Node.cpp
 *
 * \brief  Definicja klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#include "Node.hpp"
#include <iostream>
#include <iomanip>


//=============================================================================
//                              node
//=============================================================================

node::node( unsigned n ) : number(n)
{

}

unsigned node::getNumber() const
{
	return number;
}


//=============================================================================
//                          node_sparse
//=============================================================================

node_sparse::node_sparse( unsigned n ) : node( n )
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
	typedef std::map<unsigned, edge>::const_iterator iter;

	for( iter it = edges.begin(); it != edges.end(); ++it )
	{
		std::cout << "  " << std::setw(2) << it->first << " [ ";
		it->second.print();
		std::cout << " ]" << std::endl;
	}
}


//=============================================================================
//                           node_dense
//=============================================================================

node_dense::node_dense( unsigned n ) : node( n )
{

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
