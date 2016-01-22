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

	bool isDense() const;

	unsigned size() const;
	
	const node * operator[]( unsigned n ) const;

	void print() const;

private:
	std::vector<node*> nodes;

	bool dense;
};

#endif // GRAPH_HPP
