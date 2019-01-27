/*
 * File:    TLParser.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLPARSERHELP_H_
#define _TLPARSERHELP_H_

int  yylex (void);                                /* Lexer entry point. */

int yyparse (void);                               /* Parser entry point. */

void yyerror (const char*);                             /* Parser / scanner error
                                                     reporting routine. */

#endif /* _TLPARSERHELP_H_ */
