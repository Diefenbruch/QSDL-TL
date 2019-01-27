/*
 * File:    TLFormulaIMPLIES.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAIMPLIES_H_
#define _TLFORMULAIMPLIES_H_

#include "TLFormulaBinary.h"

class TLFormulaIMPLIES : public TLFormulaBinary
{
  public:
                                  TLFormulaIMPLIES (TLFormula* pLeftOp,
                                                    TLFormula* pRightOp,
                                                    const SCObject*  pFather = NULL);

                                  TLFormulaIMPLIES (const TLFormulaIMPLIES&);
                                  TLFormulaIMPLIES (const TLFormulaIMPLIES*);

                                  ~TLFormulaIMPLIES (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
//                                  TLFormulaImplies (void);
                                                  // Forbidden!
};


#if _TL_INLINING_
#include "TLFormulaIMPLIES.inl.h"
#endif

#endif // _TLFORMULAIMPLIES_H_
