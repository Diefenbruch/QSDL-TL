/* File:            TLNode.h
   Author:          Axel Hirche, Marc Diefenbruch
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, All rights reserved.
*/

#ifndef _TLNODE_H_
#define _TLNODE_H_

#include "TL.h"
#include "TLFormula.h"
#include "TLFormulaSet.h"
#include "TLState.h"

class TLNode
{
  friend class TLState;
  friend class SCStream& operator<< (class SCStream&, TLNode&);


  public:

    TLNode (      TLFormulaSet* NewSet,           // Set of unprocessed
                                                  // formulae.
                  TLFormulaSet* NowSet,           // Set of formulae that have
                                                  // to be valid in this state.
                  TLFormulaSet* NextSet,          // Set of formulae, that have
                                                  // to be valid in the next
                                                  // state.
            class TLStateList*  incoming,         // A node can have more than
                                                  // one incoming edge.
                  SCBoolean     isInit = false);  // True if initial node.

    TLNode (const TLNode*);                       // Copy constructor.

    ~TLNode (void);

          TLFormulaSet* GetNew (void) const;
          TLFormulaSet* GetNow (void) const;
          TLFormulaSet* GetNext (void) const;

          SCBoolean     IsInitial (void) const;
          SCBoolean     SetIsInitial (SCBoolean b);

    class TLStateList*  GetIncoming (void);
          SCBoolean     SetIncoming (class TLStateList* s);

          SCNatural     GetName (void) const;

          SCBoolean     operator== (const TLState&) const;
          SCBoolean     operator!= (const TLState&) const;

  private:
          TLNode (void);                          // Forbidden!
          TLNode (const TLNode&);                 // Forbidden!

          TLFormulaSet* newSet;
          TLFormulaSet* nowSet;
          TLFormulaSet* nextSet;
          SCBoolean     isInitial;
    class TLStateList*  incoming;

          SCNatural      name;

   static SCNatural nextName;
};

class SCStream& operator<< (class SCStream&, TLNode&);
class SCStream& operator<< (class SCStream&, TLNode*);

#if _TL_INLINING_
#include "TLNode.inl.h"
#endif

#endif // _TLSTATE_H_
