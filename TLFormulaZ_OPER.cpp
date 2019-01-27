/*
 * File:    TLFormulaZ_OPER.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

//#include <assert.h>
#include "TLFormulaZ_OPER.h"
#include "TLFormulaWAITFOR.h"
#include "TLFormulaALWAYS.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaAND.h"
//#include "SCL/SCListIter.h"
#include "TLFormulaSet.h"

#if _TL_INLINING_ == 0
#include "TLFormulaZ_OPER.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaZ_OPER::~TLFormulaZ_OPER (void)
{
  /* void */
}


TLFormula* TLFormulaZ_OPER::GetCopy (void) const
{
  return new TLFormulaZ_OPER (this);
}


TLFormula* TLFormulaZ_OPER::Rewrite (void) const
{
  if (TLFormula::partialRewrite)
  {
    return new TLFormulaZ_OPER (leftOperand->Rewrite(),
                                rightOperand->Rewrite());
  }
  else
  {
    return new TLFormulaUNTIL (rightOperand->Rewrite(),
                               new TLFormulaAND (leftOperand->Rewrite(),
                                                 rightOperand->Rewrite()));
                                                  // a Z b <==> b U (a && b)
                            
  }
}


TLFormula* TLFormulaZ_OPER::PushNegations (SCBoolean doIt) const
{
  if (TLFormula::partialRewrite)
  {
    if (doIt)
      return new TLFormulaWAITFOR (leftOperand->PushNegations(doIt),
                                   rightOperand->PushNegations(doIt));
    else
      return new TLFormulaZ_OPER (leftOperand->PushNegations(doIt),
                                  rightOperand->PushNegations(doIt));
  }
  else
  {
    TLAssert (false, "No Z_OPER allowed.");
    return NULL;
  }
}


SCNatural TLFormulaZ_OPER::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}


SCBoolean TLFormulaZ_OPER::HasAcceptanceStateSet (void) const
{
  return true;
}

