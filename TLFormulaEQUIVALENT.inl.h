/*
 * File:    TLFormulaEQUIVALENT.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAEQUIVALENT_INL_H_
#define _TLFORMULAEQUIVALENT_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaEQUIVALENT::TLFormulaEQUIVALENT (      TLFormula* pLeftOp,
                                                         TLFormula* pRightOp,
                                                   const SCObject* pFather)
:  TLFormulaBinary (pLeftOp,
                    EQUIVALENT,
                    pRightOp,
                    UNDEFINED_LISTINDEX,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaEQUIVALENT::TLFormulaEQUIVALENT (const TLFormulaEQUIVALENT& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaEQUIVALENT::TLFormulaEQUIVALENT (const TLFormulaEQUIVALENT* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


#endif // _TLFORMULAEQUIVALENT_INL_H_
