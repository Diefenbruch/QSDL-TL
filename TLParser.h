/*
 * File:    TLParser.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLPARSER_H_
#define _TLPARSER_H_

#include "TL.h"
 
SCBoolean InitializeParser (const char* source,   /* String to be parsed. */
                            SCName2PropFuncPtr* pName2Func,
                                                  /* Translation table names <->
                                                     proposition functions. */
                            SCNatural numOfElems);
                                                  /* Number of elements in
                                                     table */

SCBoolean CleanUpParser (void);                   /* Do any housecleaning that
                                                     might be necessary... */

SCPropFuncPtr Name2PropFuncPtr (char*);           /* Translation routine. */


class TLFormula* NewUnaryFormula (TLLetter,
                                  class TLFormula*);
                                                   /* Create a new unary formula
                                                      of the correct kind. */


class TLFormula* NewBinaryFormula (class TLFormula*,
                                   TLLetter,
                                   class TLFormula*);


class TLFormula* TLParse (void);                   /* Parser entry point. */

#endif /* _TLPARSER_H_ */
