/*************************************************************************
                           Node  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#ifndef NODE_H
#define NODE_H

#include <memory>
#include <unordered_map>

//------------------------------------------------------------------------
// Rôle de la classe <Node>
// Represents a node (or vertex) in a directed graph.
// A Node holds a value of generic type and edges to the next Nodes.
// Each edge is associated with the number of times the edge was added to the Node.
//------------------------------------------------------------------------

template<typename DataType>
class Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    /*
     * Returns the data held by this Node
     */
    const DataType& getData() const
    {
        return data;
    }

    /*
     * Returns the map representing the edges of the Node.
     * The key is the Node linked to this Node by the edge.
     * The value is the number of times the link occurred.
     */
    const std::unordered_map<std::shared_ptr<Node<DataType>>, unsigned>& getEdges() const
    {
        return edges;
    }

    /*
     * Adds an edge between this Node and the given Node.
     * If such an edge already exists, it increments the counter associated with the edge.
     */
    void addEdge(std::shared_ptr<Node<DataType>>& node)
    {
        if(edges.count(node))
        {
            edges[node]++;
        }
        else
        {
            edges[node] = 1;
        }
    }
//-------------------------------------------- Constructeur - destructeur

    /*
     * Builds
     */
    explicit Node(DataType data) : data(data) {}

    ~Node() = default;

protected:
//----------------------------------------------------- Attributs protégés

    DataType data;

    std::unordered_map<std::shared_ptr<Node<DataType>>, unsigned> edges;
};

#endif // NODE_H