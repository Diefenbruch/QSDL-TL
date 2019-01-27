/* File:            TLTemplates.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/


#ifdef __GNUC__

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#include "TLFormula.h"
#include "TLState.h"
#include "TLStateList.h"
#include "TLFormulaSet.h"

#include "SCL/SCList.tmpl.h"
#include "SCL/SCListIter.h"
#include "SCL/SCListCons.h"
#include "SCL/SCTable.h"
#include "SCL/SCTable.tmpl.h"

template class SCList<TLFormula>;
template class SCListIter<TLFormula>;
template class SCListCons<TLFormula>;

template class SCList<TLState>;
template class SCListIter<TLState>;
template class SCListCons<TLState>;

template class SCTable<TLState>;

#endif // __GNUC__
