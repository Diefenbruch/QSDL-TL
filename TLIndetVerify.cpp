/* File:            TLIndetVerify.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998, University of Essen, Germany
*/

#include <sys/times.h>

#include "SCL/SCStream.h"
#include "SCL/SCStack.h"
#include "SCL/SCStackElem.h"
#include "SCL/SCStateSpace.h"
#include "SCL/SCMem.h"
#include "SCL/SCRunnable.h"
#include "SCL/SCScheduler.h"

#include "TLFormula.h"
#include "TLState.h"
#include "TLStateList.h"
#include "TLBuechi.h"
#include "TLIndetVerify.h"

#include "SCL/SCDebug.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _SC_NOINLINES
  #include "TLIndetVerify.inl.h"
#endif

TLIndetVerify::TLIndetVerify (char*               pPhiStr,
                                                  // Formula as c-string
                              SCName2PropFuncPtr* pName2Func,
                                                  // Translation table atomic prop
                                                  // to prop function
                              SCNatural           pNumOfElems,
                                                  // number of elements in
                                                  // translation table.
                              SCTime              pStopTime,
                              SCBoolean           pFindErrors,
                              SCNatural           pMaxErrors,
                              SCBoolean           pDeadCode,
                              SCStateSpace *      stateSpace,
                              SCStateSpace *      cycleStateSpace,
                              SCNatural           pMaxVerifyDepth,
                              SCName2PropFuncPtr *bAtom,
                              SCBoolean           pTrueEquivEmpty,
                                                  // treat {TRUE} as {}
                              SCBoolean           pNowIsPureAtomic,
                                                  // restrict nowSet to atomic
                                                  // props
                              SCBoolean           pNowDisplaysOnlyAtomics,
                                                  // Only display atokic props
                                                  // of nowSet.
                              SCBoolean           pExtendedAutomaton,
                                                  // Do not rewrite <>, [], W, Z.
                              SCBoolean           pSimplifyFormulae,
                                                  // Apply some simple equivalence
                                                  // transformations to phi.
                              SCBoolean           pGreedyAutomaton,
                                                  // Make buechi automate advance
                                                  // to accepting states as
                                                  // quickly as possible.
                              SCBoolean           pAutoNegate)
                                                  // Automaticall prepend a ~
                                                  // to the formula.
  : SCIndetVal(pStopTime,
               true,
               pMaxErrors,
               pDeadCode,
               true,                 // cycle detection, MD 22.04.97
               stateSpace,
               cycleStateSpace,
               pMaxVerifyDepth,
               kSCMaxCreatedInstances,
               bAtom,
               scIndetVerification),
     nextInitialBuechiState (0),
     currentBuechiState (NULL)
{
  (void) pFindErrors;                             // Keep gcc happy...
  
  buechi = new TLBuechi (pPhiStr,
                         pName2Func,
                         pNumOfElems,
                         pTrueEquivEmpty,
                         pNowIsPureAtomic,
                         pNowDisplaysOnlyAtomics,
                         pExtendedAutomaton,
                         pSimplifyFormulae,
                         pGreedyAutomaton,
                         pAutoNegate);
  assert(buechi);                                 // We can't set
                                                  // currentBuechiState here
                                                  // as the automaton might be
                                                  // empty. In this case we
                                                  // couldn't take proper action as
                                                  // we are running in a
                                                  // constructor with no return
                                                  // value.
                                                  // HERE: This is useless. We
                                                  // have to raise an exception!!!
  
}


TLIndetVerify::~TLIndetVerify (void)
{
  delete buechi;
}


