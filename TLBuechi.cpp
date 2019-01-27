/* 
 * File:            TLBuechi.cc
 * Author:          Marc Diefenbruch, Axel Hirche
 * Project:         QUEST
 * Date:            (C) 1997, 1998 - University of Essen, Germany
 */

#include "TL.h"
#include "TLHelp.h"
#include "TLFormula.h"
#include "TLFormulaALWAYS.h"
#include "TLFormulaAND.h"
#include "TLFormulaAtomic.h"
#include "TLFormulaAtomic_NOT.h"
#include "TLFormulaBinary.h"
#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaFALSE.h"
#include "TLFormulaIMPLIES.h"
#include "TLFormulaNEXTTIME.h"
#include "TLFormulaNOT.h"
#include "TLFormulaOR.h"
#include "TLFormulaSet.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaUnary.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaWAITFOR.h"
#include "TLFormulaSet.h"
#include "TLParser.h"
#include "TLStateList.h"
#include "TLState.h"
#include "TLNode.h"
#include "TLBuechi.h"
#include "TLBuechiHelp.h"

#include "SCL/SCListIter.h"

#if _TL_INLINING_ == 0
#include "TLBuechi.inl.h"
#endif // _TL_INLINING_ == 0

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif


/***************** Constructor: *****************/

TLBuechi::TLBuechi (char               *phiStr,
                    SCName2PropFuncPtr *pName2Func,
                    SCNatural           pNumOfElems,
                    SCBoolean           pTrueEquivEmpty,
                    SCBoolean           pNowIsPureAtomic,
                    SCBoolean           pNowDisplaysOnlyAtomics,
                    SCBoolean           pExtendedAutomaton,
                    SCBoolean           pSimplifyFormulae,
                    SCBoolean           pGreedyAutomaton,
                    SCBoolean           pAutoNegate)
  : trueEquivEmpty (pTrueEquivEmpty),
    nowIsPureAtomic (pNowIsPureAtomic),
    nowDisplaysOnlyAtomics (pNowDisplaysOnlyAtomics),
    extendedAutomaton (pExtendedAutomaton),
    greedyAutomaton (pGreedyAutomaton),
    autoNegate (pAutoNegate),
    nextAcceptanceSetNo (0)
{
  TLFormula* notPhi = NULL;
  TLFormula* rewritePhi = NULL;

  acceptFormulae = new TLFormulaSet;

#if _TL_DEBUG_ > 4
  tlDebugLog << "+++ Entering TLBuechi::TLBuechi (char*, SCName2PropFuncPtr*, SCNatural)" << std::endl;
#endif

  TLState::Initialize (pTrueEquivEmpty,
                       pNowIsPureAtomic,
                       pNowDisplaysOnlyAtomics,
                       pExtendedAutomaton,
                       pGreedyAutomaton);


  TLFormulaSet::Initialize (pTrueEquivEmpty,
                            pNowIsPureAtomic,
                            pExtendedAutomaton);  // Initialize formula set
                                                  // class.

  TLFormula::Initialize (pExtendedAutomaton,
                         pSimplifyFormulae);      // Initialize formula class.



  TLAssert (InitializeParser (phiStr,
                              pName2Func,
                              pNumOfElems),
            "Initialization of parser failed.");
  
  origPhi = TLParse();                            // Parse formula.
  TLAssert (origPhi, "Parsing of formula failed.");
  
  CleanUpParser();                                // Do house keeping.

#if _TL_DEBUG_
    tlDebugLog << "origPhi == " << *origPhi << std::endl;
#endif

  if (autoNegate)
  {
    notPhi = new TLFormulaNOT (origPhi->GetCopy(), false);
    TLAssert (notPhi, "Negation of formula failed.");
                                                  // This is pointless as
                                                  // operator new NEVER
                                                  // returns NULL.
  }
  else
  {
#if _TL_DEBUG_ > 3
   tlDebugLog  << std::endl << "*** WARNING: Auto negation disabled! ***" << std::endl;
#endif
    notPhi = origPhi->GetCopy();
  }

  assert (notPhi != origPhi);
  
#if _TL_DEBUG_  > 3
  tlDebugLog << "notPhi == " << *notPhi << std::endl;
#endif

  rewritePhi = notPhi->Rewrite();
  TLAssert (rewritePhi, "Rewriting of formula failed.");
  assert (rewritePhi != notPhi);
  delete notPhi;
  
  
#if _TL_DEBUG_ > 3
  tlDebugLog << "rewritePhi == " << *rewritePhi << std::endl;
#endif

  phi = rewritePhi->PushNegations(false);         // Push negations etc.
  TLAssert (phi, "Pushing of negations failed.");

  assert (rewritePhi != phi);

  delete rewritePhi;                              // Don´t need it anymore.
  
#if _TL_DEBUG_ > 3
  tlDebugLog << "pushNegPhi == " << *phi << std::endl;
#endif

  TLAssert (SetUpAcceptanceSet (phi),
            "Setting up of acceptance state sets failed!");

#if _TL_DEBUG_ > 3
  tlDebugLog << "acceptFormulae == " << acceptFormulae << std::endl;
#endif


  referenceAcceptanceSet = 0ULL;                  // Clear all bits just to be sure.

  for (SCNatural i = 0; i < nextAcceptanceSetNo; i++)
  {
    referenceAcceptanceSet |= (1ULL << i);        // Set all used bits to one.
  }
  
#if _TL_DEBUG_
  tlDebugLog << "referenceAcceptanceSet == ";
  ShowBits (tlDebugLog, referenceAcceptanceSet);
  tlDebugLog << std::endl;
  tlDebugLog << "phi ==        " << *phi << std::endl;
#endif
  
  stateList = new TLStateList(true);              // Delete states upon
                                                  // destruction.
  
  TLAssert (stateList, "Allocation of stateList failed.");
  
  initialStates = new TLStateList();
  TLAssert (initialStates, "Allocation of initialStates failed.");

  new1Set = new TLFormulaSet();
  assert (new1Set);
  
  new2Set = new TLFormulaSet();
  assert (new2Set);

  next1Set = new TLFormulaSet();
  assert (next1Set);

  TLAssert (CreateGraph(), "Construction of buechi automaton failed.");

#if _TL_DEBUG_ > 4
  tlDebugLog << "Exiting TLBuechi::TLBuechi." << std::endl;
#endif

}


