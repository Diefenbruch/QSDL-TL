/* File:            TLState.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#include "SCL/SCStream.h"

#include "SCL/SCDebug.h"
#include "TL.h"
#include "TLFormulaSet.h"
#include "TLStateList.h"
#include "TLNode.h"
#include "TLState.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_DEBUG_
extern SCStream tldebug;
#endif

#if _TL_INLINING_ == 0
#include "TLState.inl.h"
#endif // _TL_INLINING_ == 0

/******************** Static members: ******************/
SCNatural TLState::nextName = 0;


SCBoolean TLState::trueEquivEmpty = false;
SCBoolean TLState::nowIsPureAtomic = false;
SCBoolean TLState::nowDisplaysOnlyAtomics = false;
SCBoolean TLState::extendedAutomaton = false;  
SCBoolean TLState::greedyAutomaton = false;

