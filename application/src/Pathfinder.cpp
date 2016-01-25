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

	// dla każdej godziny powtórz algorytm dijkstry i wybierz najlepszy uzyskany czas
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

	// ustaw dystans do węzłów na DISTANCE_MAX dla wszystkich poza początkowym
	// początkowy ma dystans 0 
	for( unsigned i = 0; i < start; ++i )
		current[i] = search_node( i );

	current[start] = search_node( start, 0, start_hour );

	for( unsigned i = start + 1; i < nodes; ++i )
		current[i] = search_node( i );

	// wstaw węzeł początkowy do kolejki priorytetowej
	queue.push( current[start] );

	// dopóki są węzły w kolejce
	while( !queue.empty() )
	{
		// zdejmij z kolejki najbliższy węzeł
		search_node node = queue.top();

		queue.pop();

		unsigned number = node.number;

		unsigned distance = node.distance;

		hours_t hour = node.hour;

		// nic nie rób jeśli to był węzeł już przetworzony
		if( distance <= current[number].distance )
		{
			if( _graph->isDense() )
			{
				// dla każdego wierzchołka
				for( unsigned i = 0; i < nodes; ++i )
				{
					// jeśli nie jest sąsiadem - nic nie rób
					if( (*(*_graph)[number])[i] == NULL_EDGE )
						continue;

					hours_t d = (*(*_graph)[number])[i].getDistance( hour );

					// jeśli przez zdjety węzel można dotrzeć do sąsiada szybciej niż dotychczas
					if( current[i].distance > distance + d )
					{
						// ustaw nowy dystans, czas dotarcia i poprzednika
						current[i].distance = distance + d;

						current[i].hour = ( hour + d ) % HOURS;

						current[i].previous = number;

						// wstaw zmodyfikowany węzeł do kolejki
						queue.push( current[i] );
					}
				}
			}
			else
			{
				const node_sparse * n = static_cast<const node_sparse *>( (*_graph)[number] );

				// dla każdego sąsiada
				for( map_iter it = n->begin(); it != n->end(); ++it )
				{
					unsigned i = it->first;

					hours_t d = (*(*_graph)[number])[i].getDistance( hour );

					// jeśli przez zdjety węzel można dotrzeć do sąsiada szybciej niż dotychczas
					if( current[i].distance > distance + d )
					{
						// ustaw nowy dystans, czas dotarcia i poprzednika
						current[i].distance = distance + d;

						current[i].hour = ( hour + d ) % HOURS;

						current[i].previous = number;

						// wstaw zmodyfikowany węzeł do kolejki
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
