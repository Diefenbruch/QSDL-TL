/* File:            TLNode.cc
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#include "SCL/SCStream.h"

#include "TLNode.h"
#include "TLBuechi.h"

#if _TL_INLINING_ == 0
  #include "TLNode.inl.h"
#endif

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

#if _TL_DEBUG_
extern SCStream tldebug;
#endif


/******************** Static members: ******************/

SCNatural TLNode::nextName = 0;

