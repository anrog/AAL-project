/**
 * \file SearchNode.hpp
 *
 * \brief Plik nagłówkowy klasy reprezentujacej wierzchołek wraz z informacjami
 *        niesbędnymi do przeszukiwania grafu.
 *
 * \author Andrzej Roguski
 */

#ifndef SEARCH_NODE_HPP
#define SEARCH_NODE_HPP

#include "types.hpp"

class search_node
{
public:
	search_node( unsigned number = 0, unsigned distance = DISTANCE_MAX, hours_t hour = 0 ) : number(number), distance(distance), hour(hour), previous(0)
	{

	}

	bool operator<(const search_node & that) const
	{
		return this->distance > that.distance;
	}

	unsigned number;

	unsigned distance;

	hours_t hour;

	unsigned previous;
};

#endif // SEARCH_NODE_HPP
