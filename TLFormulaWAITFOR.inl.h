/*
 * File:    TLFormulaWAITFOR.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAWAITFOR_INL_H_
#define _TLFORMULAWAITFOR_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormulaWAITFOR::TLFormulaWAITFOR (      TLFormula* pLeftOp,
                                                   TLFormula* pRightOp,
                                             const SCObject*  pFather)
:  TLFormulaBinary (pLeftOp,
                    WAITFOR,
                    pRightOp,
                    UNDEFINED_LISTINDEX,
                    pFather)
{
  /* empty */
}


TLINLINE TLFormulaWAITFOR::TLFormulaWAITFOR (const TLFormulaWAITFOR& phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


TLINLINE TLFormulaWAITFOR::TLFormulaWAITFOR (const TLFormulaWAITFOR* phi)
:  TLFormulaBinary (phi)
{
  /* empty */
}


#endif // _TLFORMULAWAITFOR_INL_H_
