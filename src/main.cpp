/*************************************************************************
                           main  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
*************************************************************************/

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string.h>
#include <string>
#include <unistd.h>

#include "main.h"
#include "Graph.h"
#include "Parser.h"

using namespace std;

const string USAGE_MESSAGE(
        "Usage : analog [options] <input-file>\n\n"
        "\t<input-file>      : path to the log file to use as input\n\n"
        "\tAvailable options :\n\n"
        "\t\t-g <output-file> : specifies that a directed graph representation of the log file\n"
        "\t\t\tshould be built and output to <output-file>. Vertices in the graph represent the webpages\n"
        "\t\t\tand arcs represent that a request occurred from a page to get another page. The actual number\n"
        "\t\t\tof request that occurred is represented as a label on the associated arc.\n\n"
        "\t\t-e : exclude files based on their ending. Blacklisted file endings are stored in banned_extension.txt.\n\n"
        "\t\t-t <hour> : only consider requests that occurred between <hour> (included)\n"
        "\t\t\tand <hour> + 1 (excluded). <hour> must be a number between 0 and 23.");
const string LOCAL_URL("intranet-if");
const string EXTENSIONS_BANNED("banned_extension.txt");

int main(int argc, char ** argv)
{
    opterr = 0;
    Args args;

    if(checkCmdLine(argc, argv, args))
    {
        Parser* p;
        try
        {
		    p = makeParser(&args);

		    if(p != nullptr)
		    {
		        if(args.makeGraph)
			        mkGraph(*p, args.graphOutputFileName);
		        else
			        mkTopTen(*p);
            }
		    else
            {
		        cerr << "Abort" << endl;
		        return -1;
            }

		    delete p;
            return 0;
        }
        catch (FileNotFoundError &e)
        {
            cerr << e.what() << endl;
            return -1;
        }
    }
    
	return -1;
} //----- End of main

Parser * makeParser(Args * argum)
{
	Parser * parser = nullptr;
	if( ! argum -> filterHour )
	{
		parser = new Parser( argum ->inputFileName);
	}
	else
	{
		parser = new Parser( argum ->inputFileName, to_string(argum->hour), to_string(argum->hour+1));
	}

	if ( argum->blacklistFiles )
	{
        fstream extension(EXTENSIONS_BANNED);
        string line;

        if( extension.fail() ) {
            cerr << "Can't open banned_extension.txt" << endl;
            return nullptr;
        }

        while( extension.good() )
        {
            getline(extension, line);
            if( line.size( ) != 0 )
            {
                parser -> addBlacklist(line);
            }
        }
	}

	return parser;
}

bool checkCmdLine(int argc, char ** argv, Args& args)
{
    args = Args();

    if(argc <= 1)
    {
        cout << USAGE_MESSAGE << endl;
        return false;
    }

    int c;
    while((c = getopt(argc, argv, "g:et:")) != -1)
    {
        switch(c)
        {
            case 'g':
            {
                args.makeGraph = true;
                args.graphOutputFileName = string(optarg);
                break;
            }
            case 'e':
                args.blacklistFiles = true;
                break;
            case 't':
            {
                args.filterHour = true;
                bool gotBadT = false;
                size_t argLen = strlen(optarg);
                if (argLen <= 2)
                {
                    for (int j = 0; j < argLen && !gotBadT; ++j)
                    {
                        if (optarg[0] <= 48 || optarg[0] >= 57)
                            gotBadT = true;
                    }
                    if (!gotBadT)
                    {
                        args.filterHour = true;
                        args.hour = atoi(optarg);
                        if (args.hour < 0 || args.hour > 23)
                            gotBadT = true;
                    }
                }
                else
                {
                    gotBadT = true;
                }
                // got bad or no number after -t
                if (gotBadT)
                {
                    cout << "Argument -t expects a number between 0 and 23" << endl;
                    return false;
                }
                break;
            }
            case '?':
                if(optopt == 't')
                {
                    cout << "Argument -t expects a number between 0 and 23" << endl;
                    return false;
                }
                if(optopt == 'g')
                {
                    cout << "Argument -g expects a file name" << endl;
                }
                else
                {
                    if(isprint(c))
                        cout << "Unknown argument : -" << char(optopt) << endl;
                    else
                        cout << hex << "Unknown argument character : \\x" << optopt << dec << endl;
                    return false;
                }
            default:
                cout << "An error occurred while parsing command line arguments" << endl;
                return false;
        }
    }

    if(optind < argc)
        args.inputFileName = argv[optind];
    else
    {
        cout << USAGE_MESSAGE << endl;
        return false;
    }

	return true;
} //----- End of checkCmdLine

static bool cmp (pair<string, int> const & a, pair<string, int> const & b)
{
    return a.second > b.second;
}

void mkTopTen( Parser& p )
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

	for(map<string, int>::const_iterator i = connections.begin(); i!=connections.end(); i ++)
	{
		connections_sorted.emplace_back(*i);
	}

	sort(connections_sorted.begin(), connections_sorted.end(), cmp);
	

	vector<pair<string, int>>::const_iterator aff = connections_sorted.begin();

	//We have less than ten elements
	if(connections_sorted.size() < 10){
		for(; aff != connections_sorted.end(); aff ++){
			cout << left << setw(50) << aff->first << " ( " << aff->second << " hits )" << endl;
		}
	}

	//More than 10 elements
	else{
		int cpt = 0;
		int max = aff->second;
		for(size_t i = 0; i<10; i++, aff ++)
		{
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

bool mkGraph( Parser& parser, const string& outputFileName )
{
    ofstream outputFile(outputFileName);

    if(outputFile.fail())
    {
        cerr << "Can't open " << outputFileName << endl;
        return false;
    }

    Graph<string> graph;

    while(parser.hasNextLine())
    {
        parser.nextLine();

        const string& referer = *parser.get(Parser::REFERER);
        if(referer != "-")
        {
            // trouver l'indice de début du nom d'hôte dans l'url
            size_t pos1 = referer.find("//", 0) + 2; // +2 pour passer compter les //

            // trouver l'indice du début de la page dans l'url
            size_t pos2 = referer.find('/', pos1);

            //TODO maybe simplify really long urls (like google ones for example)

            // l'url contient une page (au moins un / à la fin)
            if(pos2 != string::npos)
            {
                // le nom d'hôte correspond au nom d'hôte local
                if(referer.substr(pos1, pos2 - pos1).find(LOCAL_URL) == 0)
                {
                    graph.add(referer.substr(pos2, referer.size()), *parser.get(Parser::DOCUMENT));
                }
                else
                {
                    graph.add(referer, *parser.get(Parser::DOCUMENT));
                }
            }
            else
            {
                graph.add(referer, *parser.get(Parser::DOCUMENT));
            }
        }
    }

    outputFile << graph << endl;
    outputFile.close();

    return true;
} //----- End of mkGraph
