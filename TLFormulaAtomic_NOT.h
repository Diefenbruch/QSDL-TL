/*
 * File:    TLFormulaAtomic_NOT.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAATOMICNOT_H_
#define _TLFORMULAATOMICNOT_H_

#include "TLFormulaAtomic.h"

class TLFormulaAtomic_NOT : public TLFormulaAtomic
{
  friend class SCStream& operator<< (class SCStream&, const TLFormulaAtomic_NOT&);

  public:
                                  TLFormulaAtomic_NOT (      char*         pName,
                                                             SCPropFuncPtr pPropFunc,
                                                       const SCObject*     pFather = NULL);

                                  TLFormulaAtomic_NOT (const TLFormulaAtomic*);
                                  TLFormulaAtomic_NOT (const TLFormulaAtomic&);

                                  TLFormulaAtomic_NOT (const TLFormulaAtomic_NOT*);
                                  TLFormulaAtomic_NOT (const TLFormulaAtomic_NOT&);

                                  ~TLFormulaAtomic_NOT (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCBoolean  Evaluate (void) const;
                                                  // Evaluate NEGATION of given
                                                  // proposition function.

                       TLFormulaAtomic* GetNegation (void) const;
                                                  // Return the negation of *this.

                 class SCStream&   Display (class SCStream&) const;

  protected:

  private:
                                  TLFormulaAtomic_NOT (void);
                                                  // Forbidden.
};

class SCStream& operator<< (class SCStream&, const TLFormulaAtomic_NOT&);
class SCStream& operator<< (class SCStream&, const TLFormulaAtomic_NOT*);

#if _TL_INLINING_
#include "TLFormulaAtomic_NOT.inl.h"
#endif

#endif // _TLFORMULAATOMICNOT_H_
