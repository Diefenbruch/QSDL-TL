/*
 * File:    TLFormulaNEXTTIME.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULANEXTTIME_INL_H_
#define _TLFORMULANEXTTIME_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaNEXTTIME::TLFormulaNEXTTIME (      TLFormula* pRightOp,
                                                     SCBoolean  dummy,
                                               const SCObject*  pFather)
:  TLFormulaUnary (NEXTTIME,
                   pRightOp,
                   UNDEFINED_LISTINDEX,
                   pFather)
{
  (void) dummy;
}


TLINLINE TLFormulaNEXTTIME::TLFormulaNEXTTIME (const TLFormulaNEXTTIME& phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


TLINLINE TLFormulaNEXTTIME::TLFormulaNEXTTIME (const TLFormulaNEXTTIME* phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}

#endif // _TLFORMULANEXTTIME_INL_H_
