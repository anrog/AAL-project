/**
 * \file   Edge.cpp
 *
 * \brief  Definicja klasy reprezentującej krawędź grafu
 *
 * \author Andrzej Roguski
 */

#include "Edge.hpp"
#include "roll.hpp"

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

