/*
 * File:    TLFormulaALWAYS.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAALWAYS_H_
#define _TLFORMULAALWAYS_H_

#include "TLFormulaUnary.h"

class TLFormulaALWAYS : public TLFormulaUnary
{
  public:
                                  TLFormulaALWAYS (      TLFormula* rightOp,
                                                         SCBoolean dummy, // Force compiler to
                                                                          // distinguish the
                                                                          // constructors.
                                                         SCNatural  pAcceptSet = UNDEFINED_LISTINDEX,
                                                   const SCObject*  Father = NULL);

                                  TLFormulaALWAYS (const TLFormulaALWAYS&);
                                  TLFormulaALWAYS (const TLFormulaALWAYS*);

                                  ~TLFormulaALWAYS (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaALWAYS (void);
                                                  // Forbidden!

};

#if _TL_INLINING_
#include "TLFormulaALWAYS.inl.h"
#endif

#endif // _TLFORMULAALWAYS_H_
