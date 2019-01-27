/*
 * File:    TLHelp.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLHELP_H_
#define _TLHELP_H_

#include "TL.h"

#define TLAssert(expr, text) (!(expr) ? FatalError (__FILE__, __LINE__, text) : (void) NULL)

void FatalError (const char* efile,
                       int   eline,
                 const char* what);

void Warning (const char* efile,
                    int   eline,
              const char* what);

SCBoolean FalsePropFunc (void);
SCBoolean TruePropFunc (void);

char* StrDup (const char*);

void ShowBits (class SCStream& out,
               const SCBitSet set);


#endif // _TLHELP_H_
