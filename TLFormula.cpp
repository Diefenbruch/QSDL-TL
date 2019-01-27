/*
 * File:     TLFormula.cc
 * Project:  QUEST
 * Author:   Marc Diefenbruch, Axel M. Hirche
 * Date:     (C) 1997, 1998 University of Essen, Germany
 */

#include "SCL/SCObject.h"
#include "TLFormula.h"

#if _TL_INLINING == 0
#include "TLFormula.inl.h"
#endif

#include "TLFormulaUnary.h"
#include "TLFormulaBinary.h"

#include "TLFormulaSet.h"                         // Can't move this up, as it
                                                  // includes TLFormula.h!
#include "SCL/SCListIter.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

// ********** static data members *************

SCBoolean     TLFormula::partialRewrite = false;
SCBoolean     TLFormula::simplifyFormulae = false;


// ********** Methods *************

TLFormula::~TLFormula (void)
{
  op = TLLETTER_UNDEFINED;
  acceptanceSetNo = UNDEFINED_LISTINDEX;
}


SCNatural TLFormula::NumOfSymbols (void) const
{
  return 1;                                       // Only the operator.
}


SCStream& TLFormula::Display (SCStream& out) const
{
  switch (op)
  {
    case AND:
      return out << "&&";
    case OR:
      return out << "||";
    case UNTIL:
      return out << "U";
    case V_OPER:
      return out << "V";
    case WAITFOR:
      return out << "W";
    case Z_OPER:
      return out << "Z";
    case IMPLIES:
      return out << "->";
    case EQUIVALENT:
      return out << "<->";
    case ALWAYS:
      return out << "[]";
    case EVENTUALLY:
      return out << "<>";
    case NEXTTIME:
      return out << "X";
    case NOT:
      return out << "~";
    default:
      assert (false);                             // Should not be here!
      return out;
  }
}


SCBoolean TLFormula::operator== (const TLFormula& pPhi) const
{
  if (op != pPhi.op)
    return false;
  
  return true;
}


SCBoolean TLFormula::operator== (const TLFormula* pPhi) const
{
  return *this == *pPhi;
}


SCBoolean TLFormula::operator!= (const TLFormula& pPhi) const
{
  return !(*this == pPhi);
}


SCBoolean TLFormula::operator!= (const TLFormula* pPhi) const
{
  return !(*this == *pPhi);
}


SCBoolean TLFormula::HasAcceptanceStateSet (void) const
{
  return false;                                   // will be modified by <>, U, Z.
}

