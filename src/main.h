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
 *  Construct the parser with the arguments structure.
 */
Parser * makeParser(Args * argum);

/*
 *
 */
bool checkCmdLine( int argc, char ** argv, Args& args);

/*
 *  Makes the top 10 most visited websites according to the arguments.
 */
 void mkTopTen( Parser& parser);

 /*
  *
  */
 void mkGraph( Parser& parser, const std::string& outputFileName );

#endif