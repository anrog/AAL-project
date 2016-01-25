/**
 * \file   limits.hpp
 *
 * \brief  Plik nagłówkowy z deklaracjami stałych
 *
 * \author Andrzej Roguski
 */

#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <limits>

const unsigned short WEIGHTS_NUMBER = 4;

const unsigned short WIEGHT_MIN = 1;
const unsigned short WIEGHT_MAX = 20;

const unsigned short HOURS = 24;
const unsigned short HOURS_PER_WEIGHT = 6;

const unsigned DISTANCE_MAX = std::numeric_limits<unsigned>::max();

const unsigned GRAPH_MAX_SIZE = 10000;

#endif // LIMITS_HPP
