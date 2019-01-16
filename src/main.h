/*************************************************************************
                           main  -  description
                             -------------------
    début                : 16/01
    copyright            : (C) 2019 par LEHOUX Pacôme et MONTGOMERY Mathieu
    e-mail               : pacome.lehoux@insa-lyon.fr et mathieu.montgomery@insa-lyon.fr
*************************************************************************/

#ifndef MAIN_H
#define MAIN_H

#include "Parser.h"
#include "Graph.h"

/*
 *
 */
int main( int argc, char ** argv );

/*
 *
 */
bool checkCmdLine( char ** argv );

/*
 *
 */
 void mkTopTen( );

 /*
  *
  */
 void mkGraph( );