/***************** Destructor: *****************/

TLBuechi::~TLBuechi (void)
{
#if _TL_DEBUG_ > 4
  tlDebugLog << "+++ Entering TLBuechi::~TLBuechi (void)" << std::endl;
#endif

  if (phi)                                        // This can't be NULL, but...
  {
    delete phi;                                   // Delete the formula.
    phi = NULL;
  }

  if (origPhi)
  {
    delete origPhi;
    origPhi = NULL;
  }

  if (stateList)
  {
    delete stateList;
    stateList = NULL;
  }

  if (initialStates)
  {
    delete initialStates;
    initialStates = NULL;
  }

  if (acceptFormulae)
  {
    delete acceptFormulae;
    acceptFormulae = NULL;
  }

  if (new1Set)
  {
    delete new1Set;
    new1Set = NULL;
  }

  if (new2Set)
  {
    delete new2Set;
    new2Set = NULL;
  }

  if (next1Set)
  {
    delete next1Set;
    next1Set = NULL;
  }

#if _TL_DEBUG_ > 4
  tlDebugLog << "+++ Exiting TLBuechi::~TLBuechi (void)" << std::endl;
#endif

}


/***************** CreateGraph: ****************/
SCBoolean TLBuechi::CreateGraph (void)
{
  TLNode*       startNode;
  TLFormulaSet* newSet;
  TLFormulaSet* nowSet;
  TLFormulaSet* nextSet;
  TLStateList  *l;


#if _TL_DEBUG_ > 4
  tlDebugLog << "+++ Entering TLBuechi::CreateGraph (void)" << std::endl;
#endif

  TLAssert (stateList, "stateList == NULL.");     // Make sure this baby is up
                                                  // and running...

  newSet = new TLFormulaSet (phi);
#if _TL_DEBUG_ > 4
  newSet->CheckMe();
#endif

  nowSet = new TLFormulaSet();

  nextSet = new TLFormulaSet();

  l = new TLStateList ();

  startNode = new TLNode (newSet,
                          nowSet,
                          nextSet,
                          l,                      // No incoming edge yet.
                          true);                  // This is an initial node!!!

  TLAssert (startNode, "Allocation of startNode failed.");

#if _TL_DEBUG_ > 4
  tlDebugLog << "startNode == " << std::endl << *startNode << std::endl;
#endif

  if (Expand (startNode, stateList))              // Since states is a pointer,
                                                  // it will be modified like
                                                  // a global. Hence no need
                                                  // to store the result.
  {
#if _TL_DEBUG_ > 3
    tlDebugLog << std::endl << "+++ TLBuechi::CreateGraph (void)" << std::endl;
    tlDebugLog << "    Graph creation successfull." << std::endl << std::endl;
    tlDebugLog << "    stateList == " << std::endl;
    {
      SCListIter<TLState> tmpIter (*(SCList<TLState>*) stateList);
      TLState* tmpState;

      for (SCNatural i = 0; i < stateList->NumOfElems(); i++)
      {
        tmpState = tmpIter++;
        assert (tmpState);
        tlDebugLog << tmpState << std::endl;
      }
    }
    tlDebugLog << "    initialStates == " << std::endl << initialStates << std::endl << std::endl;
    tlDebugLog << "The formula is " << (IsFulfillable() ? "" : " NOT ");
    tlDebugLog << "fullfillable." << std::endl;
#endif

    stateList->SetUpIndices();                    // Activate operator[]
    initialStates->SetUpIndices();                // Activate operator[]

    for (SCNatural i = 0; i < stateList->NumOfElems(); i++)
    {
      (*stateList)[i]->GetOutEdges()->SetUpIndices();
      (*stateList)[i]->GetInEdges()->SetUpIndices();
    }

    return true;
  }
  else
  {
#if _TL_DEBUG_ > 3
    tlDebugLog << "+++ Exiting TLBuechi::CreateGraph (void)" << std::endl;
    tlDebugLog << "    Graph creation failed!" << std::endl;
#endif
    return false;
  }
}


