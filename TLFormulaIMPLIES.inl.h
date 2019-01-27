/*
 * File:    TLFormulaIMPLIES.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAIMPLIES_INL_H_
#define _TLFORMULAIMPLIES_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaIMPLIES::TLFormulaIMPLIES (      TLFormula* pLeftOp,
                                                   TLFormula* pRightOp,
                                             const SCObject* pFather)
:  TLFormulaBinary (pLeftOp,
                    IMPLIES,
                    pRightOp,
                    UNDEFINED_LISTINDEX,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaIMPLIES::TLFormulaIMPLIES (const TLFormulaIMPLIES& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaIMPLIES::TLFormulaIMPLIES (const TLFormulaIMPLIES* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


#endif // _TLFORMULAIMPLIES_INL_H_
