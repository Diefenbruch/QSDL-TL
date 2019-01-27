/*
 * File:    TLBuechiHelp.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TL_BUECHIHELP_H_
#define _TL_BUECHIHELP_H_

class TLStateSuccIdx                              // Stack element for dfs.
{
  public:
    TLStateSuccIdx (class TLState*  pS) : s(pS), k(0) {}

    ~TLStateSuccIdx (void) { s = NULL; k = 0; }

    class TLState*  s;                            // State being explored.
          SCNatural k;                            // Number of next successor
                                                  // to be explored.
};

#endif // _TL_BUECHIHELP_H_
