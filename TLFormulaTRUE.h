/*
 * File:    TLFormulaTRUE.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULATRUE_H_
#define _TLFORMULATRUE_H_

#include "TLFormulaAtomic.h"

class TLFormulaTRUE : public TLFormulaAtomic
{
  public:
                                  TLFormulaTRUE (const SCObject* pFather = NULL);

                                  TLFormulaTRUE (const TLFormulaTRUE&);
                                  TLFormulaTRUE (const TLFormulaTRUE*);

                                  ~TLFormulaTRUE (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;

  protected:

  private:

};

#if _TL_INLINING_
#include "TLFormulaTRUE.inl.h"
#endif

#endif // _TLFORMULATRUE_H_
