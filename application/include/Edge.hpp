/**
 * \file   Edge.hpp
 *
 * \brief  Plik nagłówkowy klasy reprezentującej krawędź grafu
 *
 * \author Andrzej Roguski
 */

#ifndef EDGE_HPP
#define EDGE_HPP

#include <array>
#include "types.hpp"


class edge
{
public:
	edge( hours_array );

	edge( hours_t = 0 );

	bool operator==( const edge & that ) const;

	hours_t operator[]( unsigned short n ) const;

private:
	hours_array weights;
};

const edge NULL_EDGE = edge();

#endif // EDGE_HPP