/***************** Expand: *****************/

TLStateList* TLBuechi::Expand (TLNode*       theNode,
                               TLStateList*  states)
{
  TLState* tmpState;
  
  assert (theNode);
  assert (states);

#if _TL_DEBUG_ > 3
  tlDebugLog << "TLBuechi::Expand: Entering..." << std::endl;
  tlDebugLog << "TLBuechi::Expand: theNode == " << theNode << std::endl;
#endif

  if (theNode->GetNew()->IsEmpty())               // New is empty.
  {
#if _TL_DEBUG_ > 3
    tlDebugLog << "TLBuechi::Expand: theNode->newSet is empty." << std::endl;
#endif

    tmpState = states->IsInList (theNode); 
    if (tmpState)                                 // There exists a node
                                                  // with the same key.
    {

#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: found tmpState == theNode." << std::endl;
      tlDebugLog << "                  tmpState == " << tmpState << std::endl;
#endif


      if (theNode->IsInitial())                   // current node is initial.
      {
        tmpState->SetIsInitial(true);
                                                  // Mark existing node
                                                  // as initial state.

        if (!initialStates->IsInList (theNode))   // The existing state is not
                                                  // in the list of initial
                                                  // states.
        {
          initialStates->Append (tmpState);
#if _TL_DEBUG_ > 3
          tlDebugLog << "TLBuechi::Expand: added tmpState to initialStates." << std::endl;
#endif
        }
      }

      assert (theNode->GetIncoming());

      tmpState->MergeToIncoming (theNode->GetIncoming());
                                                  // Join the sets of incoming
                                                  // edges and store with
                                                  // existing node. Update
                                                  // inEdges / outEdges of all
                                                  // states affected.

#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Updated tmpState->inEdges." << std::endl;
      tlDebugLog << "                  tmpState == " << tmpState << std::endl;
#endif

      if (nowIsPureAtomic)
      {
        *tmpState->GetNow() += *theNode->GetNow();
                                                  // Operator == will only compare
                                                  // atomic propositions in nowSet,
                                                  // but the non atomic propositions
                                                  // in tmpState->nowSet and theNode->nowSet
                                                  // may differ. This way we synchronize
                                                  // the sets.
#if _TL_DEBUG_ > 3
        tlDebugLog << "TLBuechi::Expand: Updatet tmpState->nowSet." << std::endl;
        tlDebugLog << "                  tmpState == " << tmpState << std::endl;
#endif
      }

      delete theNode;                             // No longer needed.

      return states;                              // Return the updatet set.
    }
    else                                          // No state with same key yet.
    {
      tmpState = new TLState (theNode);

      assert (tmpState);

      tmpState->SetUpAcceptanceSets (acceptFormulae);
                                                  // Set up membership to
                                                  // acceptance sets. This
                                                  // requires the full
                                                  // NOW set, with non
                                                  // atomic formulae.

      tmpState->MergeToIncoming (theNode->GetIncoming());

      states->Append(tmpState);                   // Add the state part of the
                                                  // current node to the set
                                                  // of expanded states.

#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Added new state to stateList." << std::endl;
      tlDebugLog << "                  new state == " << tmpState << std::endl;
#endif

      if (tmpState->IsInitial())
      {
        initialStates->Append (tmpState);
      }

#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Add new state to initialStates." << std::endl;
#endif

      *theNode->GetNew() = *theNode->GetNext();   // Convert theNode to it's
                                                  // successor node.
      theNode->GetNow()->RemoveAllElements();
      theNode->GetNext()->RemoveAllElements();

      theNode->SetIncoming (new TLStateList());   // This will delete the old list
      assert (theNode->GetIncoming());

      theNode->GetIncoming()->Append (tmpState);  // Make sure we add the STATE,
                                                  // not the NODE!
      theNode->SetIsInitial (false);

#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi:Expand: Updatet theNode." << std::endl;
      tlDebugLog << "                 theNode == " << theNode << std::endl;
#endif

      return Expand (theNode, states);            // Expand successor node.
    }
  }
  else                                            // New is not empty.
  {
#if _TL_DEBUG_ > 3
    tlDebugLog << "TLBuechi::Expand: theNode->newSet is NOT empty." << std::endl;
#endif

    TLFormula* eta = theNode->GetNew()->ExtractAny();
                                                  // Select an arbitrary
                                                  // formula from new.
    assert (eta);

#if _TL_DEBUG_ > 3
    tlDebugLog << "TLBuechi::Expand: Extracted eta == '" << eta << "' from theNode->nowSet." << std::endl;
#endif

    TLByte opr = eta->Operator();                 // Retrieve the operator.

    if (eta->Arity() == TLAtomic)                 // Atomic proposition or
                                                  // negation of such. Note
                                                  // that negations only
                                                  // occur directly in front
                                                  // of atomic propositions.
                                                  // NOT is considered atomic.
    {
      if ((opr == F) ||                           // False is a contradiction.
          (theNode->GetNow()->IsElem (((TLFormulaAtomic*) eta)->GetNegation())))

                                                  // Negation of eta is
                                                  // already in now, i.e.
                                                  // we have a contradiction.
      {
        delete theNode;                           // Discard current node.
#if _TL_DEBUG_ > 3
        tlDebugLog << "TLBuechi::Expand: eta is a contradiction!" << std::endl;
#endif
        return states;
      }
      else                                        // No contradiction.
      {
        *theNode->GetNow() += eta;                // Add eta to now-set.
#if _TL_DEBUG_ > 3
        tlDebugLog << "TLBuechi::Expand: Added eta to theNode->nowSet." << std::endl;
        tlDebugLog << "                  theNode == " << theNode << std::endl;
#endif
        return Expand (theNode, states);          // Continue to expand current
                                                  // node.
      }
    }


    if (opr == UNTIL ||
        opr == V_OPER ||
        opr == EVENTUALLY ||
        opr == OR ||
        opr == WAITFOR ||
        opr == Z_OPER)
    {
      if (opr == UNTIL)                           // C.f. GPVW95, pp. 11-10
      {
        assert (((TLFormulaBinary*) eta)->RightOperand());
        assert (theNode->GetNew());
        assert (theNode->GetNow());

        if (   (theNode->GetNew()->IsElem (((TLFormulaBinary*) eta)->RightOperand()))
            || (theNode->GetNow()->IsElem (((TLFormulaBinary*) eta)->RightOperand()))
           )                                      // if eta is of type UNTIL and
                                                  // eta->rightOperand is in
                                                  // (theNode->nowSet + theNode->newSet)
                                                  // we don't need a split. Simply move eta
                                                  // into theNode->nowSet and continue.
        {
          *theNode->GetNow() += eta;
          return Expand (theNode, states);
        }
      }

      if (opr == V_OPER)                          // C.f. GPVW95, pp. 11-10
      {
        assert (((TLFormulaBinary*) eta)->RightOperand());
        assert (((TLFormulaBinary*) eta)->LeftOperand());
        assert (theNode->GetNew());
        assert (theNode->GetNow());

        if (     (   (theNode->GetNew()->IsElem (((TLFormulaBinary*) eta)->LeftOperand()))
                  || (theNode->GetNow()->IsElem (((TLFormulaBinary*) eta)->LeftOperand()))
                 )
              && (   (theNode->GetNew()->IsElem (((TLFormulaBinary*) eta)->RightOperand()))
                  || (theNode->GetNow()->IsElem (((TLFormulaBinary*) eta)->RightOperand()))
                 )
           )
        {
          *theNode->GetNow() += eta;
          return Expand (theNode, states);
        }
      }

      {
        TLStateList* tmpStates;
        TLNode       *node1 = new TLNode (theNode); // 2nd node of split.

        assert (node1);

        *theNode->GetNew() += *New1(eta);
        *theNode->GetNew() -= *theNode->GetNow();
        *theNode->GetNow() += eta;
        *theNode->GetNext() += *Next1(eta);

        *node1->GetNew() += *New2(eta);
        *node1->GetNew() -= *node1->GetNow();
        *node1->GetNow() += eta;

#if _TL_DEBUG_ > 3
        tlDebugLog << "TLBuechi::Expand: Splitted theNode to" << std::endl;
        tlDebugLog << "                  node1 == " << node1 << std::endl;
        tlDebugLog << "                  TheNode == " << theNode << std::endl;
#endif

        tmpStates = Expand (theNode, states);
        return Expand (node1, tmpStates);
      }
    }

    if (opr == AND)
    {
      *theNode->GetNew() += ((TLFormulaAND*) eta)->RightOperand();
      *theNode->GetNew() += ((TLFormulaAND*) eta)->LeftOperand();
      *theNode->GetNew() -= *theNode->GetNow();   // NEW = (NEW + (eta->left + eta->right))\ NOW
      *theNode->GetNow() += eta;
#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Processed AND." << std::endl;
      tlDebugLog << "                  theNode == " << theNode << std::endl;
#endif
      return Expand (theNode, states);
    }


    if (opr == ALWAYS)
    {
      *theNode->GetNew() += ((TLFormulaALWAYS*) eta)->RightOperand();
      *theNode->GetNew() -= theNode->GetNow();
      *theNode->GetNow() += eta;
      *theNode->GetNext() += eta;
#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Processed ALWAYS." << std::endl;
      tlDebugLog << "                  theNode == " << theNode << std::endl;
#endif
      return Expand (theNode, states);
    }

    if (opr == NEXTTIME)
    {
      *theNode->GetNow() += eta;
      *theNode->GetNext() += ((TLFormulaNEXTTIME*) eta)->RightOperand();
#if _TL_DEBUG_ > 3
      tlDebugLog << "TLBuechi::Expand: Processed ALWAYS." << std::endl;
      tlDebugLog << "                  theNode == " << theNode << std::endl;
#endif
      return Expand (theNode, states);
    }

    if (opr == IMPLIES)                           // These are always rewritten.
    {
      assert (false);
      return NULL;
    }

    assert (false);
    return NULL;
  }

  assert (false);                                 // Should never be here!!!
}


