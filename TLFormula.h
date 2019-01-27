/*
 * File:    TLFormula.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULA_H_
#define _TLFORMULA_H_


#include "SCL/SCObject.h"
#include "TL.h"


class TLFormula : public SCObject                        // Has to be derived from
                                                  // SCObject as we want to use
                                                  // it with SC*-classes!
{
  friend class SCStream& operator << (class SCStream&,
                                     const TLFormula&);

  public:
                                  TLFormula (const TLLetter   op,
                                             SCNatural  acceptSetNo = UNDEFINED_LISTINDEX,
                                             const SCObject*  father = NULL);

                                  TLFormula (const TLFormula&);
                                  TLFormula (const TLFormula*);

    virtual                       ~TLFormula (void);

    virtual            TLFormula* GetCopy (void) const = 0;
                                                  // Return a copy of *this.
                                                  // Virtual constructor.

    virtual            TLArity    Arity (void) const = 0;
                                                  // Arity of formula. C.f.
                                                  // TL.h for details on legal
                                                  // values for arity.

    virtual            TLFormula* PushNegations (SCBoolean) const = 0;
                                                  // Return a copy of this with
                                                  // all negations pushed in front
                                                  // of the atomic propositions, so
                                                  // that no negations stand before
                                                  // any operator.

    virtual            TLFormula* Rewrite (void) const = 0;
                                                  // Rewrite the formula, so
                                                  // that it only contains the
                                                  // operators
                                                  // ||, &&, !, U, V, X.
                                                  // if pedanticEventually,
                                                  // interpret <>a as !a U a
                                                  // rather than true U a.
                                                  // if partial rewrite, do not
                                                  // rewrite the operators
                                                  // <> and [].

    virtual            SCNatural  NumOfSymbols (void) const;
                                                  // Number of symbols in
                                                  // formula excluding
                                                  // punctuation marks
                                                  // (parenthesis, comma, etc).
                                                  // The number of symbols in
                                                  // a formula is equal to the
                                                  // number of its subformulae:
                                                  // a U b: a, b, a U b

    virtual            SCNatural  GetPrecedenceLevel (void) const = 0;
                                                  // Used by Display method to
                                                  // determine when to print
                                                  // parentheses. C.f. TL.y

    virtual            SCBoolean  HasAcceptanceStateSet (void) const;
                                                  // True, iff the formula
                                                  // causes creation of a set of
                                                  // acceptance states.

    virtual      class SCStream&   Display (class SCStream&) const;
                                                  // Output formula to stream.

    virtual            SCBoolean  operator== (const TLFormula&) const;
    virtual            SCBoolean  operator== (const TLFormula*) const;
    virtual            SCBoolean  operator!= (const TLFormula&) const;
    virtual            SCBoolean  operator!= (const TLFormula*) const;

                       TLLetter   Operator (void) const;

                       SCBoolean  SetAcceptanceSetNo (SCNatural);
                       SCNatural  GetAcceptanceSetNo (void) const;
                                                  // Give access to acceptance
                                                  // set.

 /*
 ************* static methods ****************
 */

                static void       Initialize (SCBoolean  partialRewrite,
                                              SCBoolean  simplifyFormulae);


  protected:

                                   TLFormula (void);
                                                  // Forbidden!

           TLLetter   op;                         // Identifies the operator
                                                  // of the formula. It is a
                                                  // TLLetter to simplify
                                                  // debugging.

           SCNatural  acceptanceSetNo;            // UNDEFINED_LISTINDEX if none
                                                  // given, else in the range
                                                  // [0..n]. This is the number
                                                  // of the acceptance set
                                                  // created by the formula.
                                                  // This number corresponds
                                                  // currently to a bit in a bit
                                                  // set. THIS MAY CHANGE, so
                                                  // don't rely on this to have a
                                                  // certain type!

    static SCBoolean partialRewrite;              // Do not rewrite formulae so
                                                  // that they only contain the
                                                  // basic operators U, V, X, !,
                                                  // &&, ||.

    static SCBoolean simplifyFormulae;            // When rewriting a formula, try
                                                  // to exploit some simple
                                                  // equivalences.
};

#if _TL_INLINING_
#include "TLFormula.inl.h"
#endif

class SCStream&  operator<< (class SCStream&, const TLFormula&);
class SCStream&  operator<< (class SCStream&, const TLFormula*);


#endif // _TLFORMULA_H_

 
