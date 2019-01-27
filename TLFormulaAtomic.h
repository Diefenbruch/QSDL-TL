/*
 * File:    TLFormulaAtomic.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULAATOMIC_H_
#define _TLFORMULAATOMIC_H_

#include "TLFormula.h"

class TLFormulaAtomic : public TLFormula
{
  friend class SCStream& operator<< (class SCStream&, const TLFormulaAtomic&);

  public:
                                  TLFormulaAtomic (      char*         pName,
                                                         SCPropFuncPtr pPropFunc,
                                                   const SCObject*     pFather = NULL);

                                  TLFormulaAtomic (const TLFormulaAtomic&);
                                  TLFormulaAtomic (const TLFormulaAtomic*);

                                  ~TLFormulaAtomic (void);

                       TLFormula* GetCopy (void) const;
                       TLFormula* PushNegations (SCBoolean) const;
                       TLFormula* Rewrite (void) const;
                       SCBoolean  SetUpAcceptanceSets (void);
                       TLArity    Arity (void) const;
                       SCNatural  GetPrecedenceLevel (void) const;
                 class SCStream&   Display (class SCStream&) const;
                       SCBoolean  operator== (const TLFormula&) const;
                       SCBoolean  operator== (const TLFormula*) const;
                       SCBoolean  operator!= (const TLFormula&) const;
                       SCBoolean  operator!= (const TLFormula*) const;

    virtual            SCBoolean  Evaluate (void) const;
                                                  // Evaluate given
                                                  // proposition function.
                                                  // Start of virtuality is here.
                                                  
    virtual            TLFormulaAtomic* GetNegation (void) const;
                                                  // Return the negation of *this.

                 const char*          GetName (void) const;
                       SCPropFuncPtr  GetPropFuncPtr (void) const;
  protected:
            SCPropFuncPtr    propFunc;            // Pointer to proposition function.
            char*            name;                // String representation of name.
    mutable TLFormulaAtomic* negation;
    
  private:
                                  TLFormulaAtomic (void);
                                                  // Forbidden!
                                  
};

#if _TL_INLINING_
#include "TLFormulaAtomic.inl.h"
#endif

class SCStream& operator<< (class SCStream&, const TLFormulaAtomic&);
class SCStream& operator<< (class SCStream&, const TLFormulaAtomic*);

#endif // _TLFORMULAATOMIC_H_
