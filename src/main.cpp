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

using namespace std;

const string LOCAL_URL("intranet-if.insa-lyon.fr");

int main(int argc, char ** argv)
// Algorithme :
//
{
    mkGraph("../anonyme.log", "../weblogs.dot");
	return 0;
} //----- Fin de main

bool checkCmdLine(char ** argv)
// Algorithme :
//
{

	return true;
} //----- Fin de checkCmdLine

void mkTopTen( )
// Algorithme :
//
{

} //----- Fin de mkTopTen

void mkGraph( const string& inputFileName, const string& outputFileName )
// Algorithme :
//
{
    try
    {
        Parser parser(inputFileName);
        Graph<string> graph;

        while(parser.hasNextLine())
        {
            parser.nextLine();

            string referer = parser.get(Parser::REFERER);
            if(referer != "-") {
                // trouver l'indice de début du nom d'hôte dans l'url
                size_t pos1 = referer.find("//", 0) + 2; // +2 pour passer compter les //

                // trouver l'indice du début de la page dans l'url
                size_t pos2 = referer.find('/', pos1);

                //TODO maybe simplify really long urls (like google ones for example)

                // l'url contient une page (au moins un / à la fin)
                if(pos2 != string::npos) {
                    // le nom d'hôte correspond au nom d'hôte local
                    if(referer.substr(pos1, pos2 - pos1).rfind(LOCAL_URL) != string::npos) {
                        graph.add(referer.substr(pos2, referer.size()), parser.get(Parser::DOCUMENT));
                    }
                    else {
                        graph.add(referer, parser.get(Parser::DOCUMENT));
                    }
                }
                else {
                    graph.add(referer, parser.get(Parser::DOCUMENT));
                }
            }
        }

        ofstream outputFile(outputFileName);
        outputFile << graph << endl;
        outputFile.close();
    }
    catch(FileNotFoundError& e)
    {
        cerr << e.what() << endl;
    }
} //----- Fin de mkGraph
