/*
 * File:    TLFormulaUnary.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAUNARY_INL_H_
#define _TLFORMULAUNARY_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaUnary::TLFormulaUnary (const TLLetter   pOp,
                                               TLFormula* right,
                                               SCNatural  acceptSet,
                                         const SCObject*  father)
: TLFormula (pOp,
             acceptSet,
             father),
  rightOperand (right)
{
  /* empty */
}

TLINLINE TLFormulaUnary::TLFormulaUnary (const TLFormulaUnary& phi)
:  TLFormula (phi),
   rightOperand (phi.rightOperand->GetCopy())
{
  /* empty */
}


TLINLINE TLFormulaUnary::TLFormulaUnary (const TLFormulaUnary* phi)
:  TLFormula (phi),
   rightOperand (phi->rightOperand->GetCopy())
{
  /* empty */
}


TLINLINE TLFormulaUnary::TLFormulaUnary (void)
{
  assert (false);
}


TLINLINE TLFormula* TLFormulaUnary::RightOperand (void) const
{
  return rightOperand;
}


TLINLINE void TLFormulaUnary::SetRightOperand (TLFormula* phi)
{
  if (rightOperand)
    delete rightOperand;
  rightOperand = phi;
}


TLINLINE SCStream& operator<< (SCStream&        out,
                              TLFormulaUnary& phi)
{
  return phi.Display(out);
}


TLINLINE SCStream& operator<< (SCStream&        out,
                              TLFormulaUnary* phi)
{
  return phi->Display(out);
}

#endif // _TLFORMULAUNARY_INL_H_
