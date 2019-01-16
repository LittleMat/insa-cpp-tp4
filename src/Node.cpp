/*************************************************************************
                           Node  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Node> (fichier Node.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Node.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//-------------------------------------------- Constructeurs - destructeur



Node::Node ( )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au constructeur de <Node>" << endl;
	#endif
} //----- Fin de Node

Node::~Node ( )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au destructeur de <Node>" << endl;
	#endif
}
//----- Fin de ~Node