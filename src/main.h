/*************************************************************************
                           main  -  description
                             -------------------
    beginning            : 16/01
    copyright            : (C) 2019 by LEHOUX Pacôme, MONTGOMERY Mathieu et ZHANG Tianyu
    e-mail               : pacome.lehoux@insa-lyon.fr, mathieu.montgomery@insa-lyon.fr, tianyu.zhang@insa-lyon.fr
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
struct Args
{
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
 * main function
 */
int main ( int argc, char ** argv );

/*
 * Construct the parser with the arguments structure.
 */
Parser * makeParser ( Args * argum );

/*
 * Parses the command line arguments and fills the given Args instance accordingly.
 * Returns true if the arguments were valid and false otherwise.
 * If false is returned, the given Args instance can't be considered valid and usable,
 * whatever the values the function may have put in it.
 */
bool checkCmdLine ( int argc, char ** argv, Args & args );

/*
 *  Makes the top 10 most visited websites according to the arguments.
 */
 void mkTopTen ( Parser & parser );

/*
  * Builds a graph from the data returned by the given parser.
  * The graph is output to the given file in the dot format
  * (see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
  */
bool mkGraph ( Parser & parser, const std::string & outputFileName );

#endif
