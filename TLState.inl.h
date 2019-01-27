/*
 * File:    TLState.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */


#ifndef _TLSTATE_INL_H_
#define _TLSTATE_INL_H_

#include "TLFormula.h"
#include "TLFormulaAtomic.h"
#include "TLFormulaUnary.h"
#include "TLFormulaBinary.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaZ_OPER.h"
#include "TLFormulaSet.h"
#include "TLHelp.h"
#include "TLNode.h"

#include "SCL/SCListIter.h"

/******************** Constructor: *********************/

TLINLINE TLState::TLState (TLFormulaSet* pNowSet,
                           TLFormulaSet* pNextSet,
                           TLStateList*  pInEdges,
                           TLStateList*  pOutEdges,
                           SCBitSet      pAcceptSets,
                           SCBoolean     pInit)
  : nowSet (pNowSet),
    nextSet (pNextSet),
    inEdges (pInEdges),
    outEdges (pOutEdges),
    isInitial (pInit),
    acceptanceSets (pAcceptSets)
{
  assert (nowSet);
  assert (nextSet);
  assert (inEdges);
  assert (outEdges);
  name = nextName++;
}


/******************** Constructor: *********************/

TLINLINE TLState::TLState (const TLState* s)
:  isInitial (s->isInitial)
{
  assert (s->nowSet);
  assert (s->nextSet);
  assert (s->inEdges);
  assert (s->outEdges);
  
  nowSet = new TLFormulaSet (s->nowSet);
  assert (nowSet);  
  
  nextSet = new TLFormulaSet (s->nextSet);
  assert (nextSet);  
  
  inEdges = new TLStateList (s->inEdges);
  assert (inEdges);
  
  outEdges = new TLStateList (s->outEdges);
  assert (outEdges);
  
  acceptanceSets = s->acceptanceSets;
  
  name = nextName++;                              // Update class member.
}


/******************** Constructor: *********************/

TLINLINE TLState::TLState (const TLState& s)
:  isInitial (s.isInitial)
{
  assert (s.nowSet);
  assert (s.nextSet);
  assert (s.inEdges);
  assert (s.outEdges);
  
  nowSet = new TLFormulaSet (s.nowSet);
  assert (nowSet);  
  
  nextSet = new TLFormulaSet (s.nextSet);
  assert (nextSet);  
  
  inEdges = new TLStateList (s.inEdges);
  assert (inEdges);

  outEdges = new TLStateList (s.outEdges);
  assert (outEdges);

  acceptanceSets = s.acceptanceSets;

  name = nextName++;                              // Update class member!
}


/******************** Constructor: *********************/

TLINLINE TLState::TLState (const TLNode* n)
:  isInitial (n->IsInitial())
{
  assert (((TLNode*) n)->GetNow());
  assert (((TLNode*) n)->GetNext());
  
  nowSet = new TLFormulaSet (((TLNode*) n)->GetNow());
  assert (nowSet);  
  
  nextSet = new TLFormulaSet (((TLNode*) n)->GetNext());
  assert (nextSet);  
  
  inEdges = new TLStateList();
  assert (inEdges);

  outEdges = new TLStateList();
  assert (outEdges);

  acceptanceSets = 0ULL;

  name = nextName++;                              // Update class member!
}


/******************** Constructor: *********************/

TLINLINE TLState::TLState (const TLNode& n)
:  isInitial (n.IsInitial())
{
  nowSet = new TLFormulaSet (((TLNode&) n).GetNow());
  assert (nowSet);  
  
  nextSet = new TLFormulaSet (((TLNode&) n).GetNext());
  assert (nextSet);  
  
  inEdges = new TLStateList();
  assert (inEdges);

  outEdges = new TLStateList();
  assert (outEdges);

  acceptanceSets = 0ULL;

  name = nextName++;                              // Update class member!
}


/******************** Destructor: *********************/

TLINLINE TLState::~TLState (void)
{
  assert (inEdges);
  delete inEdges;
  inEdges = NULL;
  
  assert (outEdges);
  delete outEdges;
  outEdges = NULL;

  assert (nowSet);
  delete nowSet;
  nowSet = NULL;
  
  assert (nextSet);
  delete nextSet;
  nextSet = NULL;

  isInitial = false;

  name = 0;
  acceptanceSets = 0ULL;
}


TLINLINE TLFormulaSet* TLState::GetNow (void) const
{
  assert (nowSet);
  return nowSet;
}


TLINLINE TLFormulaSet* TLState::GetNext (void) const
{
  assert (nextSet);
  return nextSet;
}


TLINLINE SCNatural TLState::GetName (void) const
{
  return name;
}


TLINLINE void TLState::SetIsInitial (SCBoolean v)
{
  isInitial = v;
}


TLINLINE SCBoolean TLState::IsInitial (void) const
{
  return isInitial;
}


