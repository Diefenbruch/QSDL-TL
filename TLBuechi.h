/* File:            TLBuechi.h
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef _TLBUECHI_H_
#define _TLBUECHI_H_

#include "TL.h"
#include "TLState.h"
#include "SCL/SCTable.h"

class TLBuechi
{
  public:
     TLBuechi (char*               phiStr,
               SCName2PropFuncPtr* name2func,
               SCNatural           numOfElems,
               SCBoolean           trueEquivEmpty = true,
               SCBoolean           nowIsPureAtomic = true,
               SCBoolean           nowDisplaysOnlyAtomics = true,
               SCBoolean           extendedAutomaton = true,
               SCBoolean           simplifyFormulae = true,
               SCBoolean           greedyAutomaton = true,
               SCBoolean           autoNegate = true);

    ~TLBuechi (void);

    class TLStateList* GetStateList (void) const; // Get the list of expanded
                                                  // states.

    class TLStateList* GetInitialStates (void) const;
                                                  // Get list of initial states.

          SCNatural    GetNumOfStates (void) const;
                                                  // Return the number of expanded
                                                  // States in list.

          SCBoolean    CreateGraph (void);        // No parameters, uses phi.

          SCBoolean    IsFulfillable (void) const;
                                                  // True, iff the automaton
                                                  // Contains at least one
                                                  // acceptance cycle.

          SCBoolean    IsAcceptingStutterState (TLState*) const;
                                                  // True iff there exists
                                                  // an accepting cycle in the
                                                  // poduct automaton
                                                  // where the system stutters
                                                  // and the buechi automaton
                                                  // advances normally.
                                                  // This is used to check
                                                  // whether a deadlock state
                                                  // fulfills the formula.
          
    const SCBitSet     GetReferenceAcceptanceSet (void) const;
                                                  // This will return the
                                                  // bitpattern with all bits
                                                  // of all existing acceptance
                                                  // sets set. By ANDing it with a
                                                  // given set S, one can determine
                                                  // whether S has all bits set.
                                                  // Unused bits are set to zero.
    class TLFormula*   GetOrigPhi (void) const;
    class TLFormula*   GetPhi (void) const;
          
          SCNatural    GetNumOfAcceptanceSets (void) const;
          
  protected:
    
    class TLStateList* Expand (class TLNode*, class TLStateList*);
                                                  // Execute the expansion
                                                  // algorithm and store the
                                                  // resulting states in state
                                                  // list.
    const                                              
    class TLFormulaSet* New1 (class TLFormula*);  // C.f. GPVW95, p.9

    const
    class TLFormulaSet* New2 (class TLFormula*);  // C.f. GPVW95, p.9

    const
    class TLFormulaSet* Next1 (class TLFormula*); // C.f. GPVW95, p.9

          SCBoolean     SetUpAcceptanceSet (TLFormula* phi);
                                                  // This sets the member
                                                  // TLFormula::acceptanceSetNo
                                                  // of all subformulae of phi
                                                  // including phi.
                                                  
          SCBoolean     Dfs1 (TLState*,
                              SCTable<TLState>&,
                              SCTable<TLState>&,
                              SCBoolean checkAtoms = false) const;
                                                  // If checkAtoms is true,
                                                  // only buechi states
                                                  // that are consistent with
                                                  // the current buechi state
                                                  // are explored. This is used
                                                  // during model checking,
                                                  // when a dead lock state
                                                  // is reached. Rather than
                                                  // simply backtracking
                                                  // we now check whether
                                                  // the formula is falsified
                                                  // by the deadlock.
          SCBoolean     Dfs2 (TLState*,
                              SCTable<TLState>&,
                              SCBitSet,
                              TLState*,
                              SCBoolean checkAtoms = false) const;


    class TLStateList*  stateList;                // List to store expanded
                                                  // states.
                                                  
    class TLStateList*  initialStates;            // List of initial states.
    
    class TLFormula*    phi;                      // The formula we are working
                                                  // with.
                                                  
    class TLFormula*    origPhi;                  // The original formula as
                                                  // constructed by the parser.

    class TLFormulaSet* acceptFormulae;           // Contains all subformulae
                                                  // of phi including phi, that
                                                  // have an associated
                                                  // aceptance state set.
    
    class TLFormulaSet* new1Set;                  // Use these to avoid memory leaks
                                                  // when returning values from
                                                  // New1, Next1 and New2!!!
    class TLFormulaSet* new2Set;
    class TLFormulaSet* next1Set;

          SCBitSet      referenceAcceptanceSet;   // Set containing all formulae that
                                                  // have an aceptance state set.
                                                  // Used by TLIndetVerify.
                                                  
    
          SCBoolean     trueEquivEmpty;           // Don´t insert true into a
                                                  // formulaset, as true is
                                                  // equivalent to nothing. Helps
                                                  // reducing the state space of
                                                  // the buechi automaton.
                                                  
          SCBoolean     nowIsPureAtomic;          // Don't display non atomic
                                                  // propositions in nowSet AND
                                                  // ignore them when comparing
                                                  // states or nodes and states.
                                                  // Do NOT ignore them when
                                                  // comparing nodes with nodes!!!
                                                  // The non atomic propositions
                                                  // are stored in nowSet
                                                  // however!
          
          SCBoolean     nowDisplaysOnlyAtomics;   // Do not display non atomic
                                                  // propositions in nowSet.
                                                  // Do NOT ignore them when
                                                  // doing comparisions between
                                                  // states and / or nodes!
          
          SCBoolean     extendedAutomaton;        // If true, the buechi automaton
                                                  // will be able to handle
                                                  // ALWAYS, NEXTTIME,
                                                  // WAITFOR and Z_OPER, so these
                                                  // don´t have to be rewritten.
          
          SCBoolean     greedyAutomaton;          // When traversing the graph
                                                  // try to reach an accepting
                                                  // state as quickly as
                                                  // possible.
          
          SCBoolean     autoNegate;               // Automatically negate the
                                                  // formula. During verification
                                                  // one exmaines the negation of
                                                  // the formula in question.
                                                  // Set this to false for internal
                                                  // testing.

          SCNatural     nextAcceptanceSetNo;      // Counter for acceptance state sets.
                                                  // Rather than storing all the states
                                                  // into an aceptance state set of 
                                                  // the formula, we assign each state
                                                  // a bit set with each bit representing
                                                  // membership in an acceptance state set.
                                                  // If bit n is set, then the state is
                                                  // a member of the nth acceptance state
                                                  // set. Each formula knows the number
                                                  // of its acceptance state set.
                                                  // This counter is used to guarantee
                                                  // a straight sequence of acceptance set
                                                  // number with no holes.
};

#if _TL_INLINING_
#include "TLBuechi.inl.h"
#endif // _TL_INLINING_

#endif // _TLBUECHI_H_
