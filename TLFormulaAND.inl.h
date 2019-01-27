/*
 * File:    TLFormulaAND.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAAND_INL_H_
#define _TLFORMULAAND_INL_H_

#include "TLHelp.h"


TLINLINE TLFormulaAND::TLFormulaAND (      TLFormula* pLeftOp,
                                           TLFormula* pRightOp,
                                           SCNatural  pAcceptSetNo,
                                     const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    AND,
                    pRightOp,
                    pAcceptSetNo,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaAND::TLFormulaAND (const TLFormulaAND& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaAND::TLFormulaAND (const TLFormulaAND* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}

#endif // _TLFORMULAAND_INL_H_
