/*
 *  File:     TLConfig.h
 *  Project:  QUEST
 *  Author:   Axel Hirche, Marc Diefenbruch
 *  Date:     (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TL_CONFIG_H_
#define _TL_CONFIG_H_

#define _TL_INLINING_ 0

#if _TL_INLINING_
#define TLINLINE inline
#else
#define TLINLINE
#endif // _TL_INLINING_

#define _TL_DEBUG_ 0
//#define _TL_ONSCREEN_DEBUG_

#endif // _TL_CONFIG_H_
