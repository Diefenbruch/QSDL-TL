/*
 * File:    TLFormulaALWAYS.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "SCL/SCStream.h"

#include "TLFormulaALWAYS.h"
#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaFALSE.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
  #include "TLFormulaALWAYS.inl.h"
#endif


TLFormulaALWAYS::~TLFormulaALWAYS (void)
{
  /* empty */
}


TLFormula* TLFormulaALWAYS::GetCopy (void) const
{
  return new TLFormulaALWAYS (this);
}


TLFormula* TLFormulaALWAYS::Rewrite (void) const
{
  assert (rightOperand);

  if (simplifyFormulae)
  {
    if (rightOperand->Operator() == ALWAYS)
    {
      return rightOperand->Rewrite();             // [][]...[]a  <->  []a
    }

    if (rightOperand->Operator() == EVENTUALLY)
    {
      TLFormulaEVENTUALLY* tmpRight = (TLFormulaEVENTUALLY*) rightOperand;
      
      if (tmpRight->RightOperand()->Operator() == ALWAYS)
      {
        return rightOperand->Rewrite();           // []<>[]...[]<>[]a  <->  <>[]a
      }
    }
  }
  
  if (TLFormula::partialRewrite)                  // Don´t rewrite it.
  {
    return new TLFormulaALWAYS (rightOperand->Rewrite(), false);
  }
  else                                            // Rewrite it.
  {
    return new TLFormulaV_OPER (new TLFormulaFALSE(),
                                rightOperand->Rewrite());
  }
}


TLFormula* TLFormulaALWAYS::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaEVENTUALLY (rightOperand->PushNegations(doIt),
                                    false);
  else
    return new TLFormulaALWAYS(rightOperand->PushNegations(doIt),
                               false);
}


SCNatural TLFormulaALWAYS::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_2;
}
