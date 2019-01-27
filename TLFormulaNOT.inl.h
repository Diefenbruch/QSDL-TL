/*
 * File:    TLFormulaNOT.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULANOT_INL_H_
#define _TLFORMULANOT_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaNOT::TLFormulaNOT (      TLFormula* pRightOp,
                                           SCBoolean  dummy,
                                     const SCObject*  pFather)
:  TLFormulaUnary (NOT,
                   pRightOp,
                   UNDEFINED_LISTINDEX,
                   pFather)
{
  (void) dummy;
}


TLINLINE TLFormulaNOT::TLFormulaNOT (const TLFormulaNOT& phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


TLINLINE TLFormulaNOT::TLFormulaNOT (const TLFormulaNOT* phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


#endif // _TLFORMULANOT_INL_H_
