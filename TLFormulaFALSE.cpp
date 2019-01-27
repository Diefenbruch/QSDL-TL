/*
 * File:    TLFormulaFALSE.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "SCL/SCStream.h"

#include "TLFormulaFALSE.h"
#include "TLFormulaTRUE.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaFALSE.inl.h"
#endif


TLFormulaFALSE::~TLFormulaFALSE (void)
{
  /* empty */
}


TLFormula* TLFormulaFALSE::GetCopy (void) const
{
  return new TLFormulaFALSE();
}


TLFormula* TLFormulaFALSE::Rewrite (void) const
{
  return new TLFormulaFALSE ();                   // No need for rewriting.
}


TLFormula* TLFormulaFALSE::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaTRUE();                 // true becomes false.
  else
    return new TLFormulaFALSE();
}

