/*
 * File:    TLFormulaOR.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TL_FORMULAOR_INL_H_
#define _TL_FORMULAOR_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaOR::TLFormulaOR (      TLFormula* pLeftOp,
                                         TLFormula* pRightOp,
                                   const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    OR,
                    pRightOp,
                    UNDEFINED_LISTINDEX,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaOR::TLFormulaOR (const TLFormulaOR& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaOR::TLFormulaOR (const TLFormulaOR* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}

#endif // _TL_FORMULAOR_INL_H_
