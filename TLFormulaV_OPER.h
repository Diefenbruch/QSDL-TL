/*
 * File:    TLFormulaV_OPER.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAV_OPER_H_
#define _TLFORMULAV_OPER_H_

#include "TLFormulaBinary.h"

class TLFormulaV_OPER : public TLFormulaBinary
{
  public:
                                  TLFormulaV_OPER (TLFormula* pLeftOp,
                                                   TLFormula* pRightOp,
                                                   SCNatural  pAcceptSetNo = UNDEFINED_LISTINDEX,
                                                   const SCObject*  pFahter = NULL);

                                  TLFormulaV_OPER (const TLFormulaV_OPER&);
                                  TLFormulaV_OPER (const TLFormulaV_OPER*);

                                  ~TLFormulaV_OPER (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaV_OPER (void);
                                                  // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaV_OPER.inl.h"
#endif

#endif // _TLFORMULAV_OPER_H_