SCRunnable* TLIndetVerify::ChooseRunnable (SCTimeEventSaveList *activeQueue)
{
  SCRunnable* tmpRunnable = NULL;

  if (   currentBuechiState == NULL
      && buechi->GetInitialStates()->NumOfElems() == 0)
  {
    return NULL;                                  // If the automaton is empty
                                                  // force stop of verification.
  }

next:  

  tmpRunnable = SCIndetVal::ChooseRunnable (activeQueue);
                                                  // This implies a call to
                                                  // TLIndetVerify::IsLimitingState
                                                  // which will set
                                                  // currentBuechiState.
    
  if (tmpRunnable)                                // Not end of verification.
  {
    assert (currentBuechiState);
    
    if (buechi->GetReferenceAcceptanceSet())
    {
      fulfilledAcceptanceSets |= currentBuechiState->GetAcceptanceSets();
                                                  // Update fulfilledAcceptanceSets.
      if (fulfilledAcceptanceSets == buechi->GetReferenceAcceptanceSet())
      {
        fulfilledAcceptanceSets = SC_BS0;         // If all bits are set, set to
                                                  // zero to simulate "modulo count"
        flipCounter++;
      }
    }
    
    return tmpRunnable;
  }
  else                                            // Exploration of current
                                                  // initial buechi
                                                  // start state is done.
  {
    assert(buechi);
    assert(buechi->GetInitialStates());
    
#if _SC_VERIFICATION_DEBUG
    scVerificationDebugLog << "TLIndetVerify::ChooseRunnable(): ";
    scVerificationDebugLog << "exploration of initial buechi state ";
    scVerificationDebugLog << (*buechi->GetInitialStates())[nextInitialBuechiState]->GetName();
    scVerificationDebugLog << " complete." << endl;
    scVerificationDebugLog.GetStream().flush();
#endif

    if (nextInitialBuechiState < buechi->GetInitialStates()->NumOfElems() - 1)
                                          // There are initial buechi states left.
    {
      currentBuechiState = NULL;
      nextInitialBuechiState++;

#if _SC_VERIFICATION_DEBUG
      scVerificationDebugLog << "TLIndetVerify::ChooseRunnable(): ";
      scVerificationDebugLog << "exploring next initial buechi state ";
      scVerificationDebugLog << (*buechi->GetInitialStates())[nextInitialBuechiState]->GetName() << endl;
#endif

      goto next;
    }
    else
    {
#if _SC_VERIFICATION_DEBUG 
      scVerificationDebugLog << "TLIndetVerify::ChooseRunnable(): ";
      scVerificationDebugLog << "all initial buechi states explored." << endl;
      scVerificationDebugLog << "TLIndetVerify::ChooseRunnable(): verification ending!" << endl;
#endif

      return NULL;
    }
  }
  
  assert (false);
}


SCErrorCode TLIndetVerify::IsErrorState (SCTimeEventSaveList *activeQueue)
{
  SCErrorCode tmpResult = SCIndetVal::IsErrorState (activeQueue);
  
  if (tmpResult == scErrorDeadlock)               // We have reached a deadlock
                                                  // state.
  {
    assert (lastError == scErrorDeadlock);
    if (buechi->IsAcceptingStutterState (currentBuechiState))
                                                  // There is an accepting
                                                  // sequence of the product
                                                  // automaton, where the
                                                  // system stutters and the
                                                  // buechi automaton
                                                  // advances.
    {
      return lastError = scErrorCycleDetected;    // This implies we have
                                                  // an accepting cycle,
                                                  // i.e. the original
                                                  // formula is invalid.
    }
  }
  
  return tmpResult;
}


SCBoolean TLIndetVerify::IsLimitingState (SCTimeEventSaveList *activeQueue)
{
  SCNatural nextSuccessorID = (SCNatural) -1;     // This will definitely be out
                                                  // out of bounds!
  //
  // 1. Execute Buechi-Transition
  //
  
  if (!currentBuechiState)                        // None chosen yet.
  {                                               // Only true for initial states.
    assert (buechi);
    assert(buechi->GetInitialStates());
    
    currentBuechiState = (*buechi->GetInitialStates())[nextInitialBuechiState];

#if _SC_VERIFICATION_DEBUG 
    scVerificationDebugLog << "TLIndetVerify::IsLimitingState():";
    scVerificationDebugLog << " buechi state is not yet set." << endl;
    scVerificationDebugLog << "TLIndetVerify::IsLimitingState():";
    scVerificationDebugLog << " using initial buechi state ";
    scVerificationDebugLog << currentBuechiState->GetName() << endl;
#endif
  }
  else
  {
    nextSuccessorID = GetLastSuccessor() - 1; // used as array index 

#if _SC_VERIFICATION_DEBUG 
    scVerificationDebugLog << "TLIndetVerify::IsLimitingState():";
    scVerificationDebugLog << " choosing buechi successor ";
    scVerificationDebugLog << nextSuccessorID + 1 << endl;
#endif

    assert (nextSuccessorID < currentBuechiState->GetOutEdges()->NumOfElems());
    currentBuechiState = (*currentBuechiState->GetOutEdges())[nextSuccessorID];

#if _SC_VERIFICATION_DEBUG 
    scVerificationDebugLog << "TLIndetVerify::IsLimitingState():";
    scVerificationDebugLog << " entering buechi state ";
    scVerificationDebugLog << currentBuechiState->GetName() << endl;
#endif

  }

  assert (currentBuechiState);

  //
  // 2. test if current Buechi state is consistent with system state
  //
  if (currentBuechiState->NowIsValid())    // Reached system state is consistent
                                           // with current buechi state?
  {
    return SCIndetVal::IsLimitingState(activeQueue);
  }
  else // reached inconsistent state, we must backtrack now!
  {
#if _SC_VERIFICATION_DEBUG 
    scVerificationDebugLog << "TLIndetVerify::IsLimitingState(): buechi state ";
    scVerificationDebugLog << currentBuechiState->GetName();
    scVerificationDebugLog << " is inconsistent with system state!" << endl;
#endif

    return true;
  }
}


