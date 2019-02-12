/*************************************************************************
                           Graph  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <memory>
#include "Node.h"

//------------------------------------------------------------------------
// Goal of the <Graph> class
// Represents a directed Graph, i.e. a set of Node instances linked together.
// When using a Graph to manipulate Nodes, rather than manipulating Nodes directly,
// the Graph makes sure than only a single instance of Node is created for each different
// value. DataType must be comparable as per std::map requirements.
//------------------------------------------------------------------------

template < typename DataType >
class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Public methods

    /*
     * Creates an edge in the graph between the two given values (where each value is a node)
     * If a Node instance already exists for the given values, it is used, otherwise a new
     * instance is created.
     */
    void add ( DataType from, DataType to )
    {
        if( !nodes.count ( from ) )
            nodes [ from ] = std::make_shared < Node < DataType > > ( from );
        if( !nodes.count ( to ) )
            nodes [ to ] = std::make_shared < Node < DataType > > (to);
        nodes [ from ] -> addEdge ( nodes [ to ] );
    }

    /*
     * Displays the Graph in dot format
     * (see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
     */
    friend std::ostream & operator << ( std::ostream & out, const Graph < DataType > & g )
    {
        auto & nodes = g.nodes;

        out << "digraph {" << std::endl;

        // itérer pour afficher les noeuds
        for ( auto it = nodes.begin ( ); it != nodes.end ( ); ++it )
            out << "\t\"" << it -> first << "\";" << std::endl;

        // réitérer pour afficher les arcs
        for ( auto nodeIt = nodes.begin ( ); nodeIt != nodes.end ( ); ++nodeIt )
        {
            auto & node = nodeIt -> second;
            auto & edges = node -> getEdges ( );

            for ( auto edgeIt = edges.begin ( ); edgeIt != edges.end ( ); ++edgeIt )
            {
                out << "\t\"" << nodeIt -> first << "\" -> \""
                    << edgeIt -> first -> getData ( )
                    << "\" [label=\""<< edgeIt -> second << "\"];" << std::endl;
            }
        }

        return out << '}';
    }

//-------------------------------------------- Constructor - destructor

    explicit Graph ( ) = default;

    ~Graph ( ) = default;

protected:
//----------------------------------------------------- Protected attributes

    std::map < DataType, std::shared_ptr < Node < DataType > > > nodes;
};

#endif // GRAPH_H
