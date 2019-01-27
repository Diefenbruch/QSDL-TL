/*
 * File:    TLFormulaOR.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaOR.h"
#include "TLFormulaAND.h"
#include "TLFormulaNOT.h"
#include "TLFormulaTRUE.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaOR.inl.h"
#endif


TLFormulaOR::~TLFormulaOR (void)
{
  /* void */
}


TLFormula* TLFormulaOR::GetCopy (void) const
{
  return new TLFormulaOR (this);
}


TLFormula* TLFormulaOR::Rewrite (void) const
{
  assert (leftOperand);
  assert (rightOperand);

  if (simplifyFormulae)
  {
    if (*leftOperand == *rightOperand)
    {
      return leftOperand->GetCopy();                // a || a <->  a
    }

    if (   (   (leftOperand->Operator() == NOT)
            && (*((TLFormulaNOT*)leftOperand)->RightOperand() == *rightOperand))
        || (   (rightOperand->Operator() == NOT)
            && (*((TLFormulaNOT*)rightOperand)->RightOperand() == *leftOperand))
       )
    {
      return new TLFormulaTRUE();                  // a || ~a <-> TRUE
    }
  }
  
  return new TLFormulaOR (leftOperand->Rewrite(),
                          rightOperand->Rewrite());
}


TLFormula* TLFormulaOR::PushNegations (SCBoolean doIt) const
{
  if (doIt)  
    return new TLFormulaAND (leftOperand->PushNegations(doIt),
                             rightOperand->PushNegations(doIt));                              
  else
    return new TLFormulaOR (leftOperand->PushNegations(doIt),
                            rightOperand->PushNegations(doIt));                              

}


SCNatural TLFormulaOR::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_0;
}


SCBoolean TLFormulaOR::operator== (const TLFormula& phi) const
{
  TLFormulaOR* tmpPhi = (TLFormulaOR*) &phi;
  
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


SCBoolean TLFormulaOR::operator== (const TLFormula* phi) const
{
  return *this == *phi;
}


SCBoolean TLFormulaOR::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormulaOR::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}
