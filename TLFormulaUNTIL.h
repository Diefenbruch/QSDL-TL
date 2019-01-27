/*
 * File:    TLFormulaUNTIL.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAUNTIL_H_
#define _TLFORMULAUNTIL_H_

#include "TLFormulaBinary.h"

class TLFormulaUNTIL : public TLFormulaBinary
{
  public:
                                  TLFormulaUNTIL (      TLFormula* pLeftOp,
                                                        TLFormula* pRightOp,
                                                        SCNatural  pAcceptSetNo = UNDEFINED_LISTINDEX,
                                                  const SCObject*  pFather = NULL);

                                  TLFormulaUNTIL (const TLFormulaUNTIL&);
                                  TLFormulaUNTIL (const TLFormulaUNTIL*);

                                  ~TLFormulaUNTIL (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;
                       SCBoolean  HasAcceptanceStateSet (void) const;

  protected:

  private:
                                  TLFormulaUNTIL (void);
                                                  // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaUNTIL.inl.h"
#endif

#endif // _TLFORMULAUNTIL_H_
