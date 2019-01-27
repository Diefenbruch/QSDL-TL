/*
 * File:    TLStateList.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLSTATELIST_INL_H_
#define _TLSTATELIST_INL_H_

#include "SCL/SCStream.h"
#include "SCL/SCListIter.h"
#include "TLNode.h" // MMDB

TLINLINE TLStateList::TLStateList (SCBoolean deleteElems)
:  SCList<TLState> (deleteElems),
   stateArray (NULL),
   isFinished (false)
{
  /* empty */
}


TLINLINE TLStateList::TLStateList (const TLStateList& toCopy)
:  SCList<TLState> (toCopy.deleteElems),
   stateArray (NULL),
   isFinished (false)
{
  SCListIter<TLState> toCopyIter ((TLStateList&) toCopy);
  TLState* tmpState;
  
  for (SCNatural i = 0; i < toCopy.NumOfElems(); i++)
  {
    tmpState = toCopyIter++;
    assert (tmpState);
    InsertAfter (tmpState);
  }
  assert (NumOfElems() == toCopy.NumOfElems());
}


TLINLINE TLStateList::TLStateList (const TLStateList* toCopy)
:  SCList<TLState> (toCopy->deleteElems),
   stateArray (NULL),
   isFinished (false)
{
  SCListIter<TLState> toCopyIter (*((TLStateList*) toCopy));
  TLState* tmpState;
  
  for (SCNatural i = 0; i < toCopy->NumOfElems(); i++)
  {
    tmpState = toCopyIter++;
    assert (tmpState);
    InsertAfter (tmpState);
  }
  assert (NumOfElems() == toCopy->NumOfElems());
}


TLINLINE TLStateList::~TLStateList (void)
{
  delete[] stateArray;
  isFinished = false;
}


TLINLINE SCBoolean TLStateList::Append (TLState* s)
{
  assert (!isFinished);

  if (IsInList (s))
  {
    return false;
  }
  else
  {
    SCList<TLState>::InsertAfter (s);
    return true;
  }
}


TLINLINE SCBoolean TLStateList::Append (TLNode* n)
{
  TLState* tmpState = new TLState (n);
  assert (deleteElems);                           // If we insert a node,
                                                  // The list is the owner
                                                  // of the newly created
                                                  // state. Hence it has
                                                  // to dispose of it.
  
  assert (!isFinished);
  
  if (IsInList (tmpState))
  {
    return false;
  }
  else
  {
    SCList<TLState>::InsertAfter (tmpState);
    return true;
  }
}


TLINLINE SCBoolean TLStateList::Prepend (TLState* s)
{
  assert (!isFinished);

  if (IsInList (s))
  {
    return false;
  }
  else
  {
    SCList<TLState>::InsertBefore (s);
    return true;
  }
}


TLINLINE SCBoolean TLStateList::Prepend (TLNode* n)
{
  TLState* tmpState = new TLState (n);
  assert (deleteElems);                           // If we insert a node,
                                                  // The list is the owner
                                                  // of the newly created
                                                  // state. Hence it has
                                                  // to dispose of it.
                                                  
  assert (!isFinished);
  
  if (IsInList (tmpState))
  {
    return false;
  }
  else
  {
    SCList<TLState>::InsertBefore (tmpState);
    return true;
  }
}



TLINLINE TLState* TLStateList::IsInList (TLState* s) const
{
  SCListIter<TLState> thisIter (*((TLStateList*) this));
  TLState* tmpState;

  if (NumOfElems() == 0)
    return NULL;
  
  for (SCNatural i = 0; i < NumOfElems(); i++)
  {
    tmpState = thisIter++;
    assert (tmpState);
    
    if (*tmpState == *s)
      return tmpState;
  }
  
  return NULL;
}


TLINLINE TLState* TLStateList::IsInList (class TLNode* n) const
{
  SCListIter<TLState> thisIter (*((TLStateList*) this));
  TLState* tmpState;

  if (NumOfElems() == 0)
    return NULL;
  
  for (SCNatural i = 0; i < NumOfElems(); i++)
  {
    tmpState = thisIter++;
    assert (tmpState);
    
    if (*tmpState == *n)
      return tmpState;
  }
  
  return NULL;
}


TLINLINE TLState* TLStateList::operator[] (SCNatural idx) const
{
  assert (isFinished);
  assert (stateArray);
  assert (idx < NumOfElems());
  return stateArray[idx];
}


TLINLINE SCBoolean TLStateList::SetUpIndices (void)
{
  assert (!isFinished);
  
  if (NumOfElems() > 0)
  {
    SCListIter<TLState> thisIter (*this);
    
    stateArray = new TLState*[NumOfElems()];

    for (SCNatural i = 0; i < NumOfElems(); i++)
    {
      stateArray[i] = thisIter++;
    }
    
    isFinished = true;
    
    return true;
  }
  
  isFinished = true;
  return false;
}


TLINLINE SCStream& operator<< (      SCStream&     out,
                              const TLStateList& list)
{
  SCListIter<TLState> listIter ((TLStateList&) list);
  TLState* tmpState;
  
  out << "[";
  for (SCNatural i = 0; i < list.NumOfElems(); i++)
  {
    tmpState = listIter++;
    assert (tmpState);
    out << tmpState->GetName();
    if (i < (list.NumOfElems() - 1))
      out << ", ";
  }
  
  return out << "]";
}


TLINLINE SCStream& operator<< (      SCStream&     out,
                              const TLStateList* list)
{
  return out << *list;
}


#endif // _TLSTATELIST_INL_H_