/***************** New1 ******************/

const TLFormulaSet* TLBuechi::New1 (TLFormula* eta)
{
  assert (new1Set);                               // Not that this might not
                                                  // be empty!

  new1Set->RemoveAllElements();

  switch (eta->Operator())
  {
    case UNTIL:
    case WAITFOR:
    case OR:
      *new1Set = ((TLFormulaBinary*) eta)->LeftOperand();
      return new1Set;
      break;

    case V_OPER:
    case Z_OPER:
      *new1Set = ((TLFormulaV_OPER*) eta)->RightOperand();
      return new1Set;
      break;

    case EVENTUALLY:
      if (!trueEquivEmpty)
      {
        *new1Set = TLFormulaSet::GetTRUEPhi();
      }

      return new1Set;

    default:
      assert (false);
  }

  return NULL;                                    // Keep the compiler happy...
}


/***************** New2 ******************/

const TLFormulaSet* TLBuechi::New2 (TLFormula* eta)
{
  assert (new2Set);                               // Note that this might
                                                  // not be empty!!!

  new2Set->RemoveAllElements();
  switch (eta->Operator())
  {
    case UNTIL:
    case WAITFOR:
    case OR:
    case EVENTUALLY:
      *new2Set = ((TLFormulaUnary*) eta)->RightOperand();
      return new2Set;
      break;

    case V_OPER:
    case Z_OPER:
      *new2Set = ((TLFormulaV_OPER*) eta)->LeftOperand();
      *new2Set += ((TLFormulaV_OPER*) eta)->RightOperand();
      return new2Set;
      break;

    default:
      assert (false);
  }

  return NULL;                                    // Keep the compiler happy...
}

