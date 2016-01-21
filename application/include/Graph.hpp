/**
 * \file Graph.hpp
 *
 * \brief Plik nagłówkowy klasy reprezentującej graf
 *
 * \author Andrzej Roguski
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

#include "Node.hpp"

class graph
{
public:
	graph( unsigned node_number, bool dense );

	graph( std::string filename );
	
	const node * operator[]( unsigned n ) const;

private:
	std::vector<node*> nodes;
};

#endif // GRAPH_HPP
