/*
 * File:    TLHelp.cc
 * Project: QUEST
 * Author:  Axel M. Hirche, Marc Diefenbruch
 * Date:    (C) 1997 University of Essen, Germamy
 */

//#include <assert.h>
#include <string.h>

#include "SCL/SCStream.h"

#include "TLHelp.h"


#if _TL_DEBUG_
  #include <fstream>
  std::ofstream tldebug ("TLDebug.log");
#endif // _TL_DEBUG_

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif

void FatalError (const char* efile,
                       int   eline,
                 const char* what)
{
  assert (efile);
  assert (eline);
  assert (what);
  std::cerr << "***** ERROR at " << efile << ", line " << eline << ":" << std::endl;
  std::cerr << "      " << what << std::endl;
  std::cerr << "***** EXITING ******" << std::endl << std::endl;
  exit (-1);
}

void Warning (const char* efile,
                    int   eline,
              const char* what)
{
  assert (efile);
  assert (eline);
  assert (what);
  std::cerr << "+++++ WARNING at " << efile << ", line " << eline << ":" << std::endl;
  std::cerr << "      " << what << std::endl;
  std::cerr << "+++++ CONTINUING +++++" << std::endl << std::endl;
  return;
}


SCBoolean FalsePropFunc (void)                    // Don´t inline -- need address!
{
  return false;
}


SCBoolean TruePropFunc (void)                     // Don´t inline -- need address!
{
  return true;
}


char* StrDup (const char* src)                    // Duplicate a string. Allocate
                                                  // with new rather than malloc.
{
  assert (src);
  return strcpy (new char[strlen (src) + 1], src);
}


void ShowBits (      SCStream& out,
               const SCBitSet set)
{
  SCInteger i;                                    // Don't use SCNatural!!!

  for (i = SC_MAX_BITINDEX; i >= 0; i--)
  {
    out << ((set & (1ULL << i)) ? "1" : "0");
  }
}
