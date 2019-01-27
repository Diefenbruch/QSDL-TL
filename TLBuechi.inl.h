/*
 * File:    TLBuechi.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TL_BUECHI_INL_H_
#define _TL_BUECHI_INL_H_


/***************** GetNumOfStates: *************/

TLINLINE SCNatural TLBuechi::GetNumOfStates (void) const
{
  assert (stateList);
  return stateList->NumOfElems();
}


/***************** GetStateList: *****************/

TLINLINE TLStateList* TLBuechi::GetStateList (void) const
{
  return stateList;
}


/***************** GetInitialStates: *****************/

TLINLINE TLStateList* TLBuechi::GetInitialStates (void) const
{
  return initialStates;
}


/***************** GetOrigPhi: *****************/

TLINLINE class TLFormula* TLBuechi::GetOrigPhi (void) const
{
  return origPhi;
}


/***************** GetPhi: *****************/

TLINLINE class TLFormula* TLBuechi::GetPhi (void) const
{
  return phi;
}


TLINLINE SCNatural TLBuechi::GetNumOfAcceptanceSets (void) const
{
  return nextAcceptanceSetNo;
}


#endif // _TL_BUECHI_INL_H_
