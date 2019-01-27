/*
 * File:    TLFormulaEVENTUALLY.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAEVENTUALLY_INL_H_
#define _TLFORMULAEVENTUALLY_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaEVENTUALLY::TLFormulaEVENTUALLY (      TLFormula* pRightOp,
                                                         SCBoolean  dummy,
                                                         SCNatural  pAcceptSetNo,
                                                   const SCObject*  pFather)
:  TLFormulaUnary (EVENTUALLY,
                   pRightOp,
                   pAcceptSetNo,
                   pFather)
{
  (void) dummy;
}


TLINLINE TLFormulaEVENTUALLY::TLFormulaEVENTUALLY (const TLFormulaEVENTUALLY& phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


TLINLINE TLFormulaEVENTUALLY::TLFormulaEVENTUALLY (const TLFormulaEVENTUALLY* phi)
:  TLFormulaUnary (phi)
{
  /* empty */
}


#endif // _TLFORMULAEVENTUALLY_INL_H_
