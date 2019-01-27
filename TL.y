%{ /* DO NOT EDIT THIS LINE!!! */
/*
 * File:    TL.y
 * Project: QUEST
 * Author:  Marc Diefenbruch, Axel M. Hirche
 * Date:    (C) 1997, 1998 University of Essen, Germany
 */

//#include <string.h>
#include "TL.h"
#include "TLParserHelp.h"
#include "TLParser.h"
#include "TLHelp.h"

#include "TLFormulaALWAYS.h"
#include "TLFormulaAND.h"
#include "TLFormulaAtomic.h"
#include "TLFormulaEQUIVALENT.h"
#include "TLFormulaEVENTUALLY.h"
#include "TLFormulaFALSE.h"
#include "TLFormulaIMPLIES.h"
#include "TLFormulaNEXTTIME.h"
#include "TLFormulaNOT.h"
#include "TLFormulaOR.h"
#include "TLFormulaTRUE.h"
#include "TLFormulaUNTIL.h"
#include "TLFormulaV_OPER.h"
#include "TLFormulaWAITFOR.h"

#ifdef DMALLOC
  #include <dmalloc.h>
#endif

#define YYERROR_VERBOSE 1                         /* Makes parser issue verbose
                                                     error messages indicating
                                                     the token that lead to the
                                                     parse error. */
                                                    
#define YYDEBUG 1                                 /* Enable debugging code. */


TLFormula* result = NULL;                         /* Use this to retrieve
                                                     the result, as the top rule
                                                     is recursive and can´t
                                                     return a result. */

SCName2PropFuncPtr* name2FuncTable;               /* Translation table to
                                                     translate names to
                                                     propFuncPtr. */

SCNatural name2FuncTableElems = 0;               /* Number of entries in
                                                     translation table. */

%}


%union{
  TLFormula*  formulaPtr;
  TLLetter    byteVal;
  char*       stringVal;
}

%token <stringVal> ATOMICtoken
%token <byteVal> ALWAYStoken
%token <byteVal> ANDtoken
%token <byteVal> EQUIVALENTtoken
%token <byteVal> EVENTUALLYtoken
%token <byteVal> FALSEtoken
%token <byteVal> LRIMPLIEStoken
%token <byteVal> RLIMPLIEStoken
%token <byteVal> NEXTTIMEtoken
%token <byteVal> NOTtoken
%token <byteVal> ORtoken
%token <byteVal> TRUEtoken
%token <byteVal> UNTILtoken
%token <byteVal> V_OPERtoken
%token <byteVal> WAITFORtoken
%token <byteval> Z_OPERtoken
%token LEFTPARtoken
%token RIGHTPARtoken

%type <formulaPtr> expr0
%type <byteVal> expr0_op
%type <formulaPtr> expr1
%type <byteVal> expr1_op
%type <formulaPtr> expr2
%type <byteVal> expr2_op
%type <formulaPtr> expr3

%start expr0

%%

expr0:      expr1 { result = $1;
                    $$ = result; } |
            expr1 expr0_op expr0 { result = NewBinaryFormula ($1, $2, $3);
                                   $$ = result; }
                                                  /* Use result to retrieve
                                                     the formula after parsing
                                                     is done. yyparse has no
                                                     return value ;-) */
            ;

expr0_op:   ANDtoken { $$ = AND; } |
            ORtoken { $$ = OR; }
            ;

expr1:      expr2 |
            expr2 expr1_op expr1 { $$ = NewBinaryFormula ($1, $2, $3); }
            ;

            
expr1_op:   UNTILtoken { $$ = UNTIL;} |
            V_OPERtoken { $$ = V_OPER; }|
            WAITFORtoken { $$ = WAITFOR; } |
            Z_OPERtoken { $$ = Z_OPER; } |
            LRIMPLIEStoken { $$ = LRIMPLIES; } |
            RLIMPLIEStoken { $$ = RLIMPLIES; } |
            EQUIVALENTtoken { $$ = EQUIVALENT; }
            ;

expr2:      expr3 |
            expr2_op expr2 { $$ = NewUnaryFormula ($1, $2); }
            ;

expr2_op:   ALWAYStoken { $$ = ALWAYS; } |
            EVENTUALLYtoken { $$ = EVENTUALLY; } |
            NEXTTIMEtoken { $$ = NEXTTIME; } |
            NOTtoken { $$ = NOT; }
            ;

expr3:      ATOMICtoken { $$ =  new TLFormulaAtomic ($1,
                                                     Name2PropFuncPtr ($1)); }
                                                  /* NOTE: $1 has been allocated
                                                       with new in TL.l, and
                                                       must be deleted by the
                                                       new formula! */ |
            TRUEtoken { $$ = new TLFormulaTRUE(); } |
            FALSEtoken { $$ = new TLFormulaFALSE(); } |
            LEFTPARtoken expr0 RIGHTPARtoken { $$ = $2; }
            ;

%%

