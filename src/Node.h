/*************************************************************************
                           Node  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Node> (fichier Node.h) ----------------
#ifndef NODE_H
#define NODE_H

#include <memory>
#include <unordered_map>

//------------------------------------------------------------------------
// Rôle de la classe <Node>

//------------------------------------------------------------------------

template<typename DataType>
class Node
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    const DataType& getData() const
    {
        return data;
    }

    const std::unordered_map<std::shared_ptr<Node<DataType>>, unsigned>& getEdges() const
    {
        return edges;
    }

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

    explicit Node(DataType data) : data(data) {}

    ~Node() = default;

protected:
//----------------------------------------------------- Attributs protégés

    DataType data;

    std::unordered_map<std::shared_ptr<Node<DataType>>, unsigned> edges;
};

#endif // NODE_H