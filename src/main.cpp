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
#include <string.h>
#include <string>

using namespace std;

const string LOCAL_URL("intranet-if.insa-lyon.fr");

constexpr int ARGS_NUM = 3;
const char* VALID_ARGS[ARGS_NUM] = { "-g", "-e", "-t" };

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

bool checkCmdLine(int argc, char ** argv, Args& args)
// Algorithme :
//
{
    args = Args();

	int gotArgs = 0; // flags to remember which args where found

	// check that all given arguments starting with '-' exist and that there's at most 1 of each
	for(int i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			bool argExist = false;
			for(int j = 0; j < ARGS_NUM && !argExist; ++j)
			{
				if(strcmp(argv[i], VALID_ARGS[j]) == 0) {
					if((gotArgs >> j) == 1) {
						cout << "Got argument " << argv[i] << " several times" << endl;
						return false;
					}
					argExist = true;
					gotArgs |= (1 << j);
				}
			}
			if(!argExist)
			{
				cout << "Unknown argument : " << argv[i] << endl;
				return false;
			}
		}
	}

	// display usage message if no args, or last arg is not file name,
	// or 2 args or more and 1st arg is file name
	if (argc <= 1 || (argv[argc - 1][0] == '-') || (argc > 2 && argv[1][0] != '-'))
	{
		cout << "Usage : analog [options] <input-file>\n\n"
				"\t<input-file>      : path to the log file to use as input\n\n"
				"\tAvailable options :\n\n"
				"\t\t-g [output-file] : specifies that a directed graph representation of the log file\n"
				"\t\t\tshould be built and outputed to [output-file]. Vertices in the graph represent the webpages\n"
				"\t\t\tand arcs represent that a request occurred from a page to get another page. The actual number\n"
				"\t\t\tof request that occurred is represented as a label on the associated arc.\n"
				"\t\t\t[output-file] defaults to \"out.dot\"\n\n"
				"\t\t-e : exclude files based on their ending. Blacklisted file endings are stored in the x file.\n\n" //TODO put name of blacklist file
				"\t\t-t <hour> : only consider requests that occurred between <hour> (included)\n"
				"\t\t\tand <hour> + 1 (excluded). <hour> must be a number between 0 and 23."
			 << endl; //TODO put some tty magic in usage message (colors, etc)
		return false;
	}

	for(int i = 1; i < argc - 1; ++i)
	{
		char* arg = argv[i];

        if(strcmp(arg, "-g") == 0)
        {
            bool defaultValue = false;
            args.makeGraph = true;
            if (i + 1 < argc - 1) {
                ++i;
                arg = argv[i];

                if (arg[0] != '-') {
                    args.graphOutputFileName = string(arg);
                } else {
                    defaultValue = true;
                }
            }
            else {
                defaultValue = true;
            }

            if(defaultValue)
                args.graphOutputFileName = string("out.dot");
        }

        if(strcmp(arg, "-t") == 0)
        {
            args.filterHour = true;
            bool gotBadT = false;
            if(i + 1 < argc - 1) {
                ++i;
                arg = argv[i];

                if(arg[0] != '-') {
                    size_t argLen = strlen(arg);
                    if (argLen <= 2) {
                        for (int j = 0; j < argLen && !gotBadT; ++j) {
                            if (arg[0] <= 48 || arg[0] >= 57) {
                                gotBadT = true;
                            }
                        }
                        if (!gotBadT) {
                            args.filterHour = true;
                            args.hour = atoi(arg);
                        }
                    } else {
                        gotBadT = true;
                    }
                }
                else {
                    gotBadT = true;
                }
            }
            else {
                gotBadT = true;
            }

            // got bad or no number after -t
            if(gotBadT) {
                cout << "Argument -t expects a number between 0 and 23" << endl;
                return false;
            }
        }

        if(strcmp(arg, "-e") == 0)
        {
            args.blacklistFiles = true;
        }
	}

	args.inputFileName = argv[argc - 1];

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
