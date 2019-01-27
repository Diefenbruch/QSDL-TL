/*
 * File:    TLFormulaV_OPER.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaV_OPER.h"
#include "TLFormulaUNTIL.h"

#if _TL_INLINING_ == 0
#include "TLFormulaV_OPER.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaV_OPER::~TLFormulaV_OPER (void)
{
  /* void */
}


TLFormula* TLFormulaV_OPER::GetCopy (void) const
{
  return new TLFormulaV_OPER (this);
}


TLFormula* TLFormulaV_OPER::Rewrite (void) const
{
  return new TLFormulaV_OPER (leftOperand->Rewrite(),
                              rightOperand->Rewrite());
                                                  // a V b <==> (b W (a && b))
}


TLFormula* TLFormulaV_OPER::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaUNTIL (leftOperand->PushNegations(doIt),
                               rightOperand->PushNegations(doIt));
  else
    return new TLFormulaV_OPER (leftOperand->PushNegations(doIt),
                                rightOperand->PushNegations(doIt));

}


SCNatural TLFormulaV_OPER::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}