/***************** Next1 ******************/

const TLFormulaSet* TLBuechi::Next1 (TLFormula* eta)
{
  assert (next1Set);

  next1Set->RemoveAllElements();
  switch (eta->Operator())
  {
    case UNTIL:
    case V_OPER:
    case EVENTUALLY:
    case WAITFOR:
    case Z_OPER:
      *next1Set = eta;
      return next1Set;
      break;

    case OR:
      next1Set->RemoveAllElements();              // Make sure that baby is empty!!!
      return next1Set;
      break;

    default:
      assert (false);
  }

  return NULL;                                    // Keep the compiler happy...
}


const SCBitSet TLBuechi::GetReferenceAcceptanceSet (void) const
{
  return referenceAcceptanceSet;
}


SCBoolean TLBuechi::SetUpAcceptanceSet (TLFormula* phi)
{
  if (phi->Arity() == TLAtomic)
    return true;                                  // Nothing to do for atomic formulae.

  switch (phi->Operator())
  {
    case EVENTUALLY:
    case UNTIL:
    case Z_OPER:
      if (acceptFormulae->Insert (phi))           // phi was not yet a member
      {
        phi->SetAcceptanceSetNo (nextAcceptanceSetNo++);
                                                  // Assign it a new acceptance
                                                  // set number.
      }
      else                                        // Phi is already in acceptFormulae.
      {
        TLFormula* tmpPhi = acceptFormulae->FindMatch (phi);
                                                  // Find the matching phi.
        assert (tmpPhi);                          // It HAS to be there!!!
        phi->SetAcceptanceSetNo (tmpPhi->GetAcceptanceSetNo());
                                                  // Use tmpPhi acceptance set number.
      }
      break;

    default:
      break;                                      // Nothing to do here.
  }

  if (phi->Arity() == TLUnary)                    // Phi has only one operand.
  {
    return SetUpAcceptanceSet(((TLFormulaUnary*) phi)->RightOperand());
  }
  else                                            // Phi has two operands.
  {
    SCBoolean tmpResult = SetUpAcceptanceSet (((TLFormulaBinary*) phi)->LeftOperand());
    return tmpResult && SetUpAcceptanceSet (((TLFormulaBinary*) phi)->RightOperand());
  }

  assert (false);                                 // Atomics were processed right
                                                  // at the beginning.
  return false;
}


