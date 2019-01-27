/*
 * File:    TLFormula.inl.h
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

#ifndef _TLFORMULA_INL_H_
#define _TLFORMULA_INL_H_

#include "SCL/SCObject.h"
#include "SCL/SCStream.h"
#include "TLHelp.h"

TLINLINE TLFormula::TLFormula (void)
{
  assert (false);                                 // Forbidden!!!
}


TLINLINE TLFormula::TLFormula (const TLLetter pOp,
                               SCNatural  pAcceptSetNo,
                               const SCObject*  pFather)
: SCObject (TL_FORMULA, pFather),
  op (pOp),
  acceptanceSetNo (pAcceptSetNo)
{
  /*empty */
}


TLINLINE TLFormula::TLFormula (const TLFormula& phi)
: SCObject (phi.GetType(),
            phi.GetParent()),
  op (phi.op),
  acceptanceSetNo (phi.acceptanceSetNo)
{
  /* empty */
}


TLINLINE TLFormula::TLFormula (const TLFormula* phi)
: SCObject (phi->GetType(),
            phi->GetParent()),
  op (phi->op),
  acceptanceSetNo (phi->acceptanceSetNo)
{
  /* empty */
}


TLINLINE TLLetter TLFormula::Operator (void) const
{
  return op;
}


TLINLINE SCBoolean TLFormula::SetAcceptanceSetNo (SCNatural pAcceptanceSetNo)
{
  acceptanceSetNo = pAcceptanceSetNo;
  return true;
}

TLINLINE SCNatural TLFormula::GetAcceptanceSetNo (void) const
{
  return acceptanceSetNo;
}


TLINLINE void TLFormula::Initialize (SCBoolean  pPartialRewrite,
                                     SCBoolean  pSimplifyFormulae)
{
  partialRewrite = pPartialRewrite;
  simplifyFormulae = pSimplifyFormulae;
}


TLINLINE SCStream& operator<< (SCStream& out,
                              const TLFormula& phi)
{
  return phi.Display (out);
}


TLINLINE SCStream& operator<< (SCStream& out,
                              const TLFormula* phi)
{
  return phi->Display (out);
}

#endif // _TLFORMULA_INL_H_
