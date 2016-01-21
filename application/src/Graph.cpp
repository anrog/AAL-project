/**
 * \file   Graph.cpp
 *
 * \brief  Definicja klasy reprezentującej graf
 *
 * \author Andrzej Roguski
 */

#include "Graph.hpp"
#include "roll.hpp"

graph::graph( unsigned node_number, bool dense )
{
	double p;

	if( dense )
		p = (double)rollUniform( 5000, 100000 ) / 100000.0;

	else
		p = (double)rollUniform( 1000, 9000 ) / 1000.0 / (double)node_number;

	for( unsigned i = 0; i < node_number; ++i )
	{
		node * n = new node_sparse();

		edge e = edge(); 

		n->addEdge( rollUniform(0, i), e );

		nodes.push_back( n );

		for( unsigned j = 0; j < i; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed = edge();

				n->addEdge( j, ed );
			}	
		}

		for( unsigned j = i + 1; j < node_number; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed;

				n->addEdge( j, ed );
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

