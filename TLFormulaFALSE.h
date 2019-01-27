/*
 * File:    TLFormulaFALSE.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAFALSE_H_
#define _TLFORMULAFALSE_H_

#include "TLFormulaAtomic.h"

class TLFormulaFALSE : public TLFormulaAtomic
{
  public:
                                  TLFormulaFALSE (const SCObject* pFather = NULL);

                                  TLFormulaFALSE (const TLFormulaFALSE&);
                                  TLFormulaFALSE (const TLFormulaFALSE*);

                                  ~TLFormulaFALSE (void);
                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;

  protected:

  private:

};

#if _TL_INLINING_
#include "TLFormulaFALSE.inl.h"
#endif

#endif // _TLFORMULAFALSE_H_
