/*
 * File:    TLFormulaEQUIVALENT.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAEQUIVALENT_H_
#define _TLFORMULAEQUIVALENT_H_

#include "TLFormulaBinary.h"

class TLFormulaEQUIVALENT : public TLFormulaBinary
{
  public:
                                  TLFormulaEQUIVALENT (      TLFormula* pLeftOp,
                                                             TLFormula* pRightOp,
                                                       const SCObject*  pFather = NULL);

                                  TLFormulaEQUIVALENT (const TLFormulaEQUIVALENT&);
                                  TLFormulaEQUIVALENT (const TLFormulaEQUIVALENT*);

                                  ~TLFormulaEQUIVALENT (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaEQUIVALENT (void);
                                                  // Forbidden!
};


#if _TL_INLINING_
#include "TLFormulaEQUIVALENT.inl.h"
#endif

#endif // _TLFORMULAEQUIVALENT_H_
