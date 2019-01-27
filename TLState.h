/* File:            TLState.h
   Author:          Axel Hirche, Marc Diefenbruch
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef _TLSTATE_H_
#define _TLSTATE_H_

#include "TL.h"
#include "SCL/SCStream.h"

class TLNode;

class TLState
{
  friend class TLNode;
  friend class SCStream& operator<< (class SCStream&, TLState&);

  public:

    TLState (const TLState*);                     // Copy constructor.
    TLState (const TLState&);                     // Copy constructor.

    TLState (const TLNode*);                      // Create state from node.
    TLState (const TLNode&);

    TLState (class TLFormulaSet* NowSet,          // Set of formulae that have
                                                  // to be valid in this state.
             class TLFormulaSet* NextSet,         // Set of formulae, that have
                                                  // to be valid in the next
                                                  // state.
             class TLStateList  *inEdgesSet,      // List of incoming edges.
             class TLStateList  *outEdgesSet,     // List of outgoing egdes.
                   SCBitSet      acceptSets = 0ULL,
                                                  // Set containing all formulae, for
                                                  // which the state is an accepting
                                                  // state.
                   SCBoolean     init = false);   // Indicates whether state
                                                  // is an initial state.

    ~TLState (void);

    class TLFormulaSet* GetNow (void) const;
    class TLFormulaSet* GetNext (void) const;
          SCNatural     GetName (void) const;
          void          SetIsInitial (SCBoolean); // Make state an initial state.

          SCBoolean     IsInitial (void) const;   // Determine, whether state
                                                  // is initial.

    class TLStateList*  GetInEdges (void);
    class TLStateList*  GetOutEdges (void);

          SCBoolean     AddToIncoming (TLState*);
          SCBoolean     AddToOutgoing (TLState*);

          SCBoolean     MergeToIncoming (const class TLStateList& toMerge);
                                                  // Merge toMerge into inEdges
                                                  // as if the lists were sets, and
                                                  // insert this into outEdges
                                                  // of every state from toMerge
                                                  // that is added to this->inEdges.

          SCNatural     NumOfSuccessors (void) const;

          SCBoolean     NowIsValid (void) const;  // Evaluates all atomic
                                                  // propositions in nowSet and
                                                  // returns true, iff all of
                                                  // them evaluate to true.

          SCBoolean     IsAcceptingState (void) const;
                                                  // True, if *this is an
                                                  // accepting state, i.e.
                                                  // if acceptanceSets
                                                  // is non-empty.

          void          SetUpAcceptanceSets (TLFormulaSet* acceptSetPhiSet);
                                                  // This requires that nowSet
                                                  // contains ALL propositions
                                                  // not onyl the atomics.
                                                  // acceptSetPhiSet is a formula
                                                  // set containing all formulae
                                                  // that have an aceptance state
                                                  // set.

          SCBitSet      GetAcceptanceSets (void);

          SCBoolean     operator== (const TLState&) const;
          SCBoolean     operator== (const class TLNode&) const;
          SCBoolean     operator!= (const TLState&) const;
          SCBoolean     operator!= (const class TLNode&) const;


   static void          Initialize (SCBoolean pTrueEquivEmpty,
                                                  // {TRUE} == {}
                                    SCBoolean pNowIsPureAtomic,
                                                  // Restrict nowSet to
                                                  // atomic propositions
                                                  // thereby possibly reducing
                                                  // the number of generated
                                                  // states.
                                    SCBoolean pNowDisplaysOnlyAtomics,
                                                  // Do NOT restrict nowSet to
                                                  // atomic propositions but
                                                  // display only the atomic
                                                  // propositions in nowSet.
                                    SCBoolean pExtendedAutomaton,
                                                  // Extend the basic set of
                                                  // operators.
                                    SCBoolean pGreedyAutomaton);
                                                  // Try to advance to an
                                                  // accepting state as quickly as
                                                  // possible. This is a heuristic,
                                                  // that will help in determining
                                                  // the fulfillabilty of a
                                                  // formula, but may not help with
                                                  // the crossproduct automaton.
                                    
   static SCNatural     GetLastName (void);       // Return the last name used.
   static SCNatural     GetNextname (void);       // Return the next valid name and
                                                  // update counter.

          SCBoolean     isReallyAccepting;        // Use this to see whether a
                                                  // state is an accepting state
                                                  // because it fulfills a formula
                                                  // or just because no formula
                                                  // with acceptance state set is
                                                  // in nowSet.

  protected:
                         TLState (void);          // Standard constructor.
  
           SCBoolean     SetInEdges (class TLStateList* l);
           SCBoolean     SetOutEdges (class TLStateList* l);
          
     class TLFormulaSet* nowSet;
     class TLFormulaSet* nextSet;

    class  TLStateList*  inEdges;
    class  TLStateList*  outEdges;
    
           SCBoolean     isInitial;               // If true, the state is an
                                                  // initial state.
           SCNatural     name;
           SCBitSet      acceptanceSets;

   static  SCNatural     nextName;
   
   static  SCBoolean     trueEquivEmpty;
   static  SCBoolean     nowIsPureAtomic;
   static  SCBoolean     nowDisplaysOnlyAtomics;
   static  SCBoolean     extendedAutomaton;  
   static  SCBoolean     greedyAutomaton;
};

class SCStream& operator<< (class SCStream&, TLState&);
class SCStream& operator<< (class SCStream&, TLState*);

#if _TL_INLINING_
#include "TLState.inl.h"
#endif // _TL_INLINING_

#endif // _TLSTATE_H_
