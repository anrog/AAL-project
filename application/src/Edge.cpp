/**
 * \file   Edge.cpp
 *
 * \brief  Definicja klasy reprezentującej krawędź grafu
 *
 * \author Andrzej Roguski
 */

#include <iostream>
#include <iomanip>

#include "Edge.hpp"
#include "roll.hpp"
#include "limits.hpp"

edge::edge( hours_array arr )
{
	for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i )
		weights[i] = arr[i];
}

edge::edge( bool uniform, hours_t min, hours_t max )
{
	if( uniform )
		for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i)
			weights[i] = rollUniform( min, max );

	else
	{
		hours_t value = ( max + min ) / 2;
		
		for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i)
			weights[i] = rollBinomial( value, min, max );
	}

}

edge::edge( unsigned x1, unsigned y1, unsigned x2, unsigned y2 )
{
	unsigned d_x = abs( x1 - x2 );
	unsigned d_y = abs( y1 - y2 );

	d_x *= d_x;
	d_y *= d_y;

	unsigned distance = sqrt( d_x + d_y );

	for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i)
		weights[i] = rollUniform( distance * 0.7, distance * 1.3 + 1 );

}

bool edge::operator==( const edge & that ) const
{	
	for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i )
		if( weights[i] != that.weights[i] )
			return false;
	
	return true;
}

hours_t edge::operator[]( unsigned short n ) const
{
	return weights[ n ];
}

hours_t edge::getDistance( hours_t time ) const
{
	return weights[ time / HOURS_PER_WEIGHT ];
}


void edge::print() const
{
	for( unsigned i = 0; i< WEIGHTS_NUMBER; ++i )
		std::cout << std::setw(2) << (unsigned)weights[ i ] << " ";
}

