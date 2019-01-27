/*
 * File:    TLFormulaUNTIL.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAUNTIL_INL_H_
#define _TLFORMULAUNTIL_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaUNTIL::TLFormulaUNTIL (      TLFormula* pLeftOp,
                                               TLFormula* pRightOp,
                                               SCNatural  pAcceptSetNo,
                                         const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    UNTIL,
                    pRightOp,
                    pAcceptSetNo,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaUNTIL::TLFormulaUNTIL (const TLFormulaUNTIL& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaUNTIL::TLFormulaUNTIL (const TLFormulaUNTIL* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}

#endif // _TLFORMULAUNTIL_INL_H_
