/**
 * \file Node.hpp
 *
 * \brief Plik nagłówkowy klasy reprezentującej węzeł grafu
 *
 * \author Andrzej Roguski
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <map>

#include "Edge.hpp"

class node
{
public:
	node( unsigned nodes, unsigned n );

	virtual const edge & operator[]( unsigned n ) const = 0;

	virtual void addEdge( unsigned target, edge e ) = 0;

	unsigned getNumber() const;

	virtual void print() const = 0;

	unsigned get_x() const;
	unsigned get_y() const;

protected:
	unsigned x;
	unsigned y;
	unsigned number;
};




class node_sparse final : public node
{
public:
	node_sparse( unsigned nodes, unsigned n = 0 );

	virtual const edge & operator[]( unsigned n ) const;

	virtual void addEdge( unsigned target, edge e );
	
	virtual void print() const;

	map_iter begin() const;

	map_iter end() const;
private:
	std::map<unsigned, edge> edges;
};




class node_dense final : public node
{
public:
	node_dense( unsigned nodes, unsigned n = 0 );

	virtual const edge & operator[]( unsigned n ) const;

	virtual void addEdge( unsigned target, edge e );

	virtual void print() const;
private:
	std::vector<edge> edges;

};

#endif // NODE_HPP
