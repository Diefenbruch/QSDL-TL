/*
 * File:    TLParserInterface.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLLEXER_H_
#define _TLLEXER_H_

SCBoolean SetLexInputString (const char *);       /* Set the input buffer of the
                                                     lexer to a given string. */

SCBoolean LexCleanUp(void);                       /* Do any clean up that might
                                                     be necessary. */

#endif // _TLLEXER_H_
