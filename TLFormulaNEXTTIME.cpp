/*
 * File:    TLFormulaNEXTTIME.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaNEXTTIME.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaNEXTTIME.inl.h"
#endif

TLFormulaNEXTTIME::~TLFormulaNEXTTIME (void)
{
  /* empty */
}


TLFormula* TLFormulaNEXTTIME::GetCopy (void) const
{
  return new TLFormulaNEXTTIME (this);
}


TLFormula* TLFormulaNEXTTIME::Rewrite (void) const
{
  return new TLFormulaNEXTTIME (rightOperand->Rewrite(),
                                true);
}


TLFormula* TLFormulaNEXTTIME::PushNegations (SCBoolean doIt) const
{
  return new TLFormulaNEXTTIME (rightOperand->PushNegations(doIt),
                                true);            // Nexttime is invariant
                                                  // to pushing of negations.
}


SCNatural TLFormulaNEXTTIME::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_2;
}

