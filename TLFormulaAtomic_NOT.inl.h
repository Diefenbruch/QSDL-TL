/*
 * File:    TLFormulaAtomic_NOT.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */


#ifndef _TLFORMULAATOMICNOT_INL_H_
#define _TLFORMULAATOMICNOT_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"


TLINLINE TLFormulaAtomic_NOT::TLFormulaAtomic_NOT (      char*         pName,
                                                         SCPropFuncPtr pPropFunc,
                                                   const SCObject*     pFather)
:  TLFormulaAtomic (pName,
                    pPropFunc,
                    pFather)
{
  op = ATOMIC_NOT;                                // Need this for operator== to
                                                  // distinguish between pure atomics
                                                  // and Atomic_NOT.
}


TLINLINE TLFormulaAtomic_NOT::TLFormulaAtomic_NOT (const TLFormulaAtomic* phi)
:  TLFormulaAtomic (StrDup(phi->GetName()),
                    phi->GetPropFuncPtr())
{
  op = ATOMIC_NOT;
}


TLINLINE TLFormulaAtomic_NOT::TLFormulaAtomic_NOT (const TLFormulaAtomic& phi)
:  TLFormulaAtomic (StrDup(phi.GetName()),
                    phi.GetPropFuncPtr())
{
  op = ATOMIC_NOT;
}


TLINLINE TLFormulaAtomic_NOT::TLFormulaAtomic_NOT (const TLFormulaAtomic_NOT& phi)
:  TLFormulaAtomic (StrDup(phi.GetName()),
                    phi.GetPropFuncPtr())
{
  op = ATOMIC_NOT;
}


TLINLINE TLFormulaAtomic_NOT::TLFormulaAtomic_NOT (const TLFormulaAtomic_NOT* phi)
:  TLFormulaAtomic (StrDup(phi->GetName()),
                    phi->GetPropFuncPtr())
{
  op = ATOMIC_NOT;
}


TLINLINE SCStream& operator<< (SCStream& out, const TLFormulaAtomic_NOT& phi)
{
  return phi.Display(out);
}


TLINLINE SCStream& operator<< (SCStream& out, const TLFormulaAtomic_NOT* phi)
{
  return out << *phi;
}

#endif // _TLFORMULAATOMICNOT_INL_H_
