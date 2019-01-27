/* File:            TL.h
   Author:          Marc Diefenbruch, Axel Hirche
   Project:         QUEST
   Date:            (C) 1997, 1998 University of Essen, Germany
*/

#ifndef _TL_H_
#define _TL_H_

#include "TLConfig.h"

#if _TL_DEBUG_
  #include "TLDebug.h"
#endif

#include "SCL/SCBasicTypes.h"

typedef unsigned char TLByte;

typedef enum
{
  TLLETTER_UNDEFINED = 0,
                      // ** Binary operators:
  AND,                // and operator
  OR,                 // or operator
  UNTIL,              // until operator
  V_OPER,             // V operator, dual to U
  WAITFOR,            // waitfor operator
  Z_OPER,             // Z operator, dual to W
  IMPLIES,            // implies operator
  LRIMPLIES,          // used to distinguish -> from <-
                      // will never be an actual operator.
  RLIMPLIES,          // s.a.
  EQUIVALENT,         // equivalence operator.
                      // ** Unary operators:
  ALWAYS,             // always operator
  EVENTUALLY,         // eventually operator
  NEXTTIME,           // nexttime operator
  NOT,                // negation operator for TLFormulaNOT
                      // ** Atomic propositions:
  F,                  // false
  T,                  // true
  ATOMIC,
  ATOMIC_NOT,         // After PushNegations, negation is considered to be
                      // atomic
  TLLETTER_MAX

} TLLetter;                                       // This is the alphabet
                                                  // for temporal formulae.

#define FIRST_PROPOSITION PROP1                   // Offset of the atomic
                                                  // propositions.

#define LAST_PROPOSITION PROP30

#define FIRST_OPERATOR AND
#define LAST_OPERATOR NOT

typedef enum TLValue
{
  TLFalse = 0,
  TLTrue,
  TLUnknown
} TLValue;                                        // We can't determine the
                                                  // SCBooleanean value of an
                                                  // arbitrary TLF. Only atomic
                                                  // propositions can be
                                                  // evaluated at any time.

typedef enum TLArity
{
  TLFORMUALTYPE_UNDEFINED = 0,                    // Undefined.
  TLAtomic,                                       // Atomic proposition.
  TLUnary,                                        // Unary formula.
  TLBinary                                        // Binary formula.
} TLArity;


typedef enum TLPrecedenceLevel
{
  PREC_LEVEL_0 = 0,
  PREC_LEVEL_1,
  PREC_LEVEL_2,
  PREC_LEVEL_3,
  PREC_LEVEL_MAX
} TLPrecedenceLevel;

#define PREC_LEVEL_HIGHEST (PREC_LEVEL_MAX - 1)   // Highest precedence level.

#define UNDEFINED_LISTINDEX UINT_MAX              // Unlikely, that any machine
                                                  // will have enough memory to
                                                  // ever reach that index :-).
                                                  // Yes, nobody thought that
                                                  // 640k could be a problem,
                                                  // I KNOW THAT!

#endif // _TL_H_
