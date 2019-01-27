/*
 * File:    TLFormulaFALSE.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAFALSE_INL_H_
#define _TLFORMULAFALSE_INL_H_

#include "TLHelp.h"


TLINLINE TLFormulaFALSE::TLFormulaFALSE (const SCObject* pFather)
:  TLFormulaAtomic (StrDup ("FALSE"),
                    TruePropFunc,
                    pFather)
{
  op = F;
}


TLINLINE TLFormulaFALSE::TLFormulaFALSE (const TLFormulaFALSE& phi)
:  TLFormulaAtomic (phi)
{
  /* empty */
}


TLINLINE TLFormulaFALSE::TLFormulaFALSE (const TLFormulaFALSE* phi)
:  TLFormulaAtomic (phi)
{
  /* empty */
}

#endif // _TLFORMULAFALSE_INL_H_
