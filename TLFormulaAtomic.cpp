/*
 * File:    TLFormulaAtomic.cc
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#include <string.h>
#include "TLFormulaAtomic_NOT.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
#include "TLFormulaAtomic.inl.h"
#endif


TLFormulaAtomic::~TLFormulaAtomic (void)
{
  propFunc = NULL;
  delete[] name;
  name = NULL;
  if (negation)
  {
    delete negation;
    negation = NULL;
  }
}


TLFormula* TLFormulaAtomic::GetCopy (void) const
{
  return new TLFormulaAtomic (this);
}


TLFormula* TLFormulaAtomic::Rewrite (void) const
{
  return new TLFormulaAtomic (this);              // No need for rewriting.
}


TLFormula* TLFormulaAtomic::PushNegations (SCBoolean doIt) const
{
  if (doIt)
    return new TLFormulaAtomic_NOT (StrDup(name),
                                    propFunc);
  else
    return new TLFormulaAtomic (this);
}




TLArity TLFormulaAtomic::Arity (void) const
{
  return TLAtomic;
}


SCBoolean TLFormulaAtomic::SetUpAcceptanceSets (void)
{
  acceptanceSetNo = UNDEFINED_LISTINDEX;
  return true;                                    // Nothing else to do here.
}


SCNatural TLFormulaAtomic::GetPrecedenceLevel (void) const
{
  return PREC_LEVEL_3;                            // Highest for atomics.
}


SCBoolean TLFormulaAtomic::Evaluate (void) const
{
  return propFunc();
}


TLFormulaAtomic* TLFormulaAtomic::GetNegation (void) const
{
  if (!negation)
  {
    negation = new TLFormulaAtomic_NOT (StrDup (name),
                                        propFunc);
  }
  return negation;
}


SCBoolean TLFormulaAtomic::operator== (const TLFormula& phi) const
{
  TLFormulaAtomic* tmpPhi = (TLFormulaAtomic*) &phi;
  
  if (op != tmpPhi->op)
    return false;
  
  if (strcmp (name, tmpPhi->name))
    return false;
  
  return true;
}


SCBoolean TLFormulaAtomic::operator== (const TLFormula* phi) const
{
  return *this == *phi;
}


SCBoolean TLFormulaAtomic::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormulaAtomic::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}


SCStream& TLFormulaAtomic::Display (SCStream& out) const
{
  return out << name;
}
