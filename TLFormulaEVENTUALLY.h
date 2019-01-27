/*
 * File:    TLFormulaEVENTUALLY.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAEVENTUALLY_H_
#define _TLFORMULAEVENTUALLY_H_

#include "TLFormulaUnary.h"

class TLFormulaEVENTUALLY : public TLFormulaUnary
{
  public:
                                  TLFormulaEVENTUALLY (      TLFormula* pRightOp,
                                                             SCBoolean  dummy,
                                                             SCNatural  pAceptSetNo = UNDEFINED_LISTINDEX,
                                                       const SCObject*  pFather = NULL);

                                  TLFormulaEVENTUALLY (const TLFormulaEVENTUALLY&);
                                  TLFormulaEVENTUALLY (const TLFormulaEVENTUALLY*);

                                  ~TLFormulaEVENTUALLY (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;
                       SCBoolean  HasAcceptanceStates (void) const;

  protected:

  private:
                                  TLFormulaEVENTUALLY (void);
                                                  // Forbidden!

};

#if _TL_INLINING_
#include "TLFormulaEVENTUALLY.inl.h"
#endif

#endif // _TLFORMULAEVENTUALLY_H_
