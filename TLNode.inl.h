/*
 * File:    TLNode.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLNODE_INL_H_
#define _TLNODE_INL_H_

#include "TLState.h"
#include "TLStateList.h"


/******************** Constructor: *********************/

TLINLINE TLNode::TLNode (TLFormulaSet* pNewSet,
                         TLFormulaSet* pNowSet,
                         TLFormulaSet* pNextSet,
                         TLStateList*  pIncoming,
                         SCBoolean     pIsInit)
  : newSet (pNewSet),
    nowSet (pNowSet),
    nextSet (pNextSet),
    isInitial (pIsInit),
    incoming (pIncoming)
{
  assert (incoming);
  assert (newSet);
  assert (nowSet);
  assert (nextSet);
  name = nextName++;                              // Get a new name.  
}

/******************** Constructor: *********************/

TLINLINE TLNode::TLNode (const TLNode* n)
  : isInitial (n->isInitial)
{
  name = nextName++;                              // Get a new name.
  
  assert (n->incoming);
  incoming = new TLStateList (n->incoming);       // Copy the list.
  assert (incoming);

  assert (n->newSet);
  newSet = new TLFormulaSet (n->newSet);          // Copy the set.
  assert (newSet);

  assert (n->nowSet);
  nowSet = new TLFormulaSet (n->nowSet);          // Copy the set.
  assert (nowSet);

  assert (n->nextSet);
  nextSet = new TLFormulaSet (n->nextSet);        // Copy the set.
  assert (nextSet);
}


/******************** Destructor: *********************/

TLINLINE TLNode::~TLNode (void)
{
  assert (incoming);
  delete incoming;
  incoming = NULL;
  
  assert (newSet);
  delete newSet;
  newSet = NULL;
  
  assert (nowSet);
  delete nowSet;
  nowSet = NULL;
  
  assert (nextSet);
  delete nextSet;
  nextSet = NULL;
}


TLINLINE TLFormulaSet* TLNode::GetNew (void) const
{
  assert (newSet);
  return newSet;
}


TLINLINE TLFormulaSet* TLNode::GetNow (void) const
{
  assert (nowSet);
  return nowSet;
}


TLINLINE TLFormulaSet* TLNode::GetNext (void) const
{
  assert (nextSet);
  return nextSet;
}
    

TLINLINE SCBoolean TLNode::IsInitial (void) const
{
  return isInitial;
}


TLINLINE SCBoolean TLNode::SetIsInitial (SCBoolean b)
{
  isInitial = b;
  return true;
}
          

TLINLINE TLStateList* TLNode::GetIncoming (void)
{
  assert (incoming);
  return incoming;
}

TLINLINE SCBoolean TLNode::SetIncoming (TLStateList* s)
{
  if (incoming)
    delete (incoming);
    
  incoming = s;
  return true;
}


TLINLINE SCNatural TLNode::GetName (void) const
{
  return name;
}


TLINLINE SCBoolean TLNode::operator== (const TLState& s1) const
{
  if (TLState::nowIsPureAtomic)
  {
    SCBoolean retVal;
    TLFormulaSet* n1Atomics = nowSet->GetAllAtomics();
    TLFormulaSet* s1Atomics = s1.GetNow()->GetAllAtomics();

    retVal =    (*n1Atomics == *s1Atomics)        // Ignore non atmomics!!!
             && (*nextSet == *s1.nextSet);

    delete n1Atomics;
    delete s1Atomics;

    return retVal;
  }
  else
  {
    return    (*nowSet == *s1.nowSet)
           && (*nextSet == *s1.nextSet);
  }
}


TLINLINE SCBoolean TLNode::operator!= (const TLState& s1) const
{
  return !(*this == s1);
}


TLINLINE SCStream& operator<< (SCStream& out, TLNode& n)
{  
  out << "--- TLNode: ---" << std::endl;
  out << "name == " << n.name << std::endl;
  out << "newSet == " << n.newSet << std::endl;
  out << "nowSet == " << n.nowSet << std::endl;
  out << "nextSet == " << n.nextSet << std::endl;

  if (n.isInitial)
    out << "Initial node." << std::endl;
  
  if (n.incoming->NumOfElems())
  {
    out << n.incoming->NumOfElems() << " incoming edges: ";
    out << n.incoming << std::endl;
  }
  else
  {
    out << "No incoming edges." << std::endl;
  }
  
  out << "---------------" << std::endl;

  return out;
}

TLINLINE SCStream& operator<< (SCStream& out, TLNode* n)
{
  return out << *n;
}

#endif // _TLNODE_INL_H_
