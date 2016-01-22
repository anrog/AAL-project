/**
 * \file   types.hpp
 *
 * \brief  Plik nagłówkowy z deklaracjami typów danych
 *
 * \author Andrzej Roguski
 */

#ifndef TYPES_HPP
#define TYPES_HPP


#include <array>
#include <map>

#include "limits.hpp"

typedef unsigned char hours_t;

typedef std::array<hours_t, WEIGHTS_NUMBER> hours_array;

class edge;
typedef std::map<unsigned, edge>::const_iterator map_iter;

#endif // TYPES_HPP
