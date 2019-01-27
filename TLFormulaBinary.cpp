/*
 * File:    TLFormulaBinary.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaBinary.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaBinary.inl.h"
#endif

TLFormulaBinary::~TLFormulaBinary (void)
{
  if (leftOperand)
    delete leftOperand;
  leftOperand = NULL;
}


TLArity TLFormulaBinary::Arity (void) const
{
  return TLBinary;
}


SCNatural TLFormulaBinary::NumOfSymbols (void) const
{
  return leftOperand->NumOfSymbols() +
         rightOperand->NumOfSymbols() + 1;
}


SCStream& TLFormulaBinary::Display (SCStream& out) const
{
  assert (rightOperand);
  assert (leftOperand);
  
  if (leftOperand->GetPrecedenceLevel() <= GetPrecedenceLevel())
  {
    out << "(";
    leftOperand->Display (out);
    out << ") ";
  }
  else                                            // Precedence is less, so binding
                                                  // of operator is clear.
  {
    leftOperand->Display (out);
    out << " ";
  }
  
  TLFormula::Display(out);
  
  if (rightOperand->GetPrecedenceLevel() <= GetPrecedenceLevel())
  {
    out << " (";
    rightOperand->Display (out);
    out << ")";
  }
  else                                            // Precedence is less, so binding
                                                  // of operator is clear.
  {
    out << " ";
    rightOperand->Display (out);
  }
  
  return out;
}


SCBoolean TLFormulaBinary::operator== (const TLFormula& phi) const
{
  TLFormulaBinary* tmpPhi = (TLFormulaBinary*) &phi;
  
  if (op != tmpPhi->op)
    return false;
  
  assert (leftOperand);
  assert (rightOperand);
  assert (tmpPhi->leftOperand);
  assert (tmpPhi->rightOperand);

  if (!(*leftOperand == *(tmpPhi->leftOperand)))
    return false;
  
  if (!(*rightOperand == *(tmpPhi->rightOperand)))
    return false;
  
  return true;
}


SCBoolean TLFormulaBinary::operator== (const TLFormula* phi) const
{
  return *this == *phi;
}


SCBoolean TLFormulaBinary::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormulaBinary::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}
