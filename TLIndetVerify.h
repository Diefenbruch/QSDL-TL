/* File:            TLIndetVerify.h
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef __TLINDETVERIFY__

#define __TLINDETVERIFY__

#include "TL.h"
#include "TLState.h"
#include "SCL/SCIndetVal.h"

class TLIndetVerify : public SCIndetVal
{
  public:
                        TLIndetVerify (char*                pPhiStr,
                                       SCName2PropFuncPtr*  pName2func,
                                       SCNatural            pNumOfElems,
                                       SCTime               pStopTime,
                                       SCBoolean            pFindErrors,
                                       SCNatural            pMaxErrors,
                                       SCBoolean            pDeadCode,
                                       class SCStateSpace * stateSpace,
                                       class SCStateSpace * cycleStateSpace,
                                       SCNatural            pMaxVerifyDepth = kSCMaxDepth,
                                       SCName2PropFuncPtr * bAtom = NULL,
                                       SCBoolean            pTrueEquivEmpty = true,
                                       SCBoolean            pNowIsPureAtomic = true,
                                       SCBoolean            pNowDisplaysOnlyAtomics = true,
                                       SCBoolean            pExtendedAutomaton = true,
                                       SCBoolean            pSimplifyFormulae = true,
                                       SCBoolean            pGreedyAutomaton = true,
                                       SCBoolean            pAutoNegate = true);
                                       
                       ~TLIndetVerify (void);

    void                StartMessage (void);
    void                EndMessage (void);

    // The following three methods classify the reached system
    // state:
    
    SCErrorCode         IsErrorState (SCTimeEventSaveList *activeQueue);
    SCBoolean           IsLimitingState (SCTimeEventSaveList *activeQueue);
    SCBoolean           IsCycleStartState (void) const;
    SCBoolean           IsCycleEndState (class SCMem * state);
    SCNatural           NumOfSuccessors (void) const;
    
    class SCRunnable *  ChooseRunnable (class SCTimeEventSaveList *activeQueue);
    
    friend SCStream &   operator<< (SCStream& pStream,
                                    const TLIndetVerify& pData);
    virtual SCStream &  Display (SCStream &pStream) const;

           SCBoolean    IsFulFillable (void) const;

  private:

    void                SystemStateSize (SCSize *pSize) const;
    SCBoolean           StoreSystemState(class SCMem *state) const;
    SCBoolean           RestoreSystemState(class SCMem *state) const;

    /* Alle Datenmember sind privat */

    class TLBuechi*     buechi;
          SCNatural     nextInitialBuechiState;   // List index of buechi state.
                                                  
          TLState*      currentBuechiState;
};


#if !_SC_NOINLINES
  #include "TLIndetVerify.inl.h"
#endif


#endif  // __TLINDETVERIFY__