TLINLINE TLStateList* TLState::GetInEdges (void)
{
  assert (inEdges);
  return inEdges;
}


TLINLINE TLStateList* TLState::GetOutEdges (void)
{
  assert (outEdges);
  return outEdges;
}


TLINLINE SCBoolean TLState::SetInEdges (class TLStateList* l)
{
  if (inEdges)
    delete inEdges;
    
  inEdges = l;
  return true;
}


TLINLINE SCBoolean TLState::SetOutEdges (class TLStateList* l)
{
  if (outEdges)
    delete outEdges;
    
  outEdges = l;
  return true;
}


TLINLINE SCBoolean TLState::AddToIncoming (TLState* s)
{
  if (   (*this == *s)                            // Self reference and
      && (IsAcceptingState())                     // current state is accepting and
      && greedyAutomaton)                         // greedy choice of transitions
  {
    return inEdges->Prepend (s);                  // Prepend to have greedy automaton.
  }
  else
  {
    return inEdges->Append (s);                   // Append to have fcfs order
                                                  // of outgoing transitions.
  }
}


TLINLINE SCBoolean TLState::AddToOutgoing (TLState* s)
{
  if (   (*this == *s)                            // Self reference and
      && (IsAcceptingState())                     // current state is accepting and
      && greedyAutomaton)                         // greedy choice of transitions.
  {
    return outEdges->Prepend (s);                 // Prepend to have greedy automaton.
  }
  else
  {
    return outEdges->Append (s);                  // Append to have fcfs order
                                                  // of outgoing transitions.
  }
}


TLINLINE SCBoolean TLState::MergeToIncoming (const TLStateList& toMerge)
                                                  // Merges toMerge into
                                                  // this->inEdges as if the two lists
                                                  // were sets. *this is added
                                                  // to outEdges of every state
                                                  // that is merged to this->inEdges.
{
  SCListIter<TLState> toMergeIter ((TLStateList&) toMerge);
                                                  // Iterator over toMerge.
  TLState* curToAddState;                         // Current state of toMerge.
  SCNatural i;                      
  
  for (i = 0; i < toMerge.NumOfElems(); i++)      // Cycle through all elements.
  {
    curToAddState = toMergeIter++;                // Get current state of toMerge.
    assert (curToAddState);
    
    if (AddToIncoming (curToAddState))            // The state was inserted. If
                                                  // false is returned, the state
                                                  // is already in this->inEdges
    {
      curToAddState->AddToOutgoing(this);     // Add *this to 
                                                  // curToAddState->outEdges
                                                  // to update the reverse direction
                                                  // of the link between states.
    }
  }

  return true;
}


TLINLINE SCNatural TLState::NumOfSuccessors (void) const
{
  assert (outEdges);
  return outEdges->NumOfElems();
}


TLINLINE SCBoolean TLState::NowIsValid (void) const
{
  return nowSet->IsValid();
}


TLINLINE SCBoolean TLState::IsAcceptingState (void) const
{
  return acceptanceSets != 0ULL;                  // A state is an accepting
                                                  // state if it is a member of
                                                  // some acceptance state set.
}


TLINLINE void TLState::SetUpAcceptanceSets (TLFormulaSet* acceptPhiSet)
                                                  // A state is a member of the acceptance state
                                                  // set of a formula phi iff
                                                  // (a) phi is in nowSet and nowSet fulfills phi.
                                                  //     Note that the presence of phi in nowSet is
                                                  //     not sufficient, whereas the presence of
                                                  //     the fulfilling subformualae of phi (see below)
                                                  //     is necessary and sufficient. A formula phi
                                                  //     is fulfilled by the current state iff
                                                  //     1) phi = a U b and b in nowSet
                                                  //     2) phi = <> a and a in nowSet
                                                  //     3) phi = a Z b and a, b in nowSet
                                                  //     Only formulae of the types listed above
                                                  //     have acceptance state sets.
                                                  //
                                                  // (b) phi is NOT an element of nowSet.
{
  SCListIter<TLFormula> acceptPhiIter (*((TLFormulaSet*) acceptPhiSet));
  TLFormula* tmpPhi;
  
  assert (nowSet);
  
  acceptanceSets = 0ULL;                          // Make sure the set is empty.
  
  for (SCNatural i = 0; i < acceptPhiSet->NumOfElems(); i++)
  {
    tmpPhi = acceptPhiIter++;
    assert (tmpPhi);
    
    if (nowSet->IsElem(tmpPhi))
    {
      switch (tmpPhi->Operator())
      {
        case UNTIL:
          if (nowSet->IsElem(((TLFormulaUNTIL*) tmpPhi)->RightOperand()))
          {
            assert (tmpPhi->GetAcceptanceSetNo() != UNDEFINED_LISTINDEX);
            acceptanceSets |= (1ULL << tmpPhi->GetAcceptanceSetNo());
                                                  // Set apropriate bit.
            isReallyAccepting = true;
          }
          break;

        case EVENTUALLY:
          if (nowSet->IsElem(((TLFormulaEVENTUALLY*) tmpPhi)->RightOperand()))
          {
            assert (tmpPhi->GetAcceptanceSetNo() != UNDEFINED_LISTINDEX);
            acceptanceSets |= (1ULL << tmpPhi->GetAcceptanceSetNo());
            isReallyAccepting = true;
          }
          break;
          
        case Z_OPER:
          if (nowSet->IsElem(((TLFormulaZ_OPER*) tmpPhi)->LeftOperand()) &&
              nowSet->IsElem(((TLFormulaZ_OPER*) tmpPhi)->RightOperand()))
          {
            acceptanceSets |= (1ULL << tmpPhi->GetAcceptanceSetNo());
            isReallyAccepting = true;
          }
          break;
          
        default:
          assert (false);                         // Should not be here...
          break;
       }
    }
    else
    {
      acceptanceSets |= (1ULL << tmpPhi->GetAcceptanceSetNo());
      isReallyAccepting = false;
    }
  }
}


