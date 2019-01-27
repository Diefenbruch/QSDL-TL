/*
 * File:    TLFormulaUNTIL.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaUNTIL.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaWAITFOR.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaFALSE.h"
//#include "SCL/SCListIter.h"
#include "TLFormulaSet.h"

#if _TL_INLINING_ == 0
#include "TLFormulaUNTIL.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaUNTIL::~TLFormulaUNTIL (void)
{
  /* void */
}


TLFormula* TLFormulaUNTIL::GetCopy (void) const
{
  return new TLFormulaUNTIL (this);
}


TLFormula* TLFormulaUNTIL::Rewrite (void) const
{
  assert (leftOperand);
  assert (rightOperand);
  
  if (simplifyFormulae)
  {
    if (rightOperand->Operator() == T)
    {
      return new TLFormulaTRUE();                   // a U T <-> T
    }

    if (rightOperand->Operator() == F)
    {
      return new TLFormulaFALSE();                  // a U F <-> F
    }

    if (rightOperand->Operator() == UNTIL)
    {
      assert (((TLFormulaUNTIL*)rightOperand)->RightOperand());
      assert (((TLFormulaUNTIL*)rightOperand)->LeftOperand());

      if (*((TLFormulaUNTIL*)rightOperand)->LeftOperand() == *leftOperand)
      {
        return rightOperand->Rewrite();             // a U (a U b) <-> a U b
      }
    }

    if (leftOperand->Operator() == UNTIL)
    {
      assert (((TLFormulaUNTIL*)leftOperand)->RightOperand());
      assert (((TLFormulaUNTIL*)leftOperand)->LeftOperand());

      if (*((TLFormulaUNTIL*)leftOperand)->RightOperand() == *rightOperand)
      {
        return leftOperand->Rewrite();             // (a U b) b <-> a U b
      }
    }

    if (rightOperand->Operator() == WAITFOR)
    {
      TLFormulaWAITFOR* tmpRight = (TLFormulaWAITFOR*) rightOperand;
      
      if (*tmpRight->LeftOperand() == *leftOperand)
      {
        return new TLFormulaWAITFOR (leftOperand->Rewrite(),
                                     tmpRight->RightOperand()->Rewrite());
                                                  // a U (a W b)  <-> a W b
      }
    }

    if (leftOperand->Operator() == WAITFOR)
    {
      TLFormulaWAITFOR* tmpLeft = (TLFormulaWAITFOR*) leftOperand;
      
      if (*tmpLeft->RightOperand() == *rightOperand)
      {
        return new TLFormulaUNTIL (tmpLeft->LeftOperand()->Rewrite(),
                                   rightOperand->Rewrite());
                                                  // (a W b) U b  <-> a U b
      }
    }
  }
  
  return new TLFormulaUNTIL (leftOperand->Rewrite(),
                             rightOperand->Rewrite());
}


TLFormula* TLFormulaUNTIL::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaV_OPER (leftOperand->PushNegations (doIt),
                                rightOperand->PushNegations (doIt));
  else
    return new TLFormulaUNTIL (leftOperand->PushNegations (doIt),
                               rightOperand->PushNegations (doIt));
}


SCNatural TLFormulaUNTIL::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}


SCBoolean TLFormulaUNTIL::HasAcceptanceStateSet (void) const
{
  return true;
}


