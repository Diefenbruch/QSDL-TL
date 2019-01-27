/*
 *  File:     TLDebug.cpp
 *  Project:  QUEST
 *  Author:   Marc Diefenbruch, Axel Hirche
 *  Date:     (C) 1997, 1998 University of Essen, Germany
 */

#include "TLConfig.h"

#if _TL_DEBUG_

  #include "TLDebug.h"
  #ifndef _TL_ONSCREEN_DEBUG_
  SCStream tlDebugLog ("TLDEBUG.log");
  #endif

#endif
