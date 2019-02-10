/*************************************************************************
                           Node  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Node> (file Node.h) ----------------
#ifndef NODE_H
#define NODE_H

#include <memory>
#include <unordered_map>

//------------------------------------------------------------------------
// Goal of the <Node> class
// Represents a node (or vertex) in a directed graph.
// A Node holds a value of generic type and edges to the next Nodes.
// Each edge is associated with the number of times the edge was added to the Node.
//------------------------------------------------------------------------

template<typename DataType>
class Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Public methods

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
//-------------------------------------------- Constructor - destructor

    /*
     * Builds
     */
    explicit Node(DataType data) : data(data) {}

    ~Node() = default;

protected:
//----------------------------------------------------- Protected attributes

    DataType data;

    std::unordered_map<std::shared_ptr<Node<DataType>>, unsigned> edges;
};

#endif // NODE_H