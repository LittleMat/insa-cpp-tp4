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
class FileNotFoundError : public std::exception
{
public:
	FileNotFoundError(const char* filename);
	~FileNotFoundError();
	const char * what() const noexcept;

private:
	char* message;
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
		DATE,
		TIME, 
		METHOD,
		DOCUMENT,
		PROTOCOL,
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
	 * 	Vérifie si la ligne est correct par rapport aux paramètres.
	 */
	bool isLineGood();

	/*
	 *	Ajoute une extension au vecteur blacklist pour que le parser ne prenne pas
	 *  les pages ayant cette extension.
	 */
	void addBlacklist ( std::string extensionName);

	/*
	 *	Retourne l'attribut passé en paramètre de la ligne stocké dans linedata.
	 */
	const std::string* get ( LineAttribute lineAttr );

//-------------------------------------------- Constructeur - destructeur
	/*
	 *	Ouvre le fichier filePath et initialise les variables.
	 */
	explicit Parser ( const std::string& filePath, const std::string& h_Deb = "00", const std::string& h_Fin = "23"  );

	/*
	 *	Destructeur de Parser.
	 */
	~Parser ( );

protected:

	/*
	 *	Affiche le vecteur blacklist;
	 */
	void showBlackList();


	/*
	 *	Transforme un string contenant un temps en seconde.
	 */
	int TimeToSecond(const std::string& time);

	/*
	 *	Extrait l'extension d'une page.
	 */
	const std::string* extractExtension(const std::string& adresse) const;


//----------------------------------------------------- Attributs protégés

	std::vector<std::string> lineData; //Contient les différents éléments de la ligne lu.

	std::fstream logFile; //Gère la lecture dans le fichier ouvert.

	std::vector<std::string> const delimiters = {" ", " ", " [", ":", "] \"" , " ", " ", "\" "," ", " \"", "\" \"", "\""};
	// Vecteur des string de délimitation entre les différents éléments d'une ligne

	std::vector<std::string> blacklist; //Contien les extensions à ignorer.

	int hDeb;
	int hFin;
	bool eof;
};

#endif // PARSER_H