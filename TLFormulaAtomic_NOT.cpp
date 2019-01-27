/*
 * File:    TLFormulaAtomic_NOT.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include "TLFormulaAtomic_NOT.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaAtomic_NOT.inl.h"
#endif

TLFormulaAtomic_NOT::~TLFormulaAtomic_NOT (void)
{
  /* empty */
}


TLFormula* TLFormulaAtomic_NOT::GetCopy (void) const
{
  return new TLFormulaAtomic_NOT (this);
}


TLFormula* TLFormulaAtomic_NOT::PushNegations (SCBoolean) const
{
  return new TLFormulaAtomic (StrDup (name),
                              propFunc);
}


TLFormula* TLFormulaAtomic_NOT::Rewrite (void) const
{
  return new TLFormulaAtomic_NOT (this);
}


SCBoolean TLFormulaAtomic_NOT::Evaluate (void) const
{
  return !propFunc();                             // Return the NEGATION!!!
}


TLFormulaAtomic* TLFormulaAtomic_NOT::GetNegation (void) const
{
  if (!negation)
  {
    negation = new TLFormulaAtomic (StrDup (name),
                                    propFunc);
  }
  return negation;
}


SCStream& TLFormulaAtomic_NOT::Display (SCStream& out) const
{
  return out << "~" << name;
}

