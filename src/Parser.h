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
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------
// Rôle de la classe <Parser>

//------------------------------------------------------------------------
struct FileNotFoundError : public std::exception
{
	const char * what() const noexcept;
};


class Parser
{
//----------------------------------------------------------------- PUBLIC

public:
	/*
	 * Enum contenant les différents attributs d'une ligne.
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
	 *	Retourne vrai si le fichier ouvert contient encore une ligne.
	 */
	bool hasNextLine ( );

	/*
	 * 	Retourne la prochaine ligne du fichier ouvert.
	 */
	void nextLine ( );

	/*
	 *	Retourne l'attribut passé en paramètre de la ligne stocké dans linedata
	 */
	std::string get ( LineAttribute lineAttr );

//-------------------------------------------- Constructeur - destructeur
	/*
	 *	Ouvre le fichier filePath et initialise les variables.
	 */
	Parser ( std::string filePath );

	/*
	 *	Destructeur de Parser.
	 */
	~Parser ( );

protected:


//----------------------------------------------------- Attributs protégés

	std::vector<std::string> *lineData; //Contient les différents éléments de la ligne lu.

	std::fstream logFile; //Gère la lecture dans le fichier ouvert.

	std::vector<std::string> const delimiters = {" ", " ", " [", "] \"" , "\" "," ", " \"", "\" \"", "\""};
	// Vecteur des string de délimitation entre les différents éléments d'une ligne
};

#endif // PARSER_H