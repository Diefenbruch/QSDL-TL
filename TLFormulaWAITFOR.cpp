/*
 * File:    TLFormulaWAITFOR.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

//#include <assert.h>
#include "TLFormulaWAITFOR.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaZ_OPER.h"
#include "TLFormulaFALSE.h"
#include "TLFormulaOR.h"

#if _TL_INLINING_ == 0
#include "TLFormulaWAITFOR.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaWAITFOR::~TLFormulaWAITFOR (void)
{
  /* void */
}


TLFormula* TLFormulaWAITFOR::GetCopy (void) const
{
  return new TLFormulaWAITFOR (this);
}


TLFormula* TLFormulaWAITFOR::Rewrite (void) const
{
  assert (leftOperand);
  assert (rightOperand);

  if (simplifyFormulae)
  {
    if (rightOperand->Operator() == WAITFOR)
    {
      assert (((TLFormulaWAITFOR*)rightOperand)->RightOperand());
      assert (((TLFormulaWAITFOR*)rightOperand)->LeftOperand());

      if (*((TLFormulaWAITFOR*)rightOperand)->LeftOperand() == *leftOperand)
      {
        return rightOperand->Rewrite();           // a W (a W b) <-> a W b
      }
    }

    if (leftOperand->Operator() == WAITFOR)
    {
      assert (((TLFormulaWAITFOR*)leftOperand)->RightOperand());
      assert (((TLFormulaWAITFOR*)leftOperand)->LeftOperand());

      if (*((TLFormulaWAITFOR*)leftOperand)->RightOperand() == *rightOperand)
      {
        return leftOperand->Rewrite();            // (a W b) W b <-> a W b
      }
    }
    
    if (rightOperand->Operator() == UNTIL)
    {
      TLFormulaUNTIL* tmpRight = (TLFormulaUNTIL*) rightOperand;
      assert (tmpRight->LeftOperand());
      assert (tmpRight->RightOperand());
      
      if (*tmpRight->LeftOperand() == *leftOperand)
      {
        return new TLFormulaWAITFOR (leftOperand->Rewrite(),
                                     tmpRight->RightOperand()->Rewrite());
                                                  // a W (a U b)  <-> a W b
      }
    }
    
    if (leftOperand->Operator() == UNTIL)
    {
      TLFormulaUNTIL* tmpLeft = (TLFormulaUNTIL*) leftOperand;
      assert (tmpLeft->LeftOperand());
      assert (tmpLeft->RightOperand());
      
      if (*tmpLeft->RightOperand() == *rightOperand)
      {
        return new TLFormulaUNTIL(tmpLeft->LeftOperand()->Rewrite(),
                                  rightOperand->Rewrite());
                                                  // (a U b) W b  <-> a U b
      }
    }

  }
  
  if (TLFormula::partialRewrite)
  {
    return new TLFormulaWAITFOR (leftOperand->Rewrite(),
                                 rightOperand->Rewrite());
  }
  else
  {
    TLFormulaFALSE* tmpLeftLeft = new TLFormulaFALSE();
    TLFormula*      tmpLeftRight = leftOperand->Rewrite();
  
    TLFormulaV_OPER* tmpLeft = new TLFormulaV_OPER (tmpLeftLeft,
                                                    tmpLeftRight);
                                                    
    TLFormulaUNTIL* tmpRight = new TLFormulaUNTIL (leftOperand->Rewrite(),
                                                   rightOperand->Rewrite());
    
    assert (tmpLeft);
    assert (tmpRight);
    
    return new TLFormulaOR (tmpLeft,
                            tmpRight);
                                                  // a W b <==> []a || a U b
                                                  // a W b <==> false V a || a U b
                            
  }
}


TLFormula* TLFormulaWAITFOR::PushNegations (SCBoolean doIt) const
{
  if (TLFormula::partialRewrite)
  {
    if (doIt)
      return new TLFormulaZ_OPER (leftOperand->PushNegations(doIt),
                                  rightOperand->PushNegations(doIt));
    else
      return new TLFormulaWAITFOR (leftOperand->PushNegations(doIt),
                                   rightOperand->PushNegations(doIt));
  }
  else
  {
    TLAssert (false, "No WAITFOR allowed.");
    return NULL;
  }
}


SCNatural TLFormulaWAITFOR::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}