SCBoolean TLIndetVerify::IsCycleStartState (void) const
{
  SCBoolean accepting;
  
  assert(currentBuechiState);
  
  accepting =  ((buechi->GetReferenceAcceptanceSet() == SC_BS0) ||
                ((currentBuechiState->IsAcceptingState())
            && (fulfilledAcceptanceSets == SC_BS0)));
                                                  // We have to check for two
                                                  // conditions:
                                                  // a) the state is in some
                                                  //    acceptance state set, and
                                                  // b) the value of the
                                                  //    "counter" (c.f. GPVW95)
                                                  //    fulfilledAcceptanceSets
                                                  //    is zero.
                                                  // Note that this check has to
                                                  // be done BEFORE
                                                  // fulfilledAcceptanceSets
                                                  // is updated!!
                                                  // The value of zero is
                                                  // arbitraily chosen. We
                                                  // could use any bitpattern for
                                                  // fulfilledAcceptanceSets.

#if _SC_VERIFICATION_DEBUG
  if (accepting)
  { 
    scVerificationDebugLog << "TLIndetVerify::IsCycleStartState(): buechi state ";
    scVerificationDebugLog << currentBuechiState->GetName();
    scVerificationDebugLog << " is an accepting state! -> starting cycle detection!" << endl;
  }
#endif

  return accepting;
}


SCBoolean TLIndetVerify::IsCycleEndState (SCMem * state)
{
  SCStackElem* cycleClosingElem = NULL;
  SCStackElem* cycleStartElem = NULL;
  SCBitSet     storedSets;    
  SCBitSet     refBits;
  SCBitSet     currentBits;
  SCBitSet     dfs1Bits;
  SCBitSet     fulfilledBits;
  SCBitSet     missingBits;
  
  if (!SCIndetVal::IsCycleEndState(state))        // Check if we reached a state
                                                  // on the DFS1 stack.
  {
    return false;                                 // If not, this state does not
                                                  // close a cycle.
  }
  
  if (buechi->GetReferenceAcceptanceSet() == SC_BS0)
  {
    return true;                                  // Formula does not impose any
                                                  // acceptance conditions,
                                                  // hence ANY cycle is accepting.
  }

  cycleClosingElem = GetCycleClosingElem();       // At this point we know that
                                                  // the state is on the stack
                                                  // of DFS1 and that DFS2 found
                                                  // a cycle.
                                                  // We have yet to see whether it
                                                  // is an accepting cycle.
  assert (cycleClosingElem);

  cycleStartElem = GetSecondStack()->Root();      // Retrieve start element of
                                                  // DFS2.
  assert(cycleStartElem);

  if (flipCounter > cycleStartElem->GetFlipCounter())
                                                  // Is there a flip on the
                                                  // stack of DFS1?
  {
    return true;
  }

  //
  // Set up some shorthands for better readability...
  //
  
  storedSets = cycleClosingElem->GetFulfilledAcceptanceSets();
                                                // Set of acceptance state
                                                // sets that so far have
                                                // states on DFS1 stack.

  refBits = buechi->GetReferenceAcceptanceSet();
                                                // Short hand for reference
                                                // bit set.

  currentBits = fulfilledAcceptanceSets;
                                                // Shorthand for the
                                                // acceptance state sets that
                                                // have states in the sequence
                                                // generated by DFS2.

  // we must test now if the bits of the cycle closing state
  // are the same as the bits of the cycle start
  // state (i.e. both are zero) or not:

  if (storedSets != SC_BS0)                     // Bits of cycle closing
  {                                             // state are not zero?
    dfs1Bits = storedSets ^ refBits;            // These are the aceptance
                                                // sets, that have states in
                                                // the sequence from the current
                                                // state to the starting point of
                                                // DFS2. ^ = XOR !?
    fulfilledBits = dfs1Bits | currentBits;
                                                // dfs1Bits | currentBits are
                                                // the acceptance state sets
                                                // that are fulfilled by the
                                                // whole cycle.

    missingBits = (~fulfilledBits) & refBits;   // These are the acceptance
                                                // state sets that have no states
                                                // in the whole cycle.

                                                // represented -> not accepting.
    if (missingBits == SC_BS0)                  // No set missing, so...
    {
      return true;                              // ...we have buechi acceptance.
    }

    return false;                               // Some sets are not
                                                // represented, hence no acceptance.
  }

  if (cycleStartElem->GetFlipCounter() > 
      cycleClosingElem->GetFlipCounter())       // Bothe sets are zero. We do
                                                // not know, whether the
                                                // sequence from the cycle closing
                                                // state to the cycle start state
                                                // conatins a flip. Is there a
                                                // flip?
  {
    return true;                                // YES, so we have acceptance!
  }


  return false;                                 // Too bad, no acceptance...
  
}


