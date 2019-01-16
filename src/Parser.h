/*************************************************************************
                           Parser  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Parser> (fichier Parser.h) ----------------
#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
//------------------------------------------------------------------------
// Rôle de la classe <Parser>

//------------------------------------------------------------------------

class Parser
{
//----------------------------------------------------------------- PUBLIC

public:
	/*
	 *
	 */
	enum LineAttribute {
		IP_CLIENT = 0, 
		USER_LOGNAME,
		AUTHENTICATED, 
		DATETIME, 
		REQUEST, 
		STATUS, 
		DATA_SIZE, 
		REFERER, 
		CLIENT 
	};

//----------------------------------------------------- Méthodes publiques
	/*
	 *
	 */
	bool hasNextLine ( );

	/*
	 *
	 */
	void nextLine ( );

	/*
	 *
	 */
	std::string get ( LineAttribute lineAttr );

//-------------------------------------------- Constructeur - destructeur
	/*
	 *
	 */
	Parser ( std::string filePath );

	/*
	 *
	 */
	~Parser ( );

protected:


//----------------------------------------------------- Attributs protégés
	/*
	 *
	 */
	std::vector<std::string> lineData;

};

#endif // PARSER_H