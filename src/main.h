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
 *
 */
bool checkCmdLine( int argc, char ** argv, Args& args);

/*
 *
 */
 void mkTopTen( Parser& parser);

 /*
  *
  */
 void mkGraph( Parser& parser, const std::string& outputFileName );

#endif