SCNatural TLIndetVerify::NumOfSuccessors (void) const
{
  return currentBuechiState->NumOfSuccessors();
}


void TLIndetVerify::SystemStateSize(SCSize *size) const
{
  assert(size);

  SCIndetVal::SystemStateSize(size);
  size->size += sizeof (SCNatural);               // Store ID (name) of state to ensure
                                                  // reproducability of hashing. Don't
                                                  // need this later on.
  size->historySize += sizeof (TLState*);         // Store tis for convenience. Restore it
                                                  // to do backtracking in buechi
                                                  // automaton.
  size->size += sizeof (SCNatural);               // nextInitialBuechiState
}


SCBoolean TLIndetVerify::StoreSystemState(SCMem *state) const
{
  SCNatural stateID;
      
  if (!SCIndetVal::StoreSystemState(state))
    return false;

  stateID = currentBuechiState->GetName();
  state->Store(&stateID, sizeof(SCNatural));
  state->HistoryStore(&currentBuechiState, sizeof (TLState*));
  state->Store(&nextInitialBuechiState, sizeof(SCNatural));
  
  return true;
}


SCBoolean TLIndetVerify::RestoreSystemState(SCMem *state) const
{  
  SCNatural stateID;
  SCNatural dummy;

  if (!SCIndetVal::RestoreSystemState(state))
    return false;
  
  state->Restore(&stateID, sizeof(SCNatural));
  state->HistoryRestore(&currentBuechiState, sizeof (TLState*));
  state->Restore(&dummy, sizeof(SCNatural));      // nextInitialBuechiState
                                                  // Why is this restored to a dummy???
  
  return true;
}


void TLIndetVerify::StartMessage (void)
{
  SCScheduler::outputStream << *this;
}


void TLIndetVerify::EndMessage (void)
{
  SCScheduler::outputStream << *this;
}


SCBoolean TLIndetVerify::IsFulFillable (void) const
{
  return buechi->IsFulfillable();
}


SCStream& operator<< (SCStream& pStream,
                      const TLIndetVerify& pData)
{
  return pData.Display(pStream); // virtuelle Funktion aufrufen
}


SCStream& TLIndetVerify::Display (SCStream& pStream) const
{
  SCNatural numOfTrans = 0;
  SCListIter<TLState> iter (*buechi->GetStateList());
  TLState* state;

  if (!SCScheduler::IsShuttingDown()) // called for start message?
  {
    if (type == scIndetVerification)
    {
      pStream << std::endl << "This is QVERIFY version ";
      pStream << SCL_VERIFIER_VERSION << std::endl << std::endl;
    }

    SCIndetVal::Display(pStream);
    pStream << "Checking requirement:       " << *buechi->GetOrigPhi() << std::endl;
    pStream << "Negated requirement:        " << *buechi->GetPhi() << std::endl;

    pStream << "Buechi states:              " << buechi->GetStateList()->NumOfElems() << std::endl;
    pStream << "Buechi start states:        " << buechi->GetInitialStates()->NumOfElems() << std::endl;

    for (state = iter++;
         state;
         state = iter++)
    {
      numOfTrans += state->GetOutEdges()->NumOfElems();
    }
    pStream << "Buechi transitions:         " << numOfTrans << std::endl;

    pStream << "Buechi acceptance sets:     " << (unsigned int) buechi->GetNumOfAcceptanceSets() << std::endl;

    if (type == scIndetVerification)
    {
      pStream << std::endl;                            // WANN IST DAS NICHT DER FALL
    }
  }
  else  // called for end message!
  {
    if (type == scIndetVerification)
    {
      pStream << std::endl << "Verifier ";
    }

    SCIndetVal::Display(pStream);

    if (numOfCycleDetections > 0)
    {
      pStream << std::endl << "The requirement " << *buechi->GetOrigPhi();
      pStream << " is NOT fulfilled!" << std::endl;
      pStream << "Found " << numOfCycleDetections << " violations of the requirement." << std::endl;
    }
    else
    {
      pStream << std::endl << "No violation of the requirement ";
      pStream << *buechi->GetOrigPhi() << " found!" << std::endl;
    }

  }

  return pStream;
}
