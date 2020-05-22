%{ /* DO NOT EDIT THIS LINE!!! */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "TL.h"
#include "TLHelp.h"
#include "TLLexer.h"
#include "TLFormula.h"
#include "TL.tab.h"


#ifdef DMALLOC
#include <dmalloc.h>
#endif

void yyerror (char* s)
{
  FatalError ("input string", 1, s);
}

%}

%option noyywrap

ALWAYSsym		"[]"
ANDsym			"&&"
EQUIVALENTsym	"<->"
EVENTUALLYsym	"<>"
FALSEsym		"FALSE"
LRIMPLIESsym	"->"
RLIMPLIESsym	"<-"
LEFTPARsym		"("
NEXTTIMEsym		"X"
NOTsym			"~"
ORsym			"||"
RIGHTPARsym		")"
TRUEsym			"TRUE"
UNTILsym		"U"
V_OPERsym		"V"
WAITFORsym		"W"
Z_OPERsym		"Z"

white_space		(" "|\t|\n)
letter			[a-zA-Z]
digit			[0-9]
name			({letter}|{digit}|"_")+


%%
{white_space}			{  ;                    /* Do nothing. */
						}
						
{FALSEsym}				{ return FALSEtoken;
						}
						
{TRUEsym}				{ return TRUEtoken;
						}
						
{NOTsym}				{ return NOTtoken;
						}

{ALWAYSsym}				{ return ALWAYStoken;
						}

{EVENTUALLYsym}			{ return EVENTUALLYtoken;
						}

{EQUIVALENTsym}			{ return EQUIVALENTtoken;
						}

{NEXTTIMEsym}			{ return NEXTTIMEtoken;
						}

{ANDsym}				{ return ANDtoken;
						}

{ORsym}					{ return ORtoken;
						}

{UNTILsym}				{ return UNTILtoken;
						}

{V_OPERsym}				{ return V_OPERtoken;
						}

{WAITFORsym}			{ return WAITFORtoken;
						}

{Z_OPERsym}				{ return Z_OPERtoken;
						}

{LRIMPLIESsym}			{ return LRIMPLIEStoken;
						}

{RLIMPLIESsym}			{ return RLIMPLIEStoken;
						}

{LEFTPARsym}			{ return LEFTPARtoken;
						}

{RIGHTPARsym}			{ return RIGHTPARtoken;
						}

{name}					{         int i = 0;       /* AMH */
                          yylval.stringVal = new char[yyleng + 1];
                                                     /* Allow for trailing \0. */
                          yylval.stringVal = (char*) strncpy ((char*) yylval.stringVal,
                                                              (char*) yytext,
                                                              (size_t) yyleng);
                                                  /* Copy the string. */

                          yylval.stringVal[yyleng] = '\0';
                                                  /* Set end of string. */
                                                  
                          i = 0;                  /* AMH begin */
                          while (yylval.stringVal[i])
                          {
                            assert ((i >= 0) && (i < yyleng));
                            yylval.stringVal[i] = tolower (yylval.stringVal[i]);
                            i++;
                          }                       /* AMH end */

                          return ATOMICtoken;     /* All done. */
                        }

.						{ assert (false);
						}
%%

YY_BUFFER_STATE myBuf;                            /* internal buffer of flex. */

SCBoolean SetLexInputString (const char *inString)/* Switch to string. */
{
  myBuf = yy_scan_string (inString);
  return (myBuf != NULL);                         /* Return non-zero on error. */
}

SCBoolean LexCleanUp(void)                        /* Clean up internals. */
{
  yy_delete_buffer (myBuf);
  return true;
}

