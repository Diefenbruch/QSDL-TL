/*
 * File:    TLFormulaEQUIVALENT.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaEQUIVALENT.h"
#include "TLFormulaOR.h"
#include "TLFormulaNOT.h"
#include "TLFormulaAND.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaEQUIVALENT.inl.h"
#endif


TLFormulaEQUIVALENT::~TLFormulaEQUIVALENT (void)
{
  /* void */
}


TLFormula* TLFormulaEQUIVALENT::GetCopy (void) const
{
  return new TLFormulaEQUIVALENT (this);
}


TLFormula* TLFormulaEQUIVALENT::Rewrite (void) const
{
  TLFormulaAND* tmpLeft = new TLFormulaAND (leftOperand->Rewrite(),
                                            rightOperand->Rewrite());
  
  TLFormulaAND* tmpRight = new TLFormulaAND (new TLFormulaNOT (leftOperand->Rewrite(), false),
                                             new TLFormulaNOT (rightOperand->Rewrite(), false));
                                                  // Don't try to optimize by using
                                                  // temps that do the rewrite once!
                                                  // We HAVE to keep it a tree, not
                                                  //a graph!!!

  return new TLFormulaOR (tmpLeft,
                          tmpRight);              // a <=> b --> (a && b) || (!a && !b)
}


TLFormula* TLFormulaEQUIVALENT::PushNegations (SCBoolean) const
{
  TLAssert (false, "Operator EQUIVALENT not allowed here.");
  return NULL;
}


SCNatural TLFormulaEQUIVALENT::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}


