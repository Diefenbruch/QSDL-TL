/*
 * File:    TLFormulaAND.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "SCL/SCStream.h"

#include "TLFormulaAND.h"
#include "TLFormulaOR.h"
#include "TLFormulaNOT.h"
#include "TLFormulaFALSE.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaAND.inl.h"
#endif


TLFormulaAND::~TLFormulaAND (void)
{
  /* void */
}


TLFormula* TLFormulaAND::GetCopy (void) const
{
  return new TLFormulaAND (this);
}


TLFormula* TLFormulaAND::Rewrite (void) const
{
  assert (leftOperand);
  assert (rightOperand);
  
  if (simplifyFormulae)
  {  
    if (*leftOperand == *rightOperand)
    {
      return leftOperand->GetCopy();                // a && a <->  a
    }

    if (   (   (leftOperand->Operator() == NOT)
            && (*((TLFormulaNOT*)leftOperand)->RightOperand() == *rightOperand))
        || (   (rightOperand->Operator() == NOT)
            && (*((TLFormulaNOT*)rightOperand)->RightOperand() == *leftOperand))
       )
    {
      return new TLFormulaFALSE();                  // a && ~a <-> FALSE
    }
  }
    
  return new TLFormulaAND (leftOperand->Rewrite(),
                           rightOperand->Rewrite());
}


TLFormula* TLFormulaAND::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaOR (leftOperand->PushNegations(doIt),
                            rightOperand->PushNegations(doIt));
  else
    return new TLFormulaAND (leftOperand->PushNegations(doIt),
                             rightOperand->PushNegations(doIt));
}

SCNatural TLFormulaAND::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_0;
}


SCBoolean TLFormulaAND::operator== (const TLFormula& phi) const
{
  TLFormulaAND* tmpPhi = (TLFormulaAND*) &phi;
  
  if (op != tmpPhi->op)
    return false;
  
  assert (leftOperand);
  assert (rightOperand);
  assert (tmpPhi->leftOperand);
  assert (tmpPhi->rightOperand);

  if (*leftOperand == *(tmpPhi->leftOperand))     // left == left
  {
    if (*rightOperand == *(tmpPhi->rightOperand)) // right == right
    {
      return true;                                // o.k.
    }
  }

  if (*leftOperand == *(tmpPhi->rightOperand))    // try it the other way round
  {
    if (*rightOperand == *(tmpPhi->leftOperand))
    {
      return true;
    }
  }

  return false;                                   // Forget it babe...
}


SCBoolean TLFormulaAND::operator== (const TLFormula* phi) const
{
  return *this == *phi;
}


SCBoolean TLFormulaAND::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormulaAND::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}
