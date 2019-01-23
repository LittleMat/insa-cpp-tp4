/*************************************************************************
                           main  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

#include "main.h"
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;


bool cmp (pair<string, int> const & a, pair<string, int> const & b)
{
	return (a.second > b.second);
}

string factorise(string info)
{
	int a,b;
	a = info.find(" ", 0);
	b = info.find(" ", a+1);
	string res = info.substr(a, b-a);
	return res;
}


int main(int argc, char ** argv)
// Algorithme :
//
{


	mkTopTen( argv [1] );


	return 0;
} //----- Fin de main

bool checkCmdLine(char ** argv)
// Algorithme :
//
{

	return true;
} //----- Fin de checkCmdLine

void mkTopTen( string filename )
// Algorithme :
//
{
	map<string, int> connections;
	Parser * p = new Parser(filename);
	string adresseRequested;

	//Insère tous les éléments
	do
	{
		p->nextLine();
		adresseRequested = p->get(Parser::REQUEST);
		if(connections.count(adresseRequested) > 0)
		{
			connections[adresseRequested] ++;
		}
		else
		{
			connections[adresseRequested] = 1;
		}
	} while(p->hasNextLine());

	delete p;

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
			cout << left << setw(50) << factorise(aff->first) << " ( " << aff->second << " hits )" << endl;
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

			cout << left << setw(50) << factorise(aff->first) << " ( " << aff->second << " hits )" << endl;

			if(cpt == 10)
			{
				cout << "Plus de 10 éléments ont " << aff->second << " hits." <<endl;
			}
		}

	}

} //----- Fin de mkTopTen

void mkGraph( )
// Algorithme :
//
{

} //----- Fin de mkGraph
