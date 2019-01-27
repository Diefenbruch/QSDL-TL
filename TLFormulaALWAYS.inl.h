/*
 * File:    TLFormulaALWAYS.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAALWAYS_INL_H_
#define _TLFORMULAALWAYS_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaALWAYS::TLFormulaALWAYS (      TLFormula* pRightOp,
                                                 SCBoolean  pDummy,
                                                 SCNatural  pAcceptSetNo,
                                           const SCObject*  pFather)
:  TLFormulaUnary (ALWAYS,
                   pRightOp,
                   pAcceptSetNo,
                   pFather)
{
  (void) pDummy;                                  // Keep gcc happy...
}


TLINLINE TLFormulaALWAYS::TLFormulaALWAYS (const TLFormulaALWAYS& phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


TLINLINE TLFormulaALWAYS::TLFormulaALWAYS (const TLFormulaALWAYS* phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}

#endif // _TLFORMULAALWAYS_INL_H_
