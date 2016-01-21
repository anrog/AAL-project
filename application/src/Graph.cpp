/**
 * \file   Graph.cpp
 *
 * \brief  Definicja klasy reprezentującej graf
 *
 * \author Andrzej Roguski
 */

#include <iostream>

#include "Graph.hpp"
#include "roll.hpp"

graph::graph( unsigned node_number, bool dense )
{
	double p;

	nodes = std::vector<node *> (node_number);

	if( dense )
		p = (double)rollUniform( 5000, 100000 ) / 100000.0;

	else
		p = (double)rollUniform( 1000, 5000 ) / 1000.0 / (double)node_number;

	if( dense )
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_dense();
	else
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_sparse();

	for( unsigned i = 1; i < node_number; ++i )
	{	       
		unsigned r = rollUniform( 0, i-1 );	

		edge e1 = edge();

		nodes[ i ]->addEdge( r, e1 );

		edge e2 = edge();

		nodes[ r ]->addEdge( i, e2 );

		for( unsigned j = 0; j < i; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed1 = edge();

				nodes[i]->addEdge( j, ed1 );

				edge ed2 = edge();

				nodes[j]->addEdge( i, ed2 );
			}	
		}

		for( unsigned j = i + 1; j < node_number; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed1 = edge();

				nodes[i]->addEdge( j, ed1 );

				edge ed2 = edge();

				nodes[j]->addEdge( i, ed2 );
			}
		}
	}
}

graph::graph( std::string filename )
{

}	

const node * graph::operator[]( unsigned n ) const
{
	return nullptr;
}

void graph::print() const
{
	for( unsigned i = 0; i < nodes.size(); ++i )
	{
		std::cout << i << ":" << std::endl;
		nodes[i]->print();
	}
}

