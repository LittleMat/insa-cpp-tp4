/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Parser> (fichier Parser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Parser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//-------------------------------------------- Constructeurs - destructeur



Parser::Parser ( )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au constructeur de <Parser>" << endl;
	#endif
} //----- Fin de Parser

Parser::~Parser ( )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au destructeur de <Parser>" << endl;
	#endif
}
//----- Fin de ~Parser