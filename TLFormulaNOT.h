/*
 * File:    TLFormulaNOT.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULANOT_H_
#define _TLFORMULANOT_H_

#include "TLFormulaUnary.h"

class TLFormulaNOT : public TLFormulaUnary
{
  public:
                                  TLFormulaNOT (      TLFormula* rightOp,
                                                      SCBoolean  dummy,
                                                const SCObject*  pFather= NULL);

                                  TLFormulaNOT (const TLFormulaNOT&);
                                  TLFormulaNOT (const TLFormulaNOT*);

                                  ~TLFormulaNOT (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaNOT (void);
                                                  // Forbidden!

};

#if _TL_INLINING_
#include "TLFormulaNOT.inl.h"
#endif

#endif // _TLFORMULANOT_H_
