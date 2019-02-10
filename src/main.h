/*************************************************************************
                           main  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include "Parser.h"
#include "Graph.h"

/*
 * Struct used to hold the program's command line arguments
 */
struct Args {
    std::string inputFileName = "";

    // -g
    bool makeGraph = false;
    std::string graphOutputFileName = "";

    // -e
    bool blacklistFiles = false;

    // -t
    bool filterHour = false;
    int hour = -1;
};

/*
 *
 */
int main( int argc, char ** argv );

/*
 * Construit le parser à partir de la structure arguments.
 */
Parser * makeParser(Args * argum);

/*
 * Parses the command line arguments and fills the given Args instance accordingly.
 * Returns true if the arguments were valid and false otherwise.
 * If false is returned, the given Args instance can't be considered valid and usable,
 * whatever the values the function may have put in it.
 */
bool checkCmdLine( int argc, char ** argv, Args& args);

/*
 * Fait le top 10 des sites les plus visités en prennant compte les arguments.
 */
 void mkTopTen( Parser& parser);

 /*
  * Builds a graph from the data returned by the given parser.
  * The graph is output to the given file in the dot format
  * (see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
  */
 void mkGraph( Parser& parser, const std::string& outputFileName );

#endif