/*
 * File:    TLFormulaBinary.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULABINARY_INL_H_
#define _TLFORMULABINARY_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaBinary::TLFormulaBinary (      TLFormula* pLeft,
                                                 TLLetter   pOp,
                                                 TLFormula* pRight,
                                                 SCNatural  acceptSet,
                                           const SCObject*  pFather)
: TLFormulaUnary (pOp,
                  pRight,
                  acceptSet,
                  pFather),
  leftOperand (pLeft)
{
  /* empty */
}


TLINLINE TLFormulaBinary::TLFormulaBinary (const TLFormulaBinary& phi)
:  TLFormulaUnary (phi),
   leftOperand (phi.leftOperand->GetCopy())
{
  /* empty */
}


TLINLINE TLFormulaBinary::TLFormulaBinary (const TLFormulaBinary* phi)
:  TLFormulaUnary (phi),
   leftOperand (phi->leftOperand->GetCopy())
{
  /* empty */
}



TLINLINE TLFormula* TLFormulaBinary::LeftOperand (void) const
{
  return leftOperand;
}


TLINLINE void TLFormulaBinary::SetLeftOperand (TLFormula* phi)
{
  if (leftOperand)
    delete leftOperand;
  leftOperand = phi;
}


TLINLINE SCStream& operator<< (      SCStream&         out,
                              const TLFormulaBinary& phi)
{
  return phi.Display(out);
}


TLINLINE SCStream& operator<< (      SCStream& out,
                              const TLFormulaUnary* phi)
{
  return phi->Display(out);
}

#endif // _TLFORMULABINARY_INL_H_
