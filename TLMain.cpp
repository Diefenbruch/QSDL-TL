/*
 * File:   Main.cc
 * Project: QUEST
 * Author: Axel Hirche, Marc Diefenbruch
 * Date:   (C) 1997, 1998 University of Essen, Germany
 */

//#include <string.h>
#include "SCL/SCStream.h"

#include "TL.h"
#include "TLFormula.h"
#include "TLFormulaNOT.h"
#include "TLFormulaSet.h"
#include "TLParser.h"
#include "TLState.h"
#include "TLStateList.h"
#include "TLNode.h"
#include "TLBuechi.h"
#include "TLHelp.h"

#include "SCL/SCListIter.h"

#if _SC_DMALLOC
  #include <dmalloc.h>
#endif


SCBoolean a (void)
{
  return true;
}

SCBoolean b (void)
{
  return false;
}

SCBoolean c (void)
{
  return false;
}

SCBoolean d (void)
{
  return true;
}

SCBoolean e (void)
{
  return false;
}

SCBoolean f (void)
{
  return true;
}

SCBoolean g (void)
{
  return false;
}

SCBoolean h (void)
{
  return true;
}


void PrintHelp (char* myName)
{
  cerr << "usage:   " << myName << " [-a|-d|-g|-e|-n|-s|-x]* \"<formula>\"" << endl;
  cerr << "  -a  when comparing states, use only the atomic propositions" << endl;
  cerr << "      in NOW for comparison." << endl;
  cerr << "  -d  When displaying states, display only the atomic propositions" << endl;
  cerr << "      in NOW." << endl;
  cerr << "  -e  Do not insert T (true) into formula sets, i.e. treat {T} as {}." << endl;
  cerr << "  -f  Same as \"-a -d -g -e -s -x\"" << endl;
  cerr << "  -g  Construct the links between the states in such a way that the" << endl;
  cerr << "      automaton will reach an acepting state as quickly as possible." << endl;
  cerr << "  -h  Display this message." << endl;
  cerr << "  -n  Automatically prepend a not (~) to the formula." << endl;
  cerr << "  -s  Use some simple equivalences to simplify the formula, e.g." << endl;
  cerr << "      <><>a <-> <>a, or a && ~a <-> F." << endl;
  cerr << "  -x  Construct automaton that can handle <>, [], W and Z without" << endl;
  cerr << "      rewriting the formula." << endl << endl;
  cerr << "Valid values for atomic propositions are the letters \"a\" through \"h\"" << endl;
  cerr << "and the values \"F\" for false and \"T\" for true." << endl;
  cerr << "Valid operators are ~, X, <>, [], ->, <->, U, V, W, Z, ||, &&." << endl;
  cerr << "example: " << myName << " -a -x \"a U b\"" << endl;
}

int main (int argc, char** argv)
{
  char*               phiStr;
  SCBoolean           trueEquivEmpty = false;
  SCBoolean           nowIsPureAtomic = false;
  SCBoolean           nowDisplaysOnlyAtomics = false;
  SCBoolean           extendedAutomaton = false;
  SCBoolean           simplifyFormulae = false;
  SCBoolean           greedyAutomaton = false;
  SCBoolean           autoNegate = false;
  SCName2PropFuncPtr *name2Func = new SCName2PropFuncPtr[8];
  TLBuechi*           myBuechi = NULL;
  
  
  if (argc > 1)                                   // At least program name and formula.
  {
    for (int i = 1; i < argc ; i++)               // Ignore argv[0], which is program name.
    {
      assert (argv[i]);
      if (*argv[i] == '-')                        // It is an option.
      {
        if (strlen (argv[i]) != 2)                // Option syntax is -<letter>
        {
          cerr << "unrecognized option: " << argv[i] << endl;
          exit (-1);
        }

        if (*(argv[i] + 1) == 'h')                // User wants help...
        {
          PrintHelp(argv[0]);
          exit (0);
        }
         
        switch (*(argv[i] + 1))                   // Use the 2nd character.
        {
          case 'e':                               // trueEquivEmpty
            trueEquivEmpty = true;
            break;
            
          case 'd':                               // nowDisplaysOnlyAtomics
            nowDisplaysOnlyAtomics = true;
            break;
            
          case 'a':                               // nowIsPureAtomic
            nowIsPureAtomic = true;
            break;
            
          case 'x':                               // extendedAutomaton
            extendedAutomaton = true;
            break;
            
          case 's':                               // simplifyFormulae
            simplifyFormulae = true;
            break;
            
          case 'g':                               // greedyAutomaton
            greedyAutomaton = true;
            break;
            
          case 'n':                               // autoNegate
            autoNegate = true;
            break;

          case 'f':
            trueEquivEmpty = true;
            nowDisplaysOnlyAtomics = true;
            nowIsPureAtomic = true;
            extendedAutomaton = true;
            simplifyFormulae = true;
            greedyAutomaton = true;
            break;

          case 'h':                               // Can't do that babe ;-)
            cerr << "can't mix -h with other options!" << endl;
            exit (-1);
            break;
          
          default:
            cerr << "unrecognized option: " << argv[i] << endl;
            exit (-1);
            break;
        }
      }
      else                                        // The formula.
      {
        phiStr = StrDup (argv[i]);
      }
    }
  }  
  else
  {
    cerr << "usage: " << argv[0] << " [-a|-d|-g|-e|-n|-s|-x]* \"<formula>\"" << endl;
    cerr << "for help type " << argv[0] << " -h" << endl;
    exit (-1);
  }
       
  name2Func[0].name = "a";                        // Translation table
  name2Func[0].Evaluate = a;                             // for translation from
  name2Func[1].name = "b";                        // names to proposition
  name2Func[1].Evaluate = b;                             // functions.
  name2Func[2].name = "c";
  name2Func[2].Evaluate = c;
  name2Func[3].name = "d";
  name2Func[3].Evaluate = d;
  name2Func[4].name = "e";
  name2Func[4].Evaluate = e;
  name2Func[5].name = "f";
  name2Func[5].Evaluate = f;
  name2Func[6].name = "g";
  name2Func[6].Evaluate = g;
  name2Func[7].name = "h";
  name2Func[7].Evaluate = h;

  myBuechi = new TLBuechi (phiStr,
                           name2Func,
                           8,
                           trueEquivEmpty,
                           nowIsPureAtomic,
                           nowDisplaysOnlyAtomics,
                           extendedAutomaton,
                           simplifyFormulae,
                           greedyAutomaton,
                           autoNegate);

  {
    SCNatural numOfTrans = 0;
    SCNatural numOfBogusAccept = 0;
    SCNatural numOfReallyAccept = 0;
    SCListIter<TLState> myIter (*myBuechi->GetStateList());
    TLState* tmpState;
    
    for (tmpState = myIter++; tmpState; tmpState = myIter++)
    {
      numOfTrans += tmpState->GetOutEdges()->NumOfElems();
      if (tmpState->IsAcceptingState())
      {
        if (tmpState->isReallyAccepting)
          numOfReallyAccept++;
        else
          numOfBogusAccept++;
      }
    }
    cout << myBuechi->GetNumOfStates();
    cout << '\t' << numOfTrans;
    cout << '\t' << myBuechi->GetNumOfAcceptanceSets();
    cout << '\t' << numOfReallyAccept;
    cout << '\t' << numOfBogusAccept << endl;
  }


//  cout << "myBuechi->GetReferenceAcceptanceSet() == ";
//  ShowBits (cout, myBuechi->GetReferenceAcceptanceSet());
//  cout << endl;

  delete myBuechi;
  delete[] name2Func;
  delete[] phiStr;
  
  return 0;
}
