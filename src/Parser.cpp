/*************************************************************************
                           Parser  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

//------------- Realisation of <Parser> (file Parser.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System include

//------------------------------------------------------ Personnal include
#include "Parser.h"
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Public methodes

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

} //End of hasNextLine


void Parser::nextLine ( )
{
	string line;
	string element;
	getline(logFile, line);

	lineData->clear();

	size_t a = 0;
	size_t b = 0;

	lineData->clear();

	vector<string>::const_iterator del = delimiters.cbegin();

	//Extract the different parts of the line and put it in the vector linedata
	for (size_t i = 0; i < delimiters.size(); ++i)
	{
		b = line.find(*del, a);
		element = line.substr(a, b-a);
		lineData->push_back(element);
		a = b + (*del).size();
		del++;
	}

	if( ! isLineGood() )
	{
		if( hasNextLine() ) //If the file still has lines, call nextLine.
		{
			nextLine();
		}
		else
		{
			eof = true;
		}
	}
} //End of nextLine

bool Parser::isLineGood()
{
	bool line_good = true;

	// Checks that the time is good according to the parameters sended to the constructor.
	if(hDeb!=0 && hFin != (23*60*60))
	{	
		int time = TimeToSecond((*get(TIME)).substr(0, 8));
		if( ! ( time >= hDeb && time < hFin ) ) 
		{
			line_good = false;
		}
	}

	// Checks that the extension of the line is not in the blacklist vector. Will not do this
	// if the line is already marked as false (because of the time).
	if(blacklist.size() != 0 && line_good)
	{
		const string * type = extractExtension(*get(DOCUMENT));
		
		if( find(blacklist.begin(), blacklist.end(), *type) != blacklist.end())
		{
			line_good = false;	
		}
		
		delete type;
	}
	return line_good;
}

void Parser::addBlacklist ( std::string extensionName )
{
	blacklist.push_back(extensionName);
} //End of addBlacklist

//----------------------------------------------------- Protected methodes


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
} //End of extractExtension

const string* Parser::get ( enum LineAttribute lineAttr )
{
	if(lineData->empty())
		return nullptr;

	return &lineData->at(lineAttr);
} //End of get

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
}//End of TimeToSecond


//-------------------------------------------- Constructors - destructor



Parser::Parser ( const string& filePath, const string& h_Deb, const string& h_Fin )
{
	#ifdef MAP
	    cerr << "Constructor of <Parser>" << endl;
	#endif
	
	lineData = new vector<string>();

	logFile.open(filePath);

	eof = false;

	if(!logFile.good())
	{
		throw FileNotFoundError(filePath.c_str());
	}

	hDeb = TimeToSecond(h_Deb);
	hFin = TimeToSecond(h_Fin);
} //----- End of Parser

Parser::~Parser ( )
{
	#ifdef MAP
	    cerr << "Destructor of <Parser>" << endl;
	#endif
	logFile.close();
	delete lineData;
}
//----- End of ~Parser 