/*
 * File:    TLFormulaZ_OPER.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAZ_OPER_INL_H_
#define _TLFORMULAZ_OPER_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaZ_OPER::TLFormulaZ_OPER (      TLFormula* pLeftOp,
                                                 TLFormula* pRightOp,
                                                 SCNatural  pAcceptSetNo,
                                           const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    Z_OPER,
                    pRightOp,
                    pAcceptSetNo,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaZ_OPER::TLFormulaZ_OPER (const TLFormulaZ_OPER& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaZ_OPER::TLFormulaZ_OPER (const TLFormulaZ_OPER* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}

#endif // _TLFORMULAZ_OPER_INL_H_
