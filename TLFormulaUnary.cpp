/*
 * File:    TLFormulaUnary.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaUnary.h"

#if _TL_INLINING_ == 0
#include "TLFormulaUnary.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaUnary::~TLFormulaUnary (void)
{
  if (rightOperand)
    delete rightOperand;
  rightOperand = NULL;
}


TLArity TLFormulaUnary::Arity (void) const
{
  return TLUnary;
}


SCNatural TLFormulaUnary::NumOfSymbols (void) const
{
  return rightOperand->NumOfSymbols() + 1;
}


SCStream& TLFormulaUnary::Display (SCStream& out) const
{
  assert (rightOperand);
  
  if (rightOperand->Arity() == TLBinary)          // It is a binary which always has
                                                  // lower precedence.
  {
    TLFormula::Display(out);
    out << " (" << rightOperand << ")";
  }
  else
  {
    TLFormula::Display(out);
    out << " " << rightOperand;
  }
  
  return out;
}


SCBoolean TLFormulaUnary::operator== (const TLFormula& phi) const
{
  TLFormulaUnary* tmpPhi = (TLFormulaUnary*) &phi;
  
  if (op != tmpPhi->op)
    return false;

  assert (rightOperand);
  assert (tmpPhi->rightOperand);

  return (*rightOperand == *(tmpPhi->rightOperand));
}


SCBoolean TLFormulaUnary::operator== (const TLFormula* phi) const
{
  return *this == *phi;
}


SCBoolean TLFormulaUnary::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormulaUnary::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}
