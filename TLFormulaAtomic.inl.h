/*
 * File:    TLFormulaAtomic.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAATOMIC_INL_H_
#define _TLFORMULAATOMIC_INL_H_


#include "SCL/SCStream.h"                              // Need this for INLINEing!
#include "TLHelp.h"


TLINLINE TLFormulaAtomic::TLFormulaAtomic (      char*         pName,
                                                 SCPropFuncPtr pPropFunc,
                                           const SCObject*     pFather)
:  TLFormula (ATOMIC,
              UNDEFINED_LISTINDEX,
              pFather),
   propFunc (pPropFunc),
   name (pName),
   negation (NULL)
{
  /* empty */
}


TLINLINE TLFormulaAtomic::TLFormulaAtomic (const TLFormulaAtomic& phi)
:  TLFormula (phi),
   propFunc (phi.propFunc),
   name (StrDup (phi.name)),
   negation (NULL)
{
  /* empty */
}


TLINLINE TLFormulaAtomic::TLFormulaAtomic (const TLFormulaAtomic* phi)
:  TLFormula (phi),
   propFunc (phi->propFunc),
   name (StrDup (phi->name)),
   negation (NULL)
{
  /* empty */
}


TLINLINE const char* TLFormulaAtomic::GetName (void) const
{
  return name;
}


TLINLINE SCPropFuncPtr TLFormulaAtomic::GetPropFuncPtr (void) const
{
  return propFunc;
}


TLINLINE SCStream& operator<< (SCStream& out,
                              const TLFormulaAtomic& phi)
{
  return phi.Display(out);
}


TLINLINE SCStream& operator<< (SCStream& out,
                              const TLFormulaAtomic* phi)
{
  return out << *phi;
}

#endif // _TLFORMULAATOMIC_INL_H_
