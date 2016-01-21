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
	virtual const edge & operator[]( unsigned n ) const = 0;

	virtual void addEdge( unsigned target, edge e ) = 0;

	unsigned getNumber() const;

private:
	unsigned number;
};




class node_sparse final : public node
{
public:
	virtual const edge & operator[]( unsigned n ) const;

	virtual void addEdge( unsigned target, edge e );
	

private:
	std::map<unsigned, edge> edges;
};




class node_dense final : public node
{
public:
	virtual const edge & operator[]( unsigned n ) const;

	virtual void addEdge( unsigned target, edge e );

private:
	std::vector<edge> edges;

};

#endif // NODE_HPP
