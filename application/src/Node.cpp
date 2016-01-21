/**
 * \file   Node.cpp
 *
 * \brief  Definicja klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#include "Node.hpp"

unsigned node::getNumber() const
{
	return number;
}

const edge & node_sparse::operator[]( unsigned n ) const
{
	return NULL_EDGE;
}
	
const edge & node_dense::operator[]( unsigned n ) const
{
	return NULL_EDGE;
}

