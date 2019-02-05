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
#include <cstring>
#include <sstream>

using namespace std;
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

FileNotFoundError::FileNotFoundError(const char *filename)
{
	ostringstream sstr;
	sstr << "Cannot open file "
		<< filename
		<< ". Either you don't have the right or it does not exists";
	message = new char[sstr.str().size() + 1];
	strcpy(message, sstr.str().c_str());
}

FileNotFoundError::~FileNotFoundError()
{
	delete[] message;
}

const char* FileNotFoundError::what() const noexcept
{
	return message;
}

bool Parser::hasNextLine ( )
// Algorithme :
//
{
	bool res = true;
	char c;
	logFile.get(c);

	if(logFile.eof())
	{
		res =  false;
	}

	logFile.unget(); 

	return res;

} //Fin de hasNextLine


void Parser::nextLine ( )
// Algorithme :
//
{
	string line;
	string element;
	getline(logFile, line);

	lineData->clear();

	size_t a = 0;
	size_t b = 0;

	vector<string>::const_iterator del = delimiters.cbegin();

	//Extrait les differents éléments d'une ligne dans le vecteur lineData
	for (size_t i = 0; i < delimiters.size(); ++i)
	{
		b = line.find(*del, a);
		element = line.substr(a, b-a);
		lineData->push_back(element);
		a = b + (*del).size();

		del++;
	}

} //Fin de nextLine

const string* Parser::get ( enum LineAttribute lineAttr )
// Algorithme :
//
{
	if(lineData->empty())
		return nullptr;

	return &lineData->at(lineAttr);
} //Fin de get

//-------------------------------------------- Constructeurs - destructeur



Parser::Parser ( const string& filePath )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au constructeur de <Parser>" << endl;
	#endif
	
	lineData = new vector<string>();

	logFile.open(filePath);

	if(!logFile.good())
	{
		
		throw FileNotFoundError(filePath.c_str());
	}

} //----- Fin de Parser

Parser::~Parser ( )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au destructeur de <Parser>" << endl;
	#endif
	logFile.close();
	delete lineData;
}
//----- Fin de ~Parser 