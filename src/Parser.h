/*************************************************************************
                           Parser  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//---------- Interface of <Parser> (file Parser.h) ----------------
#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------
// Rôle de la classe <Parser>
// This class will open a file passed to the constructor and each time the method nextLine
// is called, it will read a new line from the file and break it into a vector of information.
// all the different information from a line are accessible with a get method, and it is possible
// to restrain the data that is read with some parameters (currently in between hours and extensions)
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
	 * Enum containing the different attributes of a line.
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

//----------------------------------------------------- Public methods
	/*
	 *	Return true if the opened file still has a line.
	 */
	bool hasNextLine ( );

	/*
	 * 	Return the next line of the opened file.
	 */
	void nextLine ( );

	/*
	 * 	Check if the line is correct (according to the parameters, hours and extensions).
	 */
	bool isLineGood();

	/*
	 *	Adds an extension to the blacklist vector so the parser would skip those lines.
	 */
	void addBlacklist ( std::string extensionName);

	/*
	 *	Returns the part of the line that is currently read corresponding to what is passed 
	 *  to the method.
	 */
	const std::string* get ( LineAttribute lineAttr );

//-------------------------------------------- Constructeur - destructeur
	/*
	 *	Opens filePath and initialize variables.
	 */
	explicit Parser ( const std::string& filePath, const std::string& h_Deb = "00", const std::string& h_Fin = "23"  );

	/*
	 *	Destructor of Parser.
	 */
	~Parser ( );

protected:

	/*
	 *	Display the blacklist vector.
	 */
	void showBlackList();


	/*
	 *	Transforms a string containing a time in an int. It must be in the form hh:mm:ss or hh.
	 */
	int TimeToSecond(const std::string& time);

	/*
	 *	Extract the extension of a page.
	 */
	const std::string* extractExtension(const std::string& adresse) const;


//----------------------------------------------------- Protected attributes

	std::vector<std::string> lineData; //Contains the different part of a line that is currently read.

	std::fstream logFile; //Manages the file where the data is read.

	std::vector<std::string> const delimiters = {" ", " ", " [", ":", "] \"" , " ", " ", "\" "," ", " \"", "\" \"", "\""};
	// Vector that contains the delimitation between the different pieces of information of a line.

	std::vector<std::string> blacklist; // Contains the extensions to ignore.

	int hDeb;
	int hFin;
	bool eof;
};

#endif // PARSER_H