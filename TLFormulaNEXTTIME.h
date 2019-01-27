/*
 * File:    TLFormulaNEXTTIME.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULANEXTTIME_H_
#define _TLFORMULANEXTTIME_H_

#include "TLFormulaUnary.h"

class TLFormulaNEXTTIME : public TLFormulaUnary
{
  public:
                                  TLFormulaNEXTTIME (      TLFormula* pRightop,
                                                           SCBoolean  dummy,
                                                     const SCObject*  pFather = NULL);

                                  TLFormulaNEXTTIME (const TLFormulaNEXTTIME&);
                                  TLFormulaNEXTTIME (const TLFormulaNEXTTIME*);

                                  ~TLFormulaNEXTTIME (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;

  protected:

  private:
                                  TLFormulaNEXTTIME (void);
                                                  // Forbidden!
};

#if _TL_INLINING_
#include "TLFormulaNEXTTIME.inl.h"
#endif

#endif // _TLFORMULANEXTTIME_H_
