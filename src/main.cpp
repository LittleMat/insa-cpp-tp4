/*************************************************************************
                           main  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
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

bool cmp (pair<string, int> const & a, pair<string, int> const & b)
{
	return (a.second > b.second);
}

int main(int argc, char ** argv)
// Algorithme :
//
{
    try
    {
        Parser parser("anonyme.log", "10:10:10", "11:00:00");
        parser.addBlacklist("css");
        parser.addBlacklist("jpeg");
        parser.addBlacklist("");

        //mkGraph(parser, "../weblogs.dot");
        mkTopTen(parser);
    }
    catch(FileNotFoundError& e)
    {
        cerr << e.what() << endl;
        return -1;
    }

	return 0;
} //----- Fin de main

bool checkCmdLine(char ** argv)
// Algorithme :
//
{

	return true;
} //----- Fin de checkCmdLine

void mkTopTen( Parser& p)
// Algorithme :
//
{
	map<string, int> connections;
	string adresseRequested;

	//Insère tous les éléments
	do
	{
		p.nextLine();

		if(p.isLineGood()) //Utile pour la dernière ligne si elle n'est pas bonne
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

	//Trie les éléments
	vector<pair<string, int>> connections_sorted;

	for(map<string, int>::const_iterator i = connections.begin(); i!=connections.end(); i ++){
		connections_sorted.emplace_back(*i);
	}

	sort(connections_sorted.begin(), connections_sorted.end(), cmp);
	

	vector<pair<string, int>>::const_iterator aff = connections_sorted.begin();

	//Moins de 10 logs
	if(connections_sorted.size() < 10){
		for(; aff != connections_sorted.end(); aff ++){
			cout << left << setw(50) << aff->first << " ( " << aff->second << " hits )" << endl;
		}
	}

	//Plus de 10 logs
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
				cout << "Plus de 10 éléments ont " << aff->second << " hits." <<endl;
			}
		}

	}

} //----- Fin de mkTopTen

void mkGraph( Parser& parser, const string& outputFileName )
// Algorithme :
//
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
} //----- Fin de mkGraph
