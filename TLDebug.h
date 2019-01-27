/*
 *  File:     TLDebug.h
 *  Project:  QUEST
 *  Author:   Marc Diefenbruch Axel Hirche
 *  Date:     (C) 1997 University of Essen, Germany
 */

#ifndef _TL_DEBUG_H_
#define _TL_DEBUG_H_

#ifdef _TL_ONSCREEN_DEBUG_
#include "SCL/SCStream.h"
#define tlDebugLog SCScheduler::errorStream
#else
#include "SCL/SCStream.h"
extern SCStream tlDebugLog;
#endif

#endif // _TL_DEBUG_H_
