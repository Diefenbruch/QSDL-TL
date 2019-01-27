/*
 * File:    TLFormulaIMPLIES.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaIMPLIES.h"
#include "TLFormulaOR.h"
#include "TLFormulaNOT.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaIMPLIES.inl.h"
#endif


TLFormulaIMPLIES::~TLFormulaIMPLIES (void)
{
  /* void */
}


TLFormula* TLFormulaIMPLIES::GetCopy (void) const
{
  return new TLFormulaIMPLIES (this);
}


TLFormula* TLFormulaIMPLIES::Rewrite (void) const
{
  TLFormulaNOT* tmpLeft = new TLFormulaNOT (leftOperand->Rewrite(),
                                           true);
  TLFormula* tmpRight = rightOperand->Rewrite();
  
  assert (tmpLeft);
  assert (tmpRight);
  
  return new TLFormulaOR (tmpLeft,
                          tmpRight);
}


TLFormula* TLFormulaIMPLIES::PushNegations (SCBoolean) const
{
  TLAssert (false, "Operator IMPLIES not allowed here.");
  return NULL;
}


SCNatural TLFormulaIMPLIES::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_1;
}


