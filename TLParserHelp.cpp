/*
 * File:    TLParser.cpp
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */
 

#include <iostream>

//extern "C" {

/****************************************************************************
 *  Funktionen
 ****************************************************************************/

void yyerror(const char* s)
{
  std::cout << s << std::endl;
}

void yywarning(const char* s)
{
  std::cout << s << std::endl;
}

//}

