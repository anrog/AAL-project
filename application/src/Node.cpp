/**
 * \file   Node.cpp
 *
 * \brief  Definicja klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#include "Node.hpp"

node::node( unsigned n ) : number(n)
{

}

unsigned node::getNumber() const
{
	return number;
}


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


node_dense::node_dense( unsigned n ) : node( n )
{

}

void node_sparse::addEdge( unsigned target, edge e )
{
	edges[ target ] = e;
	++number;
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
