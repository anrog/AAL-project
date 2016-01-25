/**
 * \file   Graph.cpp
 *
 * \brief  Definicja klasy reprezentującej graf
 *
 * \author Andrzej Roguski
 */

#include <iostream>
#include <fstream>

#include "Graph.hpp"
#include "roll.hpp"
#include "debug.hpp"

graph::graph( unsigned node_number, bool dense ) : dense(dense)
{
	double p;

	nodes = std::vector<node *> (node_number);

	if( dense )
		p = 0.9;

	else
		p = std::min( 0.2, 5.0 / (double)node_number );

	if( dense )
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_dense(node_number);
	else
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_sparse(node_number);

	for( unsigned i = 1; i < node_number; ++i )
	{	   

		unsigned r = rollUniform( 0, i-1 );	

		edge e1 = edge( nodes[i]->get_x(), nodes[i]->get_y(), nodes[r]->get_x(), nodes[r]->get_y() );

		nodes[ i ]->addEdge( r, e1 );

		edge e2 = edge( nodes[i]->get_x(), nodes[i]->get_y(), nodes[r]->get_x(), nodes[r]->get_y() );

		nodes[ r ]->addEdge( i, e2 );

		for( unsigned j = 0; j < i; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed1 = edge(nodes[i]->get_x(), nodes[i]->get_y(), nodes[j]->get_x(), nodes[j]->get_y());

				nodes[i]->addEdge( j, ed1 );

				edge ed2 = edge(nodes[i]->get_x(), nodes[i]->get_y(), nodes[j]->get_x(), nodes[j]->get_y());

				nodes[j]->addEdge( i, ed2 );
			}	
		}

		for( unsigned j = i + 1; j < node_number; ++j )
		{
			if( rollBinary( p ) )
			{
				edge ed1 = edge(nodes[i]->get_x(), nodes[i]->get_y(), nodes[j]->get_x(), nodes[j]->get_y());

				nodes[i]->addEdge( j, ed1 );

				edge ed2 = edge(nodes[i]->get_x(), nodes[i]->get_y(), nodes[j]->get_x(), nodes[j]->get_y());

				nodes[j]->addEdge( i, ed2 );
			}
		}
	}
}

graph::graph( std::string filename )
{
	std::ifstream ifs ( filename );

	if( !ifs.good() )
	{
		std::cout << "[ERR] Błąd podczas otwierania pliku" << std::endl;
		exit(1);
	}

	unsigned node_number;
	unsigned edges;
	unsigned node;
	unsigned tmp;

	hours_array weights;

	ifs >> dense;
	DBG(dense);
	ifs >> node_number;
	DBG(node_number);

	/* 
	 * nodes = std::vector<nodes *> (node_number);
	 * powoduje zupełnie absurdalny błąd - kompilator stwierdza, że argument szablonu jest błędny
	 * żeby było śmieszniej, dokładnie ta sama linia jest w poprzednim konstruktorze
	 */
	nodes.resize(node_number);

	DBG(nodes.size());
	
	if( dense )
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_dense(node_number);
	else
		for( unsigned i = 0; i < node_number; ++i )
			nodes[ i ] = new node_sparse(node_number);

	for( unsigned i = 0; i < node_number; ++i )
	{
		ifs >> edges;

		for( unsigned k = 0; k < edges; ++k)
		{
			ifs >> node;

			for( unsigned j = 0; j < WEIGHTS_NUMBER; ++j )
			{
				ifs >> tmp;
				weights[j] = tmp & 0xFF;
			}

			edge e = edge( weights );

			nodes[i]->addEdge( node, e );
		}
	}
}	

bool graph::isDense() const
{
	return dense;
}

unsigned graph::size() const
{
	return nodes.size();
}

const node * graph::operator[]( unsigned n ) const
{
	return nodes[n];
}

void graph::print() const
{
	for( unsigned i = 0; i < nodes.size(); ++i )
	{
		std::cout << i << ":" << std::endl;
		nodes[i]->print();
	}
}

