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

struct Args {
    std::string inputFileName;

    // -g
    bool makeGraph = false;
    std::string graphOutputFileName;

    // -e
    bool blacklistFiles = false;

    // -t
    bool filterHour = false;
    int hour;
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
 *
 */
bool checkCmdLine( char ** argv );

/*
 * Fait le top 10 des sites les plus visités en prennant compte les arguments.
 */
 void mkTopTen( Parser& parser);

 /*
  *
  */
 void mkGraph( Parser& parser, const std::string& outputFileName );

#endif