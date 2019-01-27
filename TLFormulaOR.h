/*
 * File:    TLFormulaOR.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAOR_H_
#define _TLFORMULAOR_H_

#include "TLFormulaBinary.h"

class TLFormulaOR : public TLFormulaBinary
{
  public:
                                  TLFormulaOR (      TLFormula* prightOp,
                                                     TLFormula* pLeftop,
                                               const SCObject*  pFather = NULL);

                                  TLFormulaOR (const TLFormulaOR&);
                                  TLFormulaOR (const TLFormulaOR*);

                                  ~TLFormulaOR (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;
                       SCBoolean  operator== (const TLFormula&) const;
                       SCBoolean  operator== (const TLFormula*) const;
                       SCBoolean  operator!= (const TLFormula&) const;
                       SCBoolean  operator!= (const TLFormula*) const;


  protected:
  
  private:
                                  TLFormulaOR (void);
                                                  // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaOR.inl.h"
#endif

#endif // _TLFORMULAOR_H_
