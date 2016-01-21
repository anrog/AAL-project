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

#include "limits.hpp"

typedef unsigned char hours_t;

typedef std::array<hours_t, WEIGHTS_NUMBER> hours_array;



#endif // TYPES_HPP
