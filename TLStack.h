/*
 * File:     TLStack.h
 * Project:  QUEST
 * Author:   Axel Hirche, Marc Diefenbruch
 * Date:     (C) 1997 University of Essen, All rights reserved.
 */

#ifndef _TLSTACK_H_
#define _TLSTACK_H_

#include "SCL/SCList.h"

template <class T> class TLStack : public SCList<T>
{
  public:
                         TLStack (void);
                        ~TLStack (void);

               T*        Pop (void);
               T*        Top (void) const;
               void      Push (T*);
               SCNatural Depth (void);
               void      Clear (void);            // Kill all elements.

};


#ifndef __GNUC__
#include "TLStack.tmpl.h"  // necessary for CC compiler
#endif

#endif // _TLSTACK_H_
