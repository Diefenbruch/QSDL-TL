/*
 * File:    TLFormulaWAITFOR.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAWAITFOR_H_
#define _TLFORMULAWAITFOR_H_

#include "TLFormulaBinary.h"

class TLFormulaWAITFOR : public TLFormulaBinary
{
  public:
                                  TLFormulaWAITFOR (      TLFormula* pLeftOp,
                                                          TLFormula* pRightOp,
                                                    const SCObject*  pFather = NULL);

                                  TLFormulaWAITFOR (const TLFormulaWAITFOR&);
                                  TLFormulaWAITFOR (const TLFormulaWAITFOR*);

                                  ~TLFormulaWAITFOR (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaWAITFOR (void);
};

#if _TL_INLINING_
#include "TLFormulaWAITFOR.inl.h"
#endif

#endif // _TLFORMULAWAITFOR_H_
