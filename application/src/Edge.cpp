/**
 * \file   Edge.cpp
 *
 * \brief  Definicja klasy reprezentującej krawędź grafu
 *
 * \author Andrzej Roguski
 */

#include "Edge.hpp"

edge::edge( hours_array arr )
{
	for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i )
		weights[i] = arr[i];
}

edge::edge( hours_t n )
{
	for( unsigned i = 0; i < WEIGHTS_NUMBER; ++i )
		weights[i] = n;
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

