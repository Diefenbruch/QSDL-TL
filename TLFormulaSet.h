/* File:            TLFormulaSet.h
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef _TL_FORMULASET_H_
#define _TL_FORMULASET_H_

#include "TL.h"
#include "SCL/SCList.h"
#include "TLFormula.h"


class TLFormulaSet : public SCList<TLFormula>
{
  friend class SCStream& operator<< (class SCStream& out, const TLFormulaSet& set);

  public:
                    TLFormulaSet (void);          // Create empty set.

                    TLFormulaSet (const TLFormulaSet*);
                                                  // Create a copy.

                    TLFormulaSet (const TLFormula* phi);
                                                  // Create set with phi as sole
                                                  // element.

                   ~TLFormulaSet (void);

    class
    SCStream&        Display (class SCStream&) const;
                                                  // Have to do redefine this
                                                  // to avoid clashes with
                                                  // SCList... 

    TLFormulaSet&   operator= (const TLFormulaSet&);
                                                  // assignment from set.

    TLFormulaSet&   operator= (const TLFormula*); // assignment from formula.

    TLFormulaSet&   operator+= (const TLFormulaSet&);
                                                  // union

    TLFormulaSet&   operator-= (const TLFormulaSet&);
                                                  // difference

    TLFormulaSet&   operator*= (const TLFormulaSet&);
                                                  // intersection

    TLFormulaSet&   operator+= (const TLFormula*);
                                                  // union assignment

    TLFormulaSet&   operator-= (const TLFormula*);
                                                  // difference assignment

    SCBoolean       Insert (const TLFormula*);    // true, if phi actually was inserted,
                                                  // false otherwise.

    SCBoolean       IsSubset  (const TLFormulaSet&);
                                                  // subset test

    SCBoolean       IsElem    (const TLFormula*) const;
                                                  // element test

    TLFormula*      FindMatch (const TLFormula* toMatch) const;
                                                  // Return the element with
                                                  // TLFormula::operator== (*FindMatch(toMatch), *toMatch)
                                                  // equal to true.
                                                  // FindMatch(toMatch) == toMatch
                                                  // is normally NOT true!!!
        
    SCBoolean       operator== (const TLFormulaSet&) const;
                                                  // Equality test.
    
    SCBoolean       operator!= (const TLFormulaSet&) const;
                                                  // Inequality test.
    
    SCNatural       NumOfElems (void) const;      // number of elements in set.
    
    SCNatural       NumOfAtomics (void) const;    // number of atomic
                                                  // propositions in set.
                                                  
    TLFormula*      ExtractAny (void);            // Extract some formula from
                                                  // the set.
                                                  
    TLFormula*      ExtractAtomic (void);         // Extract some atomic formula
                                                  // from the set.
                                                  
    TLFormulaSet*   GetAllAtomics (void) const;   // Get subset with all
                                                  // atomic propositions.
                                                  
    SCBoolean       IsEmpty (void) const;         // Test emptyness of set.

    SCBoolean       IsValid (void) const;         // Check if all atomic
                                                  // props evaluate to TRUE.
    
    void            RemoveAllElements (void);

    static
    void            Initialize (SCBoolean  trueEquivEmpty,
                                SCBoolean  nowIsPureAtomic,
                                SCBoolean  extendedAutomaton);
    static
    TLFormula*      GetTRUEPhi (void);

    static
    TLFormula*      GetFALSEPhi (void);           // Formula sets only store
                                                  // references, i.e. do not
                                                  // dispose of their elements.
                                                  // If we have to create a TRUE
                                                  // or FALSE on the fly during
                                                  // expansion, we use a
                                                  // reference to a global static
                                                  // object to avoid memory leaks.
    
#if _TL_DEBUG_ > 4
    void            CheckMe (void) const;         // Do some internal error
                                                  // checkig and bail out
                                                  // if any are found.
#endif

    
  protected:
  
    void            InsertBefore (const TLFormula*             toInsert,
                                  class SCListCons<TLFormula>* where = NULL);

    void            InsertAfter (const TLFormula*             toInsert,
                                 class SCListCons<TLFormula>* where = NULL);

    TLFormula*      Remove (const TLFormula* toKill);
    
#if _TL_DEBUG_ > 4
          SCBoolean    deleted;                  // destructor sets this to true.
#endif

           SCNatural    numOfAtomics;             // Number of Atomic
                                                  // propositions in a formula
                                                  // set.
    static SCBoolean      trueEquivEmpty;
    static SCBoolean      nowIsPureAtomic;
    static SCBoolean      extendedAutomaton;
    
    static class TLFormulaTRUE  truePhi;
    static class TLFormulaFALSE falsePhi;
};

class SCStream& operator<< (class SCStream& out, const TLFormulaSet& set);
class SCStream& operator<< (class SCStream& out, const TLFormulaSet* set);

#if _TL_INLINING_
#include "TLFormulaSet.inl.h"
#endif // _TL_INLINING_


#endif // _TL_FORMULASET_H_
