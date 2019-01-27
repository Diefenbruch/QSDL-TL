/*
 * File:    TLParser.c
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germamny
 */

#include <string.h>
//#include <stdio.h>
#include "TLParserHelp.h"
#include "TLParser.h"
#include "TLLexer.h"
#include "TLHelp.h"

#include "TLFormula.h"
#include "TLFormulaALWAYS.h"
#include "TLFormulaAND.h"
#include "TLFormulaEQUIVALENT.h"
#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaIMPLIES.h"
#include "TLFormulaNEXTTIME.h"
#include "TLFormulaNOT.h"
#include "TLFormulaOR.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaWAITFOR.h"
#include "TLFormulaZ_OPER.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

extern SCName2PropFuncPtr* name2FuncTable;
extern SCNatural name2FuncTableElems;
extern TLFormula* result;

SCBoolean InitializeParser (const char*         source,
                            SCName2PropFuncPtr* pName2Func,
                            SCNatural           pnumOfElems)
{
  assert (pName2Func);
  assert (pnumOfElems);

  TLAssert (SetLexInputString (source), "Initialization of scanner failed.");
 

  name2FuncTable = pName2Func;
  name2FuncTableElems = pnumOfElems;
  return true;
}


SCBoolean CleanUpParser (void)
{
  return LexCleanUp();                            /* Clean up the lexer. */
}


SCPropFuncPtr Name2PropFuncPtr (char* s)
{
  SCNatural i;
  const char* str = "Failed look-up of atomic proposition ´%s´.";
  char* msg;
  
  for (i = 0; i < name2FuncTableElems; i++)
  {
    if (!strcmp (s, name2FuncTable[i].name))      // strcmp returns zero (boolean
                                                  // false) if the two strings
                                                  // are equal, nonzero otherwise.
      return name2FuncTable[i].Evaluate;
  }
  
  msg = new char[strlen (str) + strlen (s) +1];
  assert (msg);
  sprintf (msg, str, s);  
  TLAssert (false, msg);                          // This will call exit().
  delete[] msg;                                   // Has no effect.
  return NULL;                                    // Keep the compiler happy...
}


TLFormula* TLParse (void)
{
  yyparse();
  assert (result);
  return result;
}


TLFormula* NewUnaryFormula (TLLetter opr,
                            TLFormula* right)
{
  TLAssert (right, "Attempt to construct unary formula from NULL operand.");
  switch (opr)
  {
    case ALWAYS:
      return new TLFormulaALWAYS (right, true);
      break;

    case EVENTUALLY:
      return new TLFormulaEVENTUALLY (right, true);
      break;

    case NEXTTIME:
      return new TLFormulaNEXTTIME (right, true);
      break;

    case NOT:
      return new TLFormulaNOT (right, true);
      break;

    default:
      TLAssert (false, "Attempt to construct unary formula from illegal operator.");
      return NULL;                                // Keep the compiler from
                                                  // nagging.
  }
}

TLFormula* NewBinaryFormula (TLFormula* left,
                             TLLetter opr,
                             TLFormula* right)
{
  TLAssert (left, "Attempt to construct unary formula from NULL left operand.");
  TLAssert (right, "Attempt to construct unary formula from NULL right operand.");
  
  switch (opr)
  {
    case AND:
      return new TLFormulaAND (left, right);
      break;
      
    case OR:
      return new TLFormulaOR (left, right);
      break;
      
    case UNTIL:
      return new TLFormulaUNTIL (left, right);
      break;
      
    case V_OPER:
      return new TLFormulaV_OPER (left, right);
      break;
      
    case WAITFOR:
      return new TLFormulaWAITFOR (left, right);
      break;
      
    case Z_OPER:
      return new TLFormulaZ_OPER (left, right);
      break;
      
    case LRIMPLIES:
      return new TLFormulaIMPLIES (left, right);
      break;

    case RLIMPLIES:
      return new TLFormulaIMPLIES (right, left);
      break;

    case EQUIVALENT:
      return new TLFormulaEQUIVALENT (left, right);
      break;
      
    default:
      TLAssert (false, "Attempt to construct binary formula from illegal operator.");
      return NULL;                                // Keep the compiler from
                                                  // nagging.
  }
}
