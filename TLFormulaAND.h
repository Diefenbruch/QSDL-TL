/*
 * File:    TLFormulaAND.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAAND_H_
#define _TLFORMULAAND_H_

#include "TLFormulaBinary.h"

class TLFormulaAND : public TLFormulaBinary
{
  public:
                                  TLFormulaAND (      TLFormula* pLeftOp,
                                                      TLFormula* pRightOp,
                                                      SCNatural  pAcceptSetNo = UNDEFINED_LISTINDEX,
                                                const SCObject*  pFather = NULL);

                                  TLFormulaAND (const TLFormulaAND&);
                                  TLFormulaAND (const TLFormulaAND*);

                                  ~TLFormulaAND (void);

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
                                  TLFormulaAND (void);
                                                  // Forbidden!
};


#if _TL_INLINING_
#include "TLFormulaAND.inl.h"
#endif

#endif // _TLFORMULAAND_H_