TLINLINE SCBitSet TLState::GetAcceptanceSets (void)
{
  return acceptanceSets;
}


TLINLINE void TLState::Initialize (SCBoolean pTrueEquivEmpty,
                                   SCBoolean pNowIsPureAtomic,
                                   SCBoolean pNowDisplaysOnlyAtomics,
                                   SCBoolean pExtendedAutomaton,
                                   SCBoolean pGreedyAutomaton)
{
  trueEquivEmpty = pTrueEquivEmpty;
  nowIsPureAtomic = pNowIsPureAtomic;
  nowDisplaysOnlyAtomics = pNowDisplaysOnlyAtomics;
  extendedAutomaton = pExtendedAutomaton;
  greedyAutomaton = pGreedyAutomaton;
}


TLINLINE SCNatural TLState::GetLastName (void)
{
  if (nextName)
    return nextName - 1;
  else
    return 0;
}


TLINLINE SCNatural TLState::GetNextname (void)
{
  return nextName++;
}


TLINLINE SCBoolean TLState::operator== (const TLState& s2) const
{
  if (TLState::nowIsPureAtomic)
  {
    SCBoolean retVal;
    TLFormulaSet* s1Atomics = nowSet->GetAllAtomics();
    TLFormulaSet* s2Atomics = s2.nowSet->GetAllAtomics();
    
    retVal = (*s1Atomics == *s2Atomics)           // Ignore non atmomics!!!
             && (*nextSet == *s2.nextSet);
             
    delete s1Atomics;
    delete s2Atomics;
    
    return retVal;
  }
  else
  {
    return (*nowSet == *s2.nowSet)
            && (*nextSet == *s2.nextSet);
  }
}


TLINLINE SCBoolean TLState::operator== (const TLNode& n1) const
{
  return n1 == *this;
}


TLINLINE SCBoolean TLState::operator!= (const TLState& s1) const
{
  return !(*this == s1);
}


TLINLINE SCBoolean TLState::operator!= (const TLNode& n1) const
{
  return !(n1 == *this);
}


TLINLINE SCStream& operator<< (SCStream& out, TLState& s)
{
  out << "--- TLState: ---" << std::endl;
  out << "name == " << s.name << std::endl;
  
  if (TLState::nowDisplaysOnlyAtomics)
  {
    TLFormulaSet* sAtomics = s.GetNow()->GetAllAtomics();
    out << "nowSet == " << sAtomics << std::endl;
    delete sAtomics;
  }
  else
  {
    out << "nowSet == " << s.nowSet << std::endl;
  }
  
  out << "nextSet == " << s.nextSet << std::endl;
  if (s.IsAcceptingState())
  {
    out << "Accepting state." << std::endl;
  }
  
  if (s.isInitial)
    out << "Initial state." << std::endl;
  
  if (s.inEdges->NumOfElems())
  {
    out << s.inEdges->NumOfElems() << " incoming edges: ";
    out << s.inEdges << std::endl;
  }
  else
    out << "No incoming edges." << std::endl;

  if (s.outEdges->NumOfElems())
  {
    out << s.outEdges->NumOfElems() << " outgoing edges: ";
    out << s.outEdges << std::endl;
  }
  else
    out << "No outgoing edges." << std::endl; 
  
  out << "acceptanceSets == ";
  ShowBits (out, s.acceptanceSets);
  out << std::endl;
  
  out << std::endl << "----------------" << std::endl;
  return out;
}

TLINLINE SCStream& operator<< (SCStream& out, TLState* s)
{
  return out << *s;
}

#endif // _TLSTATE_INL_H_
