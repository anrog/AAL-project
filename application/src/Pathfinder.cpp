/**
 * \file Pathfinder.cpp
 *
 * \brief Implementacja klasy szukającej najlepszej ścieżki
 *
 * \author Andrzej Roguski
 */
#include <iostream>

#include "Pathfinder.hpp"
#include "types.hpp"
#include "debug.hpp"

pathfinder::pathfinder( graph * g ) : _graph( g ), nodes( g->size() ), best_time(DISTANCE_MAX)
{
	best = std::vector<search_node> (nodes);
	current = std::vector<search_node> (nodes);
}

void pathfinder::find_path( unsigned start, unsigned end, std::forward_list<unsigned> & path, hours_t & hour )
{
	hours_t best_hour = 0;

	for( unsigned i = 0; i < HOURS; ++i )
	{
		unsigned time = dijkstra( start, end, i );

		if( time < best_time )
		{
			best_time = time;
			best = current;
			best_hour = i;
		}
	}

	hour = best_hour;

	path.clear();

	DBG_DO
	(
	DBG("\nBest path:");
	for( unsigned i = 0; i < best.size(); ++i )
		std::cout << std::setw(2) << i << " ";
		std::cout << std::endl;
	for( auto i : best )
		std::cout << std::setw(2) << i.previous << " ";
		std::cout << std::endl;
	)

	unsigned node = end;

	while( node != start )
	{
		path.push_front(node);
		node = best[node].previous;
	}
}

unsigned pathfinder::dijkstra( unsigned start, unsigned end, hours_t start_hour )
{
	DBG( "dijkstra( " << start << ", " << end << ", " << (unsigned)start_hour << " )");

	for( unsigned i = 0; i < start; ++i )
		current[i] = search_node( i );

	current[start] = search_node( start, 0, start_hour );

	for( unsigned i = start + 1; i < nodes; ++i )
		current[i] = search_node( i );

	//for( unsigned i = 0; i < nodes; ++i )
	//	queue.push( current[i] );

	queue.push( current[start] );

	while( !queue.empty() )
	{
		search_node node = queue.top();

		queue.pop();

		unsigned number = node.number;

		unsigned distance = node.distance;

		hours_t hour = node.hour;

		if( distance <= current[number].distance )
		{
			if( _graph->isDense() )
			{
				for( unsigned i = 0; i < nodes; ++i )
				{
					if( (*(*_graph)[number])[i] == NULL_EDGE )
						continue;

					hours_t d = (*(*_graph)[number])[i].getDistance( hour );

					if( current[i].distance > distance + d )
					{
						current[i].distance = distance + d;

						current[i].hour = ( hour + d ) % HOURS;

						current[i].previous = number;

						queue.push( current[i] );
					}
				}
			}
			else
			{
				const node_sparse * n = static_cast<const node_sparse *>( (*_graph)[number] );

				for( map_iter it = n->begin(); it != n->end(); ++it )
				{
					unsigned i = it->first;

					hours_t d = (*(*_graph)[number])[i].getDistance( hour );

					if( current[i].distance > distance + d )
					{
						current[i].distance = distance + d;

						current[i].hour = ( hour + d ) % HOURS;

						current[i].previous = number;

						queue.push( current[i] );
					}

				}
			}
		}
	}

	DBG_DO
	(
	for( unsigned i = 0; i < current.size(); ++i )
		std::cout << std::setw(2) << i << " ";
		std::cout << std::endl;
	for( auto i : current )
		std::cout << std::setw(2) << i.previous << " ";
		std::cout << std::endl;
	)

	DBG_DO( std::cout<< " Distance: " << current[end].distance << std::endl; );
	return current[end].distance;	
}
