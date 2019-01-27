/*
 * File:    TLFormulaTRUE.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */


#include "TLFormulaTRUE.h"
#include "TLFormulaFALSE.h"


#if _TL_INLINING_ == 0
#include "TLFormulaTRUE.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

TLFormulaTRUE::~TLFormulaTRUE (void)
{
  /* empty */
}


TLFormula* TLFormulaTRUE::GetCopy (void) const
{
  return new TLFormulaTRUE();
}


TLFormula* TLFormulaTRUE::Rewrite (void) const
{
  return new TLFormulaTRUE();                    // No need for rewriting.
}


TLFormula* TLFormulaTRUE::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaFALSE();                 // true becomes false - life is a lie, you know...
  else
    return new TLFormulaTRUE();
}