SCBoolean TLBuechi::IsFulfillable (void) const
{
  SCListIter<TLState> iter (*initialStates);

  SCTable<TLState> hash1 (stateList->NumOfElems(),
                          false,
                          false);                 // Hash table for Dfs1

  SCTable<TLState> hash2 (stateList->NumOfElems(),
                          false,
                          false);                 // Hash table for Dfs2

  if (initialStates->NumOfElems() == 0)
    return false;

  for (TLState* tmpState = iter++;
       tmpState;
       tmpState = iter++)
  {
    if (Dfs1 (tmpState,
              hash1,
              hash2))
    {
#if _TL_DEBUG_ > 1
      tlDebugLog << "[" << tmpState->GetName() << "]" << std::endl;
#endif
      return true;
    }
  }
  return false;
}


SCBoolean TLBuechi::IsAcceptingStutterState (TLState* s) const
{
  SCTable<TLState> hash1 (stateList->NumOfElems(),
                          false,
                          false);                 // Hash table for Dfs1

  SCTable<TLState> hash2 (stateList->NumOfElems(),
                          false,
                          false);                 // Hash table for Dfs2

  assert (s);

  if (Dfs1 (s,
            hash1,
            hash2,
            true))
  {
    return true;
  }

  return false;
}


SCBoolean TLBuechi::Dfs1 (TLState*          s,
                          SCTable<TLState>& hash1,
                          SCTable<TLState>& hash2,
                          SCBoolean checkAtoms) const
{
  SCListIter<TLState> iter (*s->GetOutEdges());

  if (checkAtoms && !s->NowIsValid())
  {
    return false;                                 // Not consistent with
                                                  // current system state
                                                  // Note the difference
                                                  // between a buechi state
                                                  // and a system state!!!
  }

  if (hash1.Find (s->GetName()))
  {
    return false;                                 // Already explored.
  }

  hash1.Insert (s->GetName(), s);                 // Mark as explored.

  for (TLState* tmpState = iter++;
       tmpState;
       tmpState = iter++)                         // For all successors
  {
    if (Dfs1 (tmpState,
              hash1,
              hash2,
              checkAtoms))
    {
#if _TL_DEBUG_
      tlDebugLog << "[" << tmpState->GetName() << "] ";
#endif
      return true;
    }
  }

  if (s->IsAcceptingState()
      || (referenceAcceptanceSet == 0ULL) )
  {
    iter.GoToFirst();                             // Reset.

    for (TLState* tmpState = iter++;
         tmpState;
         tmpState = iter++)
    {
      if (Dfs2 (tmpState,
                hash2,
                0ULL,
                s,
                checkAtoms))                      // s is the state we are
                                                  // looking for.
      {
#if _TL_DEBUG_
        tlDebugLog << "[" << tmpState->GetName() << "] ";
#endif
        return true;
      }
    }
  }

  return false;                                   // No cycle found.
}


