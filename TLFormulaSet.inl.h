/*
 * File:    TLFormulaSet.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULASET_INL_H_
#define _TLFORMULASET_INL_H_

#include "SCL/SCStream.h"
#include "TLHelp.h"
#include "SCL/SCListIter.h"
#include "SCL/SCListCons.h"

TLINLINE TLFormulaSet::TLFormulaSet (void)
:  SCList<TLFormula> (false),                     // DO NOT DELETE ELEMENTS!
#if _TL_DEBUG_ > 4
  deleted (false),
#endif
   numOfAtomics(0)
{
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  /* empty */
}


TLINLINE TLFormulaSet::TLFormulaSet (const TLFormulaSet* toCopy)
: SCList<TLFormula>(false),
#if _TL_DEBUG_ > 4
  deleted (false),
#endif
  numOfAtomics(0)
{
  SCListIter<TLFormula> iter (*((TLFormulaSet*) toCopy));
  TLFormula* currentPhi;
  SCNatural i;
  SCNatural limit = toCopy->NumOfElems();
  
  for (i = 0 ; i < limit; i++)
  {
    currentPhi = iter++;                          // Get current element and
                                                  // move iter to next.
    assert (currentPhi);
    Insert (currentPhi);                          // Append. Since toCopy is already
                                                  // partitioned into atomic / nonatomic
                                                  // we don't have to worry about that.
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
}


TLINLINE TLFormulaSet::TLFormulaSet (const TLFormula* phi)
: SCList<TLFormula> (false),
#if _TL_DEBUG_ > 4
  deleted (false),
#endif
  numOfAtomics(0)
{
  assert (phi);
  Insert (phi);
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
}


TLINLINE TLFormulaSet::~TLFormulaSet (void)
{
  numOfAtomics = 0;
#if _TL_DEBUG_ > 4
  deleted = true;
#endif
}


TLINLINE TLFormula* TLFormulaSet::GetTRUEPhi (void)
{
  return (TLFormula*) &truePhi;
}


TLINLINE TLFormula* TLFormulaSet::GetFALSEPhi (void)
{
  return (TLFormula*) &falsePhi;
}


TLINLINE SCBoolean TLFormulaSet::Insert (const TLFormula* toInsert)
{
  assert (toInsert);

  if (IsElem (toInsert))                          // No doublettes.
    return false;

  if (trueEquivEmpty && (toInsert->Operator() == T))
                                                  // If TRUE is equivalent to
                                                  // nothing i.e. empty set,
                                                  // we don't add it.
  {
#if _TL_DEBUG_ > 4
    CheckMe();
#endif
    return false;
  }

  if (toInsert->Arity() == TLAtomic)
  {
    numOfAtomics++;
    SCList<TLFormula>::InsertBefore ((TLFormula*) toInsert);
  }
  else
  {
    SCList<TLFormula>::InsertAfter ((TLFormula*) toInsert);
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return true;
}


TLINLINE TLFormula* TLFormulaSet::Remove (const TLFormula* toKill)
{  
  TLFormula* retVal;

  if (!toKill)                                    // NULL kill.
    return NULL;
  
  if (trueEquivEmpty && (toKill->Operator() == T))
                                                  // If TRUE is equivalent to
                                                  // nothing i.e. empty set,
                                                  // we rightfully assume, that
                                                  // it cannot be in the set.
    return NULL;


  if (toKill->Arity() == TLAtomic)                // It is an atomic prop.
  {
    SCListIter<TLFormula> thisIter (*this);       // Iterator over this.
    TLFormula* currThisPhi;
    SCListCons<TLFormula>* currCons;
    
    for (SCNatural i = 0; i < numOfAtomics; i++)  // Scan atomic half of the set.
    {
      currCons = thisIter.GetCurrentCons();
      currThisPhi = thisIter++;
      assert (currThisPhi);
      assert (currThisPhi->Arity() == TLAtomic);
      if (*currThisPhi == *toKill)
      {
        numOfAtomics--;      
        retVal =  SCList<TLFormula>::Remove (currCons);
                                                  // Delete it.
        assert (retVal);
#if _TL_DEBUG_ > 4
        CheckMe();
#endif
        return retVal;
      }
//      else
//      {
//        currThisPhi = thisIter++;                 // Move on.
//      }
    }
  }
  else                                            // It is a nonatomic prop.
  {
    SCListIter<TLFormula> thisIter (*this, false);// Iterator over this. Start from tail.
    TLFormula* currThisPhi;
    SCListCons<TLFormula>* currCons;
    
    for (SCNatural i = 0; i < (NumOfElems() - numOfAtomics); i++)
                                                 // Scan the non-atomic half of the set.
    {
      currCons = thisIter.GetCurrentCons();
      currThisPhi = thisIter--;
      assert (currThisPhi);
      assert (currThisPhi->Arity() != TLAtomic);
      if (*currThisPhi == *toKill)
      {
        retVal = SCList<TLFormula>::Remove (currCons);
                                                  // Delete it.
#if _TL_DEBUG_ > 4
        CheckMe();
#endif
        return retVal;

      }
//      else
//      {
//        currThisPhi = thisIter--;                 // Move on.
//      }
    }
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return NULL;                                    // *toKill was not in set.

}


TLINLINE void TLFormulaSet::RemoveAllElements (void)
{
  SCList<TLFormula>::RemoveAllElements();
  numOfAtomics = 0;
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
}


TLINLINE TLFormulaSet& TLFormulaSet::operator= (const TLFormulaSet& toCopy)
{
  SCListIter<TLFormula> toCopyIter ((TLFormulaSet&) toCopy);
  SCNatural i;
  TLFormula* tmpPhi;
  
  RemoveAllElements();                            // Empty list.
  
  for (i = 0; i < toCopy.NumOfElems(); i++)
  {
    tmpPhi = toCopyIter++;
    assert (tmpPhi);
    Insert (tmpPhi);
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE TLFormulaSet& TLFormulaSet::operator= (const TLFormula* phi)
{
  assert (phi);
  
  RemoveAllElements();                            // Empty list.
  assert (NumOfElems() == 0);
  assert (numOfAtomics == 0);

  Insert (phi);
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE TLFormulaSet& TLFormulaSet::operator+= (const TLFormulaSet& toAdd)
{
  SCListIter<TLFormula> toAddIter ((TLFormulaSet&) toAdd);
                                                  // Iterator over toAdd.
  TLFormula* currToAddPhi;                        // Current formula of toAdd.
  
  for (SCNatural i = 0; i < toAdd.NumOfElems(); i++)
  {
    currToAddPhi = toAddIter++;
    assert (currToAddPhi);
    Insert (currToAddPhi);
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE TLFormulaSet& TLFormulaSet::operator-= (const TLFormulaSet& toDelete)
{
  SCListIter<TLFormula> toDeleteIter ((TLFormulaSet&) toDelete);
                                                  // Iterator over toDelete.
  TLFormula* currToDeletePhi;                     // Current formula of toDelete.
  SCNatural i;                      

  for (i = 0; i < toDelete.NumOfElems(); i++)
  {
    currToDeletePhi = toDeleteIter++;
    assert (currToDeletePhi);
    Remove (currToDeletePhi);                     // Try to delete it.
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE TLFormulaSet& TLFormulaSet::operator+= (const TLFormula* toAddPhi)
{
  assert (toAddPhi);
  
  if (!IsElem (toAddPhi))
  {
    Insert (toAddPhi);
  }
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE TLFormulaSet& TLFormulaSet::operator-= (const TLFormula* toKillPhi)
{
  Remove (toKillPhi);  
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return *this;
}


TLINLINE SCBoolean TLFormulaSet::IsElem (const TLFormula* phi) const
{
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  if (IsEmpty())
    return false;
  
  if (phi->Arity() == TLAtomic)
  {
    SCListIter<TLFormula> thisIter (*this);
    TLFormula* tmpPhi;

    for (SCNatural i = 0 ; i < NumOfAtomics(); i++)
    {
      tmpPhi = thisIter++;
      assert (tmpPhi);
      assert (tmpPhi->Arity() == TLAtomic);
      
      if (*tmpPhi == *phi)
        return true;
    }
  }
  else                                            // phi is a non-atomic.
  {
    SCListIter<TLFormula> thisIter (*this, false);
    TLFormula* tmpPhi;

    for (SCNatural i = 0 ; i < (NumOfElems() - NumOfAtomics()); i++)
    {
      tmpPhi = thisIter--;
      assert (tmpPhi);
      assert (tmpPhi->Arity() != TLAtomic);

      if (*tmpPhi == *phi)
        return true;
    }
  }
  
  return false;
}


TLINLINE TLFormula* TLFormulaSet::FindMatch (const TLFormula* toMatch) const
{
  SCListIter<TLFormula> thisIter (*((TLFormulaSet*) this));
  TLFormula* tmpPhi;

#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  
  if (toMatch->Arity() == TLAtomic)
  {
    for (SCNatural i = 0 ; i < NumOfAtomics(); i++)
    {
      tmpPhi = thisIter++;
      assert (tmpPhi);
      assert (tmpPhi->Arity() == TLAtomic);
      
      if (*tmpPhi == *toMatch)
        return tmpPhi;;
    }
  }
  else
  {
    thisIter.GoToLast();
    for (SCNatural i = 0 ; i < (NumOfElems() - NumOfAtomics()); i++)
    {
      tmpPhi = thisIter--;
      assert (tmpPhi);
      assert (tmpPhi->Arity() != TLAtomic);

      if (*tmpPhi == *toMatch)
        return tmpPhi;
    }
  }
  
  return NULL;
}


TLINLINE SCBoolean TLFormulaSet::operator== (const TLFormulaSet& toCompare) const
{
  SCListIter<TLFormula> thisIter (*((TLFormulaSet*) this));
  SCListIter<TLFormula> toCompareIter ((TLFormulaSet&) toCompare);
  TLFormula* currentToComparePhi;
  TLFormula* currentThisPhi;
  SCBoolean flag;
  
#if _TL_DEBUG_ > 4
  CheckMe();
  toCompare.CheckMe();
#endif

  if (toCompare.NumOfElems() != NumOfElems())
    return false;                                 // Number of elements does not match.


  for (SCNatural i = 0; i < NumOfElems(); i++)    // Cycle through all elements
                                                  // of toCompare.
  {
    currentToComparePhi = toCompareIter++;        // Get the next element of toCompare.
    assert (currentToComparePhi);
    flag = false;                                 // Reset flag.
    thisIter.GoToFirst();                         // Rewind iterator.
    currentThisPhi = thisIter++;                  // Get first element.

    while (currentThisPhi && !flag)               // While not end of list and
                                                  // no match found.
    {
      if (*currentThisPhi == currentToComparePhi) // Found a match?
        flag = true;                              // Set flag.
      currentThisPhi = thisIter++;                // Get next element.
    }

    if (!flag)                                    // Nothing found?
      return false;                               // We are done.
  }

  return true;                                    // All elements from toCompare have
                                                  // a matching element in this.
}


TLINLINE SCBoolean TLFormulaSet::operator!= (const TLFormulaSet& toCompare) const
{
#if _TL_DEBUG_ > 4
  CheckMe();
  toCompare.CheckMe();
#endif

  return !(*this == toCompare);
}


TLINLINE SCNatural TLFormulaSet::NumOfElems (void) const
{
  return SCList<TLFormula>::NumOfElems();
}


TLINLINE SCNatural TLFormulaSet::NumOfAtomics (void) const
{
  return numOfAtomics;
}


TLINLINE TLFormula* TLFormulaSet::ExtractAny (void)
{
  TLFormula* tmpPhi;
  TLFormula* retVal;
  
  if (NumOfElems() == 0)
    return NULL;

  tmpPhi = (*Tail())();
  assert (tmpPhi);
  
  if (tmpPhi->Arity() == TLAtomic)
    numOfAtomics--;

  retVal =  SCList<TLFormula>::Remove (Tail());      // Could be Head() too.

#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return retVal;
}


TLINLINE TLFormula* TLFormulaSet::ExtractAtomic (void)
{
  TLFormula* tmpPhi;
  TLFormula* retVal;

  if (!numOfAtomics)
    return NULL;

  tmpPhi = (*Head())();
  assert (tmpPhi);
  assert (tmpPhi->Arity() == TLAtomic);
  numOfAtomics--;

  retVal = SCList<TLFormula>::Remove (Head());      // This HAS to be Head()!
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return retVal;
}


TLINLINE TLFormulaSet* TLFormulaSet::GetAllAtomics (void) const
{
  TLFormulaSet* result = new TLFormulaSet();
  SCListIter<TLFormula> thisIter (*((TLFormulaSet*) this));
  TLFormula* tmpPhi;

  for (SCNatural i = 0; i < numOfAtomics; i++)
  {
    tmpPhi = thisIter++;
    assert (tmpPhi);
    assert (tmpPhi->Arity() == TLAtomic);
    result->Insert (tmpPhi);
  }

  assert (result->NumOfElems() == numOfAtomics);
  assert (result->NumOfAtomics() == numOfAtomics);

#if _TL_DEBUG_ > 4
  CheckMe();
  result->CheckMe();
#endif

  return result;
}


TLINLINE SCBoolean TLFormulaSet::IsEmpty (void) const
{
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
  return numOfElems == 0;
}


TLINLINE SCBoolean TLFormulaSet::IsValid (void) const
{

  SCListIter<TLFormula> thisIter (*((TLFormulaSet*) this));
  TLFormulaAtomic* tmpPhi;
#if _TL_DEBUG_ > 4
  CheckMe();
#endif
      
  for (SCNatural i = 0; i < numOfAtomics; i++)
  {
    tmpPhi = (TLFormulaAtomic*) thisIter++;
    assert (tmpPhi->Arity() == TLAtomic);
    
    if (!tmpPhi->Evaluate())
      return false;
  }
  
  return true;
}


TLINLINE void TLFormulaSet::Initialize (SCBoolean pTrueEquivEmpty,
                                        SCBoolean pNowIsPureAtomic,
                                        SCBoolean pExtendedAutomaton)
{
  trueEquivEmpty = pTrueEquivEmpty;
  nowIsPureAtomic = pNowIsPureAtomic;
  extendedAutomaton = pExtendedAutomaton;
}


TLINLINE SCStream& operator<< (      SCStream&      out,
                              const TLFormulaSet& set)
{
  SCListIter<TLFormula> thisIter ((TLFormulaSet&) set);
  
  out << "{";
  
  if (set.NumOfElems() == 0)
  {
    out << "}";
    return out;
  }
    
  for (SCNatural i = 0; i < set.NumOfElems(); i++)
  {
     (thisIter++)->Display(out);
     if (i < set.NumOfElems() - 1)                // Add ";" only after 1st to n - 1
                                                  // element. Since i rund from 0 to n - 1
                                                  // stop ";" after n - 2.
       out << "; ";
  }
  
  return out << "}";
}


TLINLINE SCStream& operator<< (      SCStream&      out,
                              const TLFormulaSet* set)
{
  return out << *set;
}


#if _TL_DEBUG_ > 4
void TLFormulaSet::CheckMe (void) const
{
  SCListIter<TLFormula> myIter (*this);
  TLFormula* tmpPhi;
  SCNatural tmpAtomCount = 0;
  SCNatural tmpNonAtomCount = 0;
  SCNatural tmpElemCount = 0;

  if (deleted)
  {
    tlDebugLog << "TLFormulaSet::CheckMe: *this is deleted!" << std::endl;
    assert (false);
  }

  if (numOfAtomics > SCList<TLFormula>::NumOfElems())
  {
    tlDebugLog << "TLFormulaSet::CheckMe: numOfAtomics > NumOfElems() (";
    tlDebugLog << std::endl;
    assert (false);
  }
  
  for (SCNatural i = 0; i < numOfAtomics; i++)
  {
    tmpPhi = myIter++;
    
    if (tmpPhi->Arity() == TLAtomic)
    {
      tmpAtomCount++;
      tmpElemCount++;
    }
    else
    {
      tlDebugLog << "TLFormulaSet::CheckMe: Found non-atomic proposition in atomic halve of set." << std::endl;
      tlDebugLog << "                       tmpPhi == " << tmpPhi << std::endl;
      tlDebugLog << "                       tmpAtomCount == " << tmpAtomCount << std::endl;
      tlDebugLog << "                       tmpNonAtomCount == " << tmpNonAtomCount << std::endl;
      tlDebugLog << "                       tmpElemCount == " << tmpElemCount << std::endl;
      tlDebugLog << "                       numOfAtomics == " << numOfAtomics << std::endl;
      tlDebugLog << "                       NumOfElems() == " << SCList<TLFormula>::NumOfElems() << std::endl;
      tlDebugLog << "                       *this == " << *this << std::endl;
      assert (false);    
    }
  }

  for (SCNatural i = 0; i < (SCList<TLFormula>::NumOfElems() - numOfAtomics); i++)
  {
    tmpPhi = myIter++;
    
    if (tmpPhi->Arity() != TLAtomic)
    {
      tmpNonAtomCount++;
      tmpElemCount++;
    }
    else
    {
      tlDebugLog << "TLFormulaSet::CheckMe: Found atomic proposition in non-atomic halve of set." << std::endl;
      tlDebugLog << "                       tmpPhi == " << tmpPhi << std::endl;
      tlDebugLog << "                       tmpAtomCount == " << tmpAtomCount << std::endl;
      tlDebugLog << "                       tmpNonAtomCount == " << tmpNonAtomCount << std::endl;
      tlDebugLog << "                       tmpElemCount == " << tmpElemCount << std::endl;
      tlDebugLog << "                       numOfAtomics == " << numOfAtomics << std::endl;
      tlDebugLog << "                       NumOfElems() == " << SCList<TLFormula>::NumOfElems() << std::endl;
      tlDebugLog << "                       *this == " << *this << std::endl;
      assert (false);
    }
  }
  
  if (tmpAtomCount != numOfAtomics)
  {
    tlDebugLog << "TLFormulaSet::CheckMe: tmpAtomCount != numOfAtomics (" << tmpAtomCount;
    tlDebugLog << " != " << numOfAtomics << ")" << std::endl;
    assert (false); 
  }

  if (tmpNonAtomCount != (SCList<TLFormula>::NumOfElems() - numOfAtomics))
  {
    tlDebugLog << "TLFormulaSet::CheckMe: tmpNonAtomCount wrong (" << tmpAtomCount;
    tlDebugLog << ", should be " << (SCList<TLFormula>::NumOfElems() - numOfAtomics) << ")" << std::endl; 
    assert (false);
  }

  if (tmpElemCount != SCList<TLFormula>::NumOfElems())
  {
    tlDebugLog << "TLFormulaSet::CheckMe: tmpElemCount wrong (" << tmpElemCount;
    tlDebugLog << ", should be " << SCList<TLFormula>::NumOfElems() << ")" << std::endl;
    assert (false);
  }
}
#endif

#endif // _TLFORMULASET_INL_H_
