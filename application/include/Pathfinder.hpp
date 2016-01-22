/**
 * \file Pathfinder.hpp
 *
 * \brief Plik nagłówkowy klasy szukającej najlepszej ścieżki
 *
 * \author Andrzej Roguski
 */

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <queue>
#include <vector>
#include <forward_list>

#include "Graph.hpp"
#include "SearchNode.hpp"

class pathfinder
{
public:
	pathfinder( graph * g );

	void find_path( unsigned start, unsigned end, std::forward_list<unsigned> & path, hours_t & hour );

private:
	unsigned dijkstra( unsigned start, unsigned end, hours_t hour );

	graph * _graph;

	unsigned nodes;

	unsigned best_time;

	std::vector<search_node> best;
	std::vector<search_node> current;

	std::priority_queue<search_node> queue;
};

#endif // PATHFINDER_HPP
