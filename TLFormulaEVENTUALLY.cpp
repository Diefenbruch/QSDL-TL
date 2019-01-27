/*
 * File:    TLFormulaEVENTUALLY.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaALWAYS.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaNOT.h"
#include "TLHelp.h"
//#include "SCL/SCListIter.h"
#include "TLFormulaSet.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaEVENTUALLY.inl.h"
#endif


TLFormulaEVENTUALLY::~TLFormulaEVENTUALLY (void)
{
  /* empty */
}


TLFormula* TLFormulaEVENTUALLY::GetCopy (void) const
{
  return new TLFormulaEVENTUALLY (this);
}


TLFormula* TLFormulaEVENTUALLY::Rewrite (void) const
{
  assert (rightOperand);
  
  if (simplifyFormulae)
  {
    if (rightOperand->Operator() == EVENTUALLY)
    {
      return rightOperand->Rewrite();             // <>...<>a  <->  <>a
    }

    if (rightOperand->Operator() == ALWAYS)
    {
      TLFormulaALWAYS* tmpRight = (TLFormulaALWAYS*) rightOperand;
      
      if (tmpRight->RightOperand()->Operator() == EVENTUALLY)
      {
        return rightOperand->Rewrite();           // <>[]<>...<>[]<>a  <->  []<>a
      }
    }
  }

  if (TLFormula::partialRewrite)                  // Don´t rewrite it.
  {
    return new TLFormulaEVENTUALLY (rightOperand->Rewrite(),
                                    true);
  }
  else                                            // Rewrite it.
  {
    return new TLFormulaUNTIL (new TLFormulaTRUE(),
                               rightOperand->Rewrite());
                                                  // <>a <=> true U a
  }
}


TLFormula* TLFormulaEVENTUALLY::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaALWAYS (rightOperand->PushNegations(doIt),
                                true);
  else
    return new TLFormulaEVENTUALLY (rightOperand->PushNegations(doIt),
                                    true);

}


SCNatural TLFormulaEVENTUALLY::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_2;
}


SCBoolean TLFormulaEVENTUALLY::HasAcceptanceStates (void) const
{
  return true;
}



