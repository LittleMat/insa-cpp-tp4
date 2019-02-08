/*************************************************************************
                           main  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

#include "main.h"
#include "Parser.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

const string LOCAL_URL("intranet-if.insa-lyon.fr");
const string EXTENSIONS_BANNED("banned_extension.txt");

bool cmp (pair<string, int> const & a, pair<string, int> const & b)
{
	return (a.second > b.second);
}

int main(int argc, char ** argv)
{
	Args * a;
	Parser * p;
    try
    {
        a = new Args;
        a->inputFileName = "anonyme.log";
	    a->makeGraph = false;
	    a->graphOutputFileName = "";
	    a->blacklistFiles = true;
	    a->filterHour = true;
	    a-> hour = 10;


		p = makeParser(a);

		if(p != nullptr)
		{
			//mkGraph(parser, "../weblogs.dot");
			mkTopTen(*p);
		}
    }
    catch(FileNotFoundError& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    delete a;
    delete p;

	return 0;
} //----- End of main

Parser * makeParser(Args * argum)
{
	Parser * parser;
	if( ! argum -> filterHour )
	{
		parser = new Parser( argum ->inputFileName);
	}
	else
	{
		parser = new Parser( argum ->inputFileName, to_string(argum->hour), to_string(argum->hour+1));
	}

	if ( argum->blacklistFiles ){
	    try
	    {
			fstream extension;
			string line;
			extension.open(EXTENSIONS_BANNED);

			bool haveExtensions = false;
			while( ! extension.eof() )
			{
				getline(extension, line);
				if( line.size( ) != 0 )
				{
					haveExtensions = true;
					parser -> addBlacklist(line);
				}
			}

			if( ! haveExtensions )
			{
				cerr << "The file banned_extension.txt does not contain any extension to ban" << endl;
			}

	    }
	    catch(FileNotFoundError& e)
	    {
	        cerr << e.what() << endl;
	        return nullptr;
	    }
	}

	return parser;
}

bool checkCmdLine(char ** argv)
{

	return true;
} //----- End of checkCmdLine

void mkTopTen( Parser& p)
{
	map<string, int> connections;
	string adresseRequested;

	//Inserts every elements
	do
	{
		p.nextLine();

		if(p.isLineGood()) //Usefull for the last line, if it's not a good one.
		{
			adresseRequested = *(p.get(Parser::DOCUMENT));
			if(connections.count(adresseRequested) > 0)
			{
				connections[adresseRequested] ++;
			}
			else
			{
				connections[adresseRequested] = 1;
			}
		}
		
	
	} while(p.hasNextLine());

	//Sort the elements
	vector<pair<string, int>> connections_sorted;

	for(map<string, int>::const_iterator i = connections.begin(); i!=connections.end(); i ++){
		connections_sorted.emplace_back(*i);
	}

	sort(connections_sorted.begin(), connections_sorted.end(), cmp);
	

	vector<pair<string, int>>::const_iterator aff = connections_sorted.begin();

	//If we have less than ten elements
	if(connections_sorted.size() < 10){
		for(; aff != connections_sorted.end(); aff ++){
			cout << left << setw(50) << aff->first << " ( " << aff->second << " hits )" << endl;
		}
	}

	//More than 10 elements
	else{
		int cpt = 0;
		int max = aff->second;
		for(size_t i = 0; i<10; i++, aff ++){
			if(aff->second == max)
			{
				cpt++;
			}

			cout << left << setw(50) << aff->first << " ( " << aff->second << " hits )" << endl;

			if(cpt == 10)
			{
				cout << "More than 10 elements have " << aff->second << " hits." <<endl;
			}
		}

	}

} //----- End of mkTopTen

void mkGraph( Parser& parser, const string& outputFileName )
{
    Graph<string> graph;

    while(parser.hasNextLine())
    {
        parser.nextLine();

        const string& referer = *parser.get(Parser::REFERER);
        if(referer != "-") {
            // trouver l'indice de début du nom d'hôte dans l'url
            size_t pos1 = referer.find("//", 0) + 2; // +2 pour passer compter les //

            // trouver l'indice du début de la page dans l'url
            size_t pos2 = referer.find('/', pos1);

            //hTODO maybe simplify really long urls (like google ones for example)

            // l'url contient une page (au moins un / à la fin)
            if(pos2 != string::npos) {
                // le nom d'hôte correspond au nom d'hôte local
                if(referer.substr(pos1, pos2 - pos1).rfind(LOCAL_URL) != string::npos) {
                    graph.add(referer.substr(pos2, referer.size()), *parser.get(Parser::DOCUMENT));
                }
                else {
                    graph.add(referer, *parser.get(Parser::DOCUMENT));
                }
            }
            else {
                graph.add(referer, *parser.get(Parser::DOCUMENT));
            }
        }
    }

    ofstream outputFile(outputFileName);
    outputFile << graph << endl;
    outputFile.close();
} //----- End of mkGraph
