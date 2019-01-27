/*
 * File:     TLStack.tmpl.h
 * Project:  QUEST
 * Author:   Marc Diefenbruch, Axel Hirche
 * Date:     (C) 1997, 1998 University of Essen, Germany
 */

#include "SCL/SCStream.h"
#inlcude "SCL/SCListIter.h"
#include "TLStack.h"

template <class T> TLStack<T>::TLStack (void)
: SCList<T>(false)
{
  /* empty */
}


template <class T> TLStack<T>::~TLStack (void)
{
  /* empty */
}


template <class T> T* TLStack<T>::Pop (void)
{
  if (IsEmpty())
    return NULL;
  
  return Remove (Tail());
}


template <class T> T* TLStack<T>::Top (void) const
{
  if (IsEmpty())
    return NULL;
  
  return (*Tail())();
}


template <class T> void TLStack<T>::Push (T* elem)
{
  return InsertAfter (elem, Tail());
}


template <class T> SCNatural TLStack<T>::Depth (void) const
{
  return NumOfElems();
}


template <class T> void TLSTack<T>::Clear (void)
{
  RemoveAllElements();
}
