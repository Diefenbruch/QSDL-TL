/*
 * File:    TLFormulaV_OPER.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAV_OPER_INL_H_
#define _TLFORMULAV_OPER_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaV_OPER::TLFormulaV_OPER (      TLFormula* pLeftOp,
                                                 TLFormula* pRightOp,
                                                 SCNatural  pAcceptSetNo,
                                           const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    V_OPER,
                    pRightOp,
                    pAcceptSetNo,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaV_OPER::TLFormulaV_OPER (const TLFormulaV_OPER& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaV_OPER::TLFormulaV_OPER (const TLFormulaV_OPER* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}

#endif // _TLFORMULAV_OPER_INL_H_
