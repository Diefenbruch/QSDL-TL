/*
 * File:    TLFormulaBinary.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULABINARY_H_
#define _TLFORMULABINARY_H_

#include "TLFormulaUnary.h"

class TLFormulaBinary : public TLFormulaUnary
{
  friend class SCStream& operator<< (class SCStream&, const TLFormulaBinary&);

  public:
                                  TLFormulaBinary (      TLFormula* pLeft,
                                                         TLLetter   pOp,
                                                         TLFormula* pRight,
                                                         SCNatural  acceptSet = UNDEFINED_LISTINDEX,
                                                   const SCObject*  father = NULL);

                                  TLFormulaBinary (const TLFormulaBinary&);
                                  TLFormulaBinary (const TLFormulaBinary*);

                                 ~TLFormulaBinary (void);

                       TLArity    Arity (void) const;
                       SCNatural  NumOfSymbols (void) const;
                       SCBoolean  SetUpAcceptanceSets (void);
                 class SCStream&   Display (SCStream&) const;
                       SCBoolean  operator== (const TLFormula&) const;
                       SCBoolean  operator== (const TLFormula*) const;
                       SCBoolean  operator!= (const TLFormula&) const;
                       SCBoolean  operator!= (const TLFormula*) const;
                       TLFormula* LeftOperand (void) const;
                       void       SetLeftOperand (TLFormula*);
                 
  protected:
                                                  
    TLFormula* leftOperand;
    
  private:
                                  TLFormulaBinary (void);
                                                  // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaBinary.inl.h"
#endif

class SCStream& operator<< (class SCStream&, const TLFormulaBinary&);

#endif // _TLFORMULABINARY_H_
