/*
 * File:    TLFormulaTRUE.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULATRUE_INL_H_
#define _TLFORMULATRUE_INL_H_

#include "SCL/SCStream.h"

#include "TLHelp.h"


TLINLINE TLFormulaTRUE::TLFormulaTRUE (const SCObject* pFather)
:  TLFormulaAtomic (StrDup ("TRUE"),
                    TruePropFunc,
                    pFather)
{
  op = T;
}


TLINLINE TLFormulaTRUE::TLFormulaTRUE (const TLFormulaTRUE& phi)
:  TLFormulaAtomic (phi)
{
  /* empty */
}


TLINLINE TLFormulaTRUE::TLFormulaTRUE (const TLFormulaTRUE* phi)
:  TLFormulaAtomic (phi)
{
  /* empty */
}

#endif // _TLFORMULATRUE_INL_H_
