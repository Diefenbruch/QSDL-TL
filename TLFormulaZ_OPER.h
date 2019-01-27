/*
 * File:    TLFormulaZ_OPER.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAZ_OPER_H_
#define _TLFORMULAZ_OPER_H_

#include "TLFormulaBinary.h"

class TLFormulaZ_OPER : public TLFormulaBinary
{
  public:
                                  TLFormulaZ_OPER (      TLFormula* pLeftOp,
                                                         TLFormula* pRightOp,
                                                         SCNatural  pAcceptSetNo = UNDEFINED_LISTINDEX,
                                                   const SCObject*  pFather = NULL);

                                  TLFormulaZ_OPER (const TLFormulaZ_OPER&);
                                  TLFormulaZ_OPER (const TLFormulaZ_OPER*);

                                  ~TLFormulaZ_OPER (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;
                       SCBoolean  HasAcceptanceStateSet (void) const;

  protected:

  private:
                                  TLFormulaZ_OPER (void);
};

#if _TL_INLINING_
#include "TLFormulaZ_OPER.inl.h"
#endif

#endif // _TLFORMULAZ_OPER_H_
