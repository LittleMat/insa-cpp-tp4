/*************************************************************************
                           main  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

#include "main.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <string.h>


int main(int argc, char ** argv)
// Algorithme :
//
{
	checkCmdLine(argc, argv);
	return 0;
} //----- Fin de main

bool checkCmdLine(int argc, char ** argv)
// Algorithme :
//
{
	cout << argc << endl;
   if(argc<1)
   {
   	cout<<"Il faut mettre quelquechose" <<endl;
   }
   if(strcmp(argv[0],"./bin/analog")==0 && argc ==1) 
		{
			cout<<"Il faut mettre un nom de fichier"<< endl;
			return false;
		}
		else if(argc ==1)
		{
			cout << "Il faut mettre une valide argument" <<endl;
			return false;
		}

   for(int i=0; i<argc; i++)
	{
		
		if(argv[i][0] == '-')
		{
			cout << argv[i][1]<<endl;

			if(argv[i][1] != 't' && argv[i][1] != 'g' && argv[i][1] != 'e')
			{
				cout << "Il faut mettre une valide argument apres le tiret" << endl;
				return false;
			}
		}
		if(argv[i][0] == '-' && argv[i][1] == 't' && argc > i)
		{
			for(int j = 48; j<=57; j++)
			{
				if(argv[i+1][0]!=j) //s'il est un int il doit avoir un ASCII valeur entre 48 et 57
				{
					cout<< "Il faut mettre une int apres -t heure" <<endl;
					return false;
				}
			}
			if(argc==i)
			{
				cout << "Il faut mettre quelquechose apres -t" <<endl;
				return false;
			}
		}

	}
	return true;
 }
	
 //----- Fin de checkCmdLine

void mkTopTen( )
// Algorithme :
//
{

} //----- Fin de mkTopTen

void mkGraph( )
// Algorithme :
//
{

} //----- Fin de mkGraph
