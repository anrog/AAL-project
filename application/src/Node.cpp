/**
 * \file   Node.cpp
 *
 * \brief  Definicja klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#include "Node.hpp"

unsigned node::getNumber() const
{
	return number;
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
}


const edge & node_dense::operator[]( unsigned n ) const
{
	return edges[n];
}

void node_dense::addEdge( unsigned target, edge e )
{
	edges[ target ] = e;
}
