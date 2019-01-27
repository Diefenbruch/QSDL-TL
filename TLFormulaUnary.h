/*
 * File:    TLFormulaUnary.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAUNARY_H_
#define _TLFORMULAUNARY_H_

#include "SCL/SCObject.h"
#include "TLFormula.h"

class TLFormulaUnary : public TLFormula
{
  friend class SCStream& operator<< (class SCStream&, TLFormulaUnary&);

  public:
                      TLFormulaUnary (const TLLetter   op,
                                            TLFormula* rightOp,
                                            SCNatural  acceptSet = UNDEFINED_LISTINDEX,
                                      const SCObject*  father = NULL);

                      TLFormulaUnary (const TLFormulaUnary&);
                      TLFormulaUnary (const TLFormulaUnary*);

                      ~TLFormulaUnary (void);

          TLArity     Arity (void) const;
          SCNatural   NumOfSymbols (void) const;
          SCBoolean   SetUpAcceptanceSets (void);
    class SCStream&    Display (SCStream&) const;
          SCBoolean   operator== (const TLFormula&) const;
          SCBoolean   operator== (const TLFormula*) const;
          SCBoolean   operator!= (const TLFormula&) const;
          SCBoolean   operator!= (const TLFormula*) const;
          TLFormula*  RightOperand (void) const;
          void        SetRightOperand (TLFormula*);

  protected:
                                                  
          TLFormula*  rightOperand;

  private:
                      TLFormulaUnary (void);      // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaUnary.inl.h"
#endif

class SCStream& operator<< (class SCStream&, TLFormulaUnary&);
class SCStream& operator<< (class SCStream&, TLFormulaUnary*);

#endif // _TLFORMULAUNARY_H_
