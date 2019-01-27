/* File:            TLStateList.h
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef _TLSTATELIST_H_
#define _TLSTATELIST_H_

#include "TL.h"
#include "SCL/SCList.h"
#include "TLState.h"


class TLStateList : public SCList<TLState>
{
  friend class SCStream& operator<< (SCStream&, const TLStateList&);

  public:
               TLStateList (SCBoolean deleteElems = false);
               TLStateList (const TLStateList& l);
               TLStateList (const TLStateList* l);

              ~TLStateList (void);
    class
    SCStream&   Display (class SCStream&) const;
    SCBoolean  Append (TLState*);
    SCBoolean  Append (TLNode*);

    SCBoolean  Prepend (TLState*);
    SCBoolean  Prepend (TLNode*);

    TLState*   IsInList (TLState* s) const;
    TLState*   IsInList (class TLNode* n) const;

    TLState*   operator[] (SCNatural) const;

    SCBoolean  SetUpIndices (void);

  private:
    TLState**  stateArray;                        // Used for fast operator[]
    SCBoolean  isFinished;                        // When this is true,
                                                  // Any call to Append,...
                                                  // is an error!
};


class SCStream& operator<< (SCStream&, const TLStateList&);
class SCStream& operator<< (SCStream&, const TLStateList*);


#if _TL_INLINING_
#include "TLStateList.inl.h"
#endif

#endif // _TLSTATELIST_H_
