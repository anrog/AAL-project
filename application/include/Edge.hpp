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
#include "Node.hpp"


class edge
{
public:
	edge( hours_array arr );

	edge( bool uniform = true, hours_t min = WIEGHT_MIN, hours_t max = WIEGHT_MAX );

	edge( unsigned x1, unsigned y1, unsigned x2, unsigned y2 );

	bool operator==( const edge & that ) const;

	hours_t operator[]( unsigned short n ) const;

	hours_t getDistance( hours_t time ) const;

	void print() const;

private:
	hours_array weights;
};

const static hours_array a = {0};

const edge NULL_EDGE = edge( a );

#endif // EDGE_HPP
