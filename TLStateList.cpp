/* File:            TLStateList.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#include "SCL/SCStream.h"
#include "SCL/SCList.tmpl.h"

#include "TLNode.h"
#include "TLStateList.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_INLINING_ == 0
  #include "TLStateList.inl.h"
#endif

SCStream& TLStateList::Display (SCStream& out) const
{
  return out << *this;
}
