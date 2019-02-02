/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <memory>
#include "Node.h"

//------------------------------------------------------------------------
// Rôle de la classe <Graph>

//------------------------------------------------------------------------

template<typename DataType>
class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void add(DataType from, DataType to)
    {
        if(!nodes.count(from))
            nodes[from] = std::make_shared<Node<DataType>>(from);
        if(!nodes.count(to))
            nodes[to] = std::make_shared<Node<DataType>>(to);
        nodes[from]->addEdge(nodes[to]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Graph<DataType>& g)
    {
        auto& nodes = g.nodes;

        out << "digraph {" << std::endl;

        // itérer pour afficher les noeuds
        for(auto it = nodes.begin(); it != nodes.end(); ++it)
            out << "\t\"" << it->first << "\";" << std::endl;

        // réitérer pour afficher les arcs
        for(auto nodeIt = nodes.begin(); nodeIt != nodes.end(); ++nodeIt)
        {
            auto& node = nodeIt->second;
            auto& edges = node->getEdges();

            for(auto edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt)
            {
                out << "\t\"" << nodeIt->first << "\" -> \""
                    << edgeIt->first->getData()
                    << "\" [label=\""<< edgeIt->second << "\"];" << std::endl;
            }
        }

        return out << '}';
    }

//-------------------------------------------- Constructeur - destructeur

    explicit Graph() = default;

    ~Graph() = default;

protected:
//----------------------------------------------------- Attributs protégés

    std::map<DataType, std::shared_ptr<Node<DataType>>> nodes;
};



#endif // GRAPH_H