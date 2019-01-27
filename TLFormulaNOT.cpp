/*
 * File:    TLFormulaNOT.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaNOT.h"
#include "TLFormulaAtomic.h"


#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaNOT.inl.h"
#endif


TLFormulaNOT::~TLFormulaNOT (void)
{
  /* empty */
}


TLFormula* TLFormulaNOT::GetCopy (void) const
{
  return new TLFormulaNOT (this);
}


TLFormula* TLFormulaNOT::Rewrite (void) const
{
  return new TLFormulaNOT(rightOperand->Rewrite(),
                          false);
}


TLFormula* TLFormulaNOT::PushNegations (SCBoolean doIt) const
{
  return rightOperand->PushNegations (!doIt);
}


SCNatural TLFormulaNOT::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_2;
}

