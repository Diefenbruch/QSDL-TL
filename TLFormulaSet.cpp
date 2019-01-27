/* File:            TLFormulaSet.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#include "SCL/SCStream.h"
#include "SCL/SCList.tmpl.h"

#include "TLFormula.h"
#include "TLFormulaUnary.h"
#include "TLFormulaBinary.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaFALSE.h"
#include "TLHelp.h"
#include "TLFormulaSet.h"

#if _TL_INLINING_ == 0
#include "TLFormulaSet.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_DEBUG_
extern SCStream tldebug;
#endif

SCBoolean      TLFormulaSet::trueEquivEmpty;
SCBoolean      TLFormulaSet::nowIsPureAtomic;
SCBoolean      TLFormulaSet::extendedAutomaton;
TLFormulaTRUE  TLFormulaSet::truePhi;
TLFormulaFALSE TLFormulaSet::falsePhi;

SCStream& TLFormulaSet::Display (SCStream& out) const
{
  return out << *this;
}

