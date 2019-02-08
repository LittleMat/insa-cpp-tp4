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
	if( eof )
	{
		return false;
	}
	
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

	lineData.clear();

	size_t a = 0;
	size_t b = 0;

	lineData.clear();

	vector<string>::const_iterator del = delimiters.cbegin();

	//Extrait les differents éléments d'une ligne dans le vecteur lineData
	for (size_t i = 0; i < delimiters.size(); ++i)
	{
		b = line.find(*del, a);
		element = line.substr(a, b-a);
		lineData.push_back(element);
		a = b + (*del).size();
		del++;
	}

	if( ! isLineGood() )
	{
		if( hasNextLine() ) //S'il reste des lignes, on passe à la suivante.
		{
			nextLine();
		}
		else //Sinon, on passe manuellement le eof à true
		{
			eof = true;
		}
	}
} //Fin de nextLine

bool Parser::isLineGood()
{
	bool line_good = true;

	// Vérifie que l'heure soit bien entre les bornes, si elles sont différentes
	// des valeurs de base
	if(hDeb!=0 && hFin != (23*60*60 + 59*60 + 59))
	{	
		int time = TimeToSecond((*get(TIME)).substr(0, 8));
		if( ! ( time >= hDeb && time < hFin ) ) 
		{
			line_good = false;
		}
	}

	// Vérifie si le type de la page est différent de celles qui sont blacklistées
	// si des extensions ont été blacklisté et si la ligne n'est pas déjà rejetée.
	if(blacklist.size() != 0 && line_good)
	{
		vector<string>::const_iterator ci;

		for(ci = blacklist.begin(); ci != blacklist.end(); ++ci)
		{
			const string * type = extractExtension(*get(DOCUMENT));
			if( ! type->compare (*ci))
			{
				line_good = false;
			}
			delete type;
		}
	}
	return line_good;
}

void Parser::addBlacklist ( std::string extensionName )
{
	blacklist.push_back(extensionName);
} //Fin de addBlacklist

void Parser::showBlackList()
{
	vector<string>::const_iterator ci;
	for(ci = blacklist.begin(); ci != blacklist.end(); ci++)
	{
		cout << *ci << endl;
	}
}

const string* Parser::extractExtension(const string& adresse) const
{
	int firstPos = adresse.find(".", 0);
	string *res = new string(adresse.substr(firstPos+1, adresse.size() - firstPos));
	return res;
} //Fin de extractExtension

const string* Parser::get ( enum LineAttribute lineAttr )
// Algorithme :
//
{
	if(lineData.empty())
		return nullptr;

	return &lineData.at(lineAttr);
} //Fin de get

int Parser::TimeToSecond(const std::string& time)
{

	if(time.size() > 2)
	{
		return stoi(time.substr(0, 2)) * 3600+ stoi(time.substr(3, 2)) * 60 + stoi(time.substr(6, 2));
	}
	else
	{
		return stoi(time) * 3600;
	}
}//Fin de TimeToSecond


//-------------------------------------------- Constructeurs - destructeur



Parser::Parser ( const string& filePath, const string& h_Deb, const string& h_Fin )
// Algorithme :
//
{
	#ifdef MAP
	    cerr << "Appel au constructeur de <Parser>" << endl;
	#endif
	
	lineData = vector<string>();

	logFile.open(filePath);

	eof = false;

	if(!logFile.good())
	{
		throw FileNotFoundError(filePath.c_str());
	}

	hDeb = TimeToSecond(h_Deb);
	hFin = TimeToSecond(h_Fin);
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