SCBoolean TLBuechi::Dfs2 (TLState*          s,
                          SCTable<TLState>& hash2,
                          SCBitSet          fulfilled,
                          TLState*          toFind,
                          SCBoolean         checkAtoms) const
{
  SCListIter<TLState> iter (*s->GetOutEdges());
  SCBitSet oldFulfilled = fulfilled;

  if (checkAtoms && !s->NowIsValid())
  {
    return false;                                 // Not consistent with
                                                  // current system state
                                                  // Note the difference
                                                  // between a buechi state
                                                  // and a system state!!!
  }
  
  if (s->IsAcceptingState())
  {
    fulfilled |= s->GetAcceptanceSets();          // Increment "counter"
  }

  if (   *s == *toFind
      && (   (referenceAcceptanceSet == 0ULL)     // No acceptance state sets.
          || (referenceAcceptanceSet == fulfilled)))
                                                  // All acceptance state sets
                                                  // have been fulfilled.
  {
    return true;
  }
  
  if (hash2.Find (s->GetName()))
  {
    return false;                                 // Already explored.
  }
  
  hash2.Insert (s->GetName(), s);                // Mark as explored.
  
  for (TLState* tmpState = iter++;
       tmpState;
       tmpState = iter++)                         // For all successors
  {
    if (Dfs2 (tmpState,
              hash2,
              oldFulfilled,
              s,
              checkAtoms))
    {
#if _TL_DEBUG_
      tlDebugLog << "[" << tmpState->GetName() << "] ";
#endif
      return true;
    }
  }
    
  return false;                                   // No cycle found.
}
