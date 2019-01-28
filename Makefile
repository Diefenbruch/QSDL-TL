#
# Makefile fuer die TL
#
#
# Author: Marc Diefenbruch
# $Date: 1998/02/19 16:17:59 $
#
# (C) 1996 Universitaet GH Essen
#
# Dieses Makefile stellt folgende Operationen zur Verfuegung:
#
# -) make [all]     : Library und Testprogramm erzeugen
# -) make lib       : Library erzeugen
# -) make release   : Neue Release der TL fuer Benutzer zugaenglich machen
# -) make install   :  "      "     "   "   "     "         "         "
# -) make install-lib: Neue Version der TL-Bibiothek zugaenglich machen
# -) make install-includes: Neue Version der TL-Header_files zugaenglich machen
# -) make checkout  : alle Projektdateien auschecken
# -) make checkout-lock: alle Projektdateien zum Aendern auschecken
# -) make depend    : alle Abhaengigkeiten zwischen Projektdateien feststellen
# -) make clean     : Objektdateien (*.o) und temporaere Dateien entfernen
# -) make veryclean : make clean + rcsclean + alle Postscriptdateien entfernen
# -) make git-pull  : pull sources from github
# -) make git-push  : push sources to github
# -) make git-add   : add changed sources to git staging
# -) make git-commit: commit staged sources to git HEAD
# -) make backup    : Backup von allen *.cpp *.h Dateien und dem Makefile
# -) make find-error: Compilierungsfehler anzeigen
#
# Der Aufbau dieses Makefiles gliedert sich wie folgt:
#
#  1. Makefiledirektiven
#  2. Pfade und Dateinamen
#  3. Programme, Kommandos, Kommandooptionen
#  4. Compilierungs- und Linkeroptionen
#  5. Quelldateien des Projekts
#  6. Objektdateien des Projekts
#  7. Makefileregeln (Operationen, s.o.)
#

###############################
# Figure out host system type #
###############################

## Don't rely on $ being set correctly!
## Try to figure it out ourselves:

## Prevent make from interpreting special characters:
SCRIPT := \
	case `uname -s` in\
    	Linux)	case `uname -m` in\
					i?86) echo ix86-linux;;\
					arm*) echo arm-linux;;\
					sparc) echo sparc-linux;;\
					*) echo unknown-linux;;\
				esac;;\
		SunOS)	echo `uname -p`-SunOS;;\
		*) echo unknown-unknown;;\
	esac

## Run script and store result in variable:
QUEST_HOSTTYPE := $(shell $(SCRIPT))



##########################
# 0. Globale Umschalter: #
##########################

ifeq ($(QUEST_HOSTTYPE), sparc-SunOS)

#TOOLS = SUN
TOOLS = GNU

else

TOOLS = GNU

endif

#PROFILING = yes
PROFILING = no

##########################
# 1. Makefiledirektiven: #
##########################

.SILENT:
                         # alle Make Operationen ohne Ausgaben

.PHONY: Makefile default clean all release .depend \
        install install-lib install-includes release \
        postscript print
                         # Welche Operationen sollen gespraechig sein?

.SUFFIXES: .y .c .l .cpp .h .o
                         # verwendete Dateiendungen

############################
# 2. Pfade und Dateinamen: #
############################

INCDIR = ../../include
                         # Verzeichnis der TL-Includedateien fuer die
                         # Benutzer der TL

LIBDIR = ../../lib/$(QUEST_HOSTTYPE)
                         # Verzeichnis der TL-Library fuer die
                         # Benutzer der TL
BINDIR = ../../bin/$(QUEST_HOSTTYPE)
                         # Verzeichnis in dem die Binaerdateien gespeichert
                         # werden sollen
OBJBASEDIR = obj
                         # Verzeichnis unter dem die Objektdateien aller Hosts
                         # gespeichert werden sollen
OBJDIR = $(OBJBASEDIR)/$(QUEST_HOSTTYPE)
                         # Verzeichnis in dem die Objektdateien gespeichert
                         # werden sollen
PSDIR = ps
                         # Directory in dem die Postscriptversionen der
                         # Dateien gespeichert werden sollen
LOGFILE = $(USER).$(QUEST_HOSTTYPE).make.log
                         # Protokollierungsdatei fuer den make-Vorgang
DEPFILE = .depend.$(QUEST_HOSTTYPE)
                         # Dependency-Datei (automatisch generiert)

OUTPUT  = $(OBJDIR)/libTL.a

TEST_OUTPUT = $(OBJDIR)/verifier

LIBS = -lTL -lSCL

BACKUP = tl
                         # Name des Backupfiles (ohne Endungen!)

TEMPLATE_INST_DIR = Templates.DB

##############################################
# 3. Programme, Kommandos, Kommandooptionen: #
##############################################

SHELL = /bin/sh
                         # Shell
LEX = flex
                         # Kommando zum Starten des lexikalischen Analysators
LEXFLAGS = -i
                         # Flags fuer Lexer-Generator
YACC = bison
                         # Kommando zum Starten des Parser-Generators
YACCFLAGS = -d -v
                         # Flags fuer Parser-Generator
TAR = tar cf
                         # Befehl zum Erzeugen eines Sourcecode-Archievs
UNTAR = tar xf
                         # Befehl zum Expandieren eines Sourcecode-Archievs
TAR_SUFFIX = tar
                         # Endung welche das tar-Kommando verwendet
COMPRESS = gzip -9
                         # Befehl zum Komprimieren von Dateien
UNCOMPRESS = gzip -d
                         # Befehl zum Dekomprimieren von Dateien

COMPRESS_SUFFIX = gz
                         # Endung welche das Komprimierungsprogramm verwendet
EDITOR = nano
                         # Name des verwendeten Editors

GIT = git                # git

TAGS = ctags -t
                         # Programm zum Erzeugen von Sourcebrowsing-Infos
                         # (wo ist eine bestimmte Funktion definiert?, etc)
MAKE_PS = a2ps
                         # Kommando zum Erzeugen von Postscript aus ASCII
MAKE_PS_FLAGS = -o
                         # Option fuer MAKE_PS
PS_SUFFIX = ps

PRINT = lp -c -d $(PRINTER)
                         # Druckkommando

ifeq ($(TOOLS), GNU)     # GNU-Version ?

CC = gcc
                         # Name des C-Compilers
C++ = g++
                         # Name des C++-Compilers

AR = ar
                         # Name des Archivers (zum Erzeugen von Libraries)
ARFLAGS = r
                         # Flags fuer den Archiver
else                     # SUN-Version

CC = cc
                         # Name des C-Compilers
C++ = CC
                         # Name des C++-Compilers
AR = $(C++)
                         # Name des Archivers (zum Erzeugen von Libraries)
ARFLAGS = -xar -o
                         # Flags fuer den Archiver
endif

RCSCLEAN = rcsclean
                         # Befehl zum "Aufraeumen" des Projekts (Loeschen
                         # der nicht mit Lock Option "ausgecheckten"
                         # Dateien
RM = /bin/rm -f
                         # Befehl zum Loeschen von Dateien
MV = /bin/mv
                         # Befehl zum Verschieben von Dateien
CP = /bin/cp -p
                         # Befehl zum Verschieben von Dateien
CHMOD = /bin/chmod
                         # Befehl zum Aendern der Dateiattribute
TOUCH = touch
                         # Befehl zum Aktualisieren des Dateidatums
MKDIR = mkdir -p
                         # Befehl zum Erzeugen von Directories
ifeq ($(TOOLS), GNU)     # GNU-Version ?

MAKE_DEPEND = $(C++) -M
                         # Befehl zum Erzeugen der Abhaengigkeiten

else

MAKE_DEPEND = $(C++) -xM
                         # Befehl zum Erzeugen der Abhaengigkeiten

endif

STRIP = strip
                         # Befehl zum entfernen von Symbolen aus Binaerfiles
CI = ci

SED = sed
                         # Name des Stream-Editors sed
COFLAGS += -M -q
                         # Tell co to set the file date to the date of the
                         # last modification of the file.

#########################################
# 4. Compilierungs- und Linkeroptionen: #
#########################################

INCLUDES = -I$(QUEST_ADDITIONAL_INC_DIR) -I. -I$(INCDIR) 
                         # Include-Verzeichnisse fuer die Compiler
                         # QUEST_ADDITIONAL_INC_DIRS may be used to specify
                         # system specific include pathes.

CTHREAD_TYPE = $(QUEST_THREAD_TYPE)
                         # Verwendete Threads (Solaris, PThreads, etc.)

ifeq ($(TOOLS), GNU)     # GNU-Version ?

CDEBUG = -O6 -pipe
#CDEBUG += -DDMALLOC -DDMALLOC_FUNC_CHECK
                         # Debug-/Optimierungsoptionen

CFLAGS = -Wall
#-pedantic
                         # Compilierungsoptionen


TFLAGS = -fno-implicit-templates

LFLAGS = $(CDEBUG)
                         # Linkeroptionen


ifeq ($(PROFILING), yes) # Profiling einschalten ?

CFLAGS += -pg
LFLAGS += -pg

endif

else                     # Sun-Version !

CDEBUG = -O
#CDEBUG += -DDMALLOC -DDMALLOC_FUNC_CHECK
                         # Debug-/Optimierungsoptionen
CFLAGS = -mt -DUSERNAME=$(USER)
                         # Compilierungsoptionen

LFLAGS = $(CDEBUG) -mt
                         # Linkeroptionen

CFLAGS +=

ifeq ($(PROFILING), yes) # Profiling einschalten ?

CFLAGS += -xpg
LFLAGS += -xpg

endif

endif

CFLAGS += $(CDEBUG)
#CFLAGS += $(CTHREAD_TYPE)

#################################
# 5. Quelldateien des Projekts: #
#################################

YFILES = TL.y

LFILES = TL.l

YOUTPUT = TL.tab.c

LOUTPUT = lex.yy.c

TMPHEADERS =\
  $(YOUTPUT:.c=.h)

TMPSRCS =\
  $(YOUTPUT)\
  $(LOUTPUT)

SRCS = \
	TLDebug.cpp \
	TLFormula.cpp \
	TLFormulaALWAYS.cpp \
	TLFormulaAND.cpp \
	TLFormulaAtomic.cpp \
	TLFormulaAtomic_NOT.cpp \
	TLFormulaBinary.cpp \
	TLFormulaEVENTUALLY.cpp \
	TLFormulaEQUIVALENT.cpp \
	TLFormulaFALSE.cpp \
	TLFormulaIMPLIES.cpp \
	TLFormulaNEXTTIME.cpp \
	TLFormulaNOT.cpp \
	TLFormulaOR.cpp \
	TLFormulaSet.cpp \
	TLFormulaTRUE.cpp \
	TLFormulaUNTIL.cpp \
	TLFormulaUnary.cpp \
	TLFormulaV_OPER.cpp \
	TLFormulaWAITFOR.cpp \
	TLFormulaZ_OPER.cpp \
	TLHelp.cpp \
	TLNode.cpp \
	TLParser.cpp \
	TLParserHelp.cpp \
	TLState.cpp \
	TLStateList.cpp \
	TLBuechi.cpp \
	TLIndetVerify.cpp


INSTANT = \
	TLTemplates.cpp

INSTALL_INLINES =

INLINES = \
	TLBuechi.inl.h \
	TLFormula.inl.h \
	TLFormulaALWAYS.inl.h \
	TLFormulaAND.inl.h \
	TLFormulaAtomic.inl.h \
	TLFormulaAtomic_NOT.inl.h \
	TLFormulaBinary.inl.h \
	TLFormulaEVENTUALLY.inl.h \
	TLFormulaEQUIVALENT.inl.h \
	TLFormulaFALSE.inl.h \
	TLFormulaIMPLIES.inl.h \
	TLFormulaNEXTTIME.inl.h \
	TLFormulaNOT.inl.h \
	TLFormulaOR.inl.h \
	TLFormulaSet.inl.h \
	TLFormulaTRUE.inl.h \
	TLFormulaUNTIL.inl.h \
	TLFormulaUnary.inl.h \
	TLFormulaV_OPER.inl.h \
	TLFormulaWAITFOR.inl.h \
	TLFormulaZ_OPER.inl.h \
	TLIndetVerify.inl.h \
	TLNode.inl.h \
	TLState.inl.h \
	TLStateList.inl.h


TEMPLATES = \
    TLStack.tmpl.h

HDRS = \
	TLStack.h \
	TL.h \
	TLBuechi.h \
	TLBuechiHelp.h \
	TLConfig.h \
	TLDebug.h \
	TLFormula.h \
	TLFormulaALWAYS.h \
	TLFormulaAND.h \
	TLFormulaAtomic.h \
	TLFormulaAtomic_NOT.h \
	TLFormulaBinary.h \
	TLFormulaEVENTUALLY.h \
	TLFormulaEQUIVALENT.h \
	TLFormulaFALSE.h \
	TLFormulaIMPLIES.h \
	TLFormulaNEXTTIME.h \
	TLFormulaNOT.h \
	TLFormulaOR.h \
	TLFormulaSet.h \
	TLFormulaTRUE.h \
	TLFormulaUNTIL.h \
	TLFormulaUnary.h \
	TLFormulaV_OPER.h \
	TLFormulaWAITFOR.h \
	TLFormulaZ_OPER.h \
	TLHelp.h \
	TLIndetVerify.h \
	TLLexer.h \
	TLNode.h \
	TLParser.h \
	TLParserHelp.h \
	TLState.h \
	TLStateList.h

TEST_SRCS =\
	TLMain.cpp


##################################
# 6. Objektdateien des Projekts: #
##################################

HEADERS	= $(HDRS) $(TEMPLATES)
SOURCES = $(SRCS) $(INSTANT)
TMP_OBJS = $(addprefix $(OBJDIR)/, $(TMPSRCS:.c=.o))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o)) $(TMP_OBJS)
TEST_OBJS = $(addprefix $(OBJDIR)/, $(TEST_SRCS:.cpp=.o))
PSFILES	= $(HEADERS:.h=.ps)

######################
# 7. Makefileregeln: #
######################


lib: clean-rubbish $(OUTPUT)

all: clean-rubbish $(OUTPUT) test

$(OUTPUT): $(OBJS)
	echo Constructing $(OUTPUT) ...
	$(AR) $(ARFLAGS) $(OUTPUT) $(OBJS) \
		2>> $(LOGFILE)

test: clean-rubbish $(OUTPUT) $(TEST_OBJS)
	@echo Linking $(TEST_OUTPUT) ...
	$(C++) $(CDEBUG) \
		-o $(TEST_OUTPUT)\
		-L $(OBJDIR) \
		-L $(LIBDIR) \
		$(TEST_OBJS) \
		$(LIBS) \
		2>> $(LOGFILE)

#
# THE FOLLOWING RULES DEPEND ON THE ORDER OF THE DEPENDENCIES LIST!
# 
# The rule $< will return the first dependency in the dependency list.
# If you change the dependency list, make sure that the dependency you want
# to process with the commands of the rule is first in the list!!!
#


$(LOUTPUT): $(LFILES) $(TMPHEADERS)
	@echo Lexing $< ...
	$(LEX) $(LEXFLAGS) $< 2>> $(LOGFILE)

$(TMPHEADERS) : $(YFILES) $(YOUTPUT)
	@echo Yaccing $< ...
	$(YACC) $(YACCFLAGS) $< 2>> $(LOGFILE)

$(YOUTPUT): $(YFILES)
	@echo Yaccing $< ...
	$(YACC) $(YACCFLAGS) $< 2>> $(LOGFILE)

$(OBJDIR)/%.o : %.cpp
	echo Compiling $< ...
	$(C++) -c $(CFLAGS) $(INCLUDES) -o $@  $< 2>>$(LOGFILE)

$(OBJDIR)/%.o: %.c 
	@echo Compiling $< ...
	$(C++) -c $(CFLAGS) $(TFLAGS) $(PFLAGS) $(DEFINES) $(INCLUDES) $< -o $@ 2>> $(LOGFILE)

$(OBJBASEDIR):
	if [ ! \( -d $(OBJBASEDIR) \) ]; then \
    echo Creating $(OBJBASEDIR) ...; \
    $(MKDIR) $(OBJBASEDIR); fi

$(OBJDIR): $(OBJBASEDIR)
	if [ ! \( -d $(OBJDIR) \) ]; then \
		echo Creating $(OBJDIR) ...; \
		$(MKDIR) $(OBJDIR); fi

$(LIBDIR):
	if [ ! \( -d $(LIBDIR) \) ]; then \
		echo Creating $(LIBDIR) ...; \
		$(MKDIR) $(LIBDIR); fi

$(BINDIR):
	if [ ! \( -d $(BINDIR) \) ]; then \
		echo Creating $(BINDIR) ...; \
		$(MKDIR) $(BINDIR); fi

$(PSDIR):
	if [ ! \( -d $(PSDIR) \) ]; then \
		echo Creating $(PSDIR) ...; \
		$(MKDIR) $(PSDIR); fi

$(INCDIR): 
	@if [ ! \( -d $(INCDIR) \) ]; then \
		echo Creating $(INCDIR) ...; \
		$(MKDIR) $(INCDIR); fi

$(INCDIR)/TL: $(INCDIR)
	@if [ ! \( -d $(INCDIR)/TL \) ]; then \
		echo Creating $(INCDIR)/TL ...; \
		$(MKDIR) $(INCDIR)/TL; fi

$(DEPFILE):
	$(TOUCH) $(DEPFILE)

%.ps : %.h
	echo Generating   $(PSDIR)/$(notdir $@) form $< ...
	$(MAKE_PS) $(MAKE_PS_FLAGS) $(PSDIR)/$(notdir $@) $<

install-lib: $(OUTPUT) $(LIBDIR)
	echo Deleting old library from $(LIBDIR) ...
	-$(RM) $(LIBDIR)/$(OUTPUT)
	echo Installing new library in $(LIBDIR) ...
	$(CP)  $(OUTPUT) $(LIBDIR)

install-includes: $(HEADERS) $(INSTALL_INLINES) $(INCDIR)/TL
	echo Deleting old include files from $(INCDIR)/TL ...
	-$(RM) $(INCDIR)/TL/*.h
	echo Installing new include files in $(INCDIR)/TL ...
	for X in $(HEADERS) $(INSTALL_INLINES); do\
		$(CP) $${X} $(INCDIR)/TL; done

install: install-includes install-lib

release: install

git-pull:
	@echo Pulling sources form github...
	$(GIT) pull

git-add:
	@echo Staging changed local sources...
	$(GIT) add -A

git-commit:
	@echo Committing changed local sources...
	$(GIT) commit

git-push:
	@echo Pushing sources to github...
	$(GIT) push 

postscript: $(PSDIR) $(PSFILES)

print: postscript
	for X in $(PSFILES); do \
		echo Printing $(PSDIR)/$$X ...; \
		$(PRINT) $(PSDIR)/$$X ; done

backup: $(SOURCES) $(HEADERS) $(INLINES) $(YFILES) $(LFILES) $(TEST_SRCS)
	-$(RM) $(BACKUP).$(TAR_SUFFIX) $(BACKUP).$(TAR_SUFFIX).$(COMPRESS_SUFFIX)
	$(TAR) $(BACKUP).$(TAR_SUFFIX)\
		$(SOURCES) $(HEADERS) $(INLINES) $(YFILES) $(LFILES) $(TEST_SRCS) Makefile
	$(COMPRESS) $(BACKUP).$(TAR_SUFFIX)
	-$(MV) $(BACKUP).$(TAR_SUFFIX).$(COMPRESS_SUFFIX) $(BACKUP).taz

veryclean: clean clean-rcs 
	-$(RM) $(TMPSRCS) $(TMPHEADERS) $(PSDIR)/*.$(PS_SUFFIX) *.$(PS_SUFFIX) *.$(TAR_SUFFIX) *.$(COMPRESS_SUFFIX) *.taz *tags 2!

clean: clean-rubbish
	-$(RM) $(OBJS) $(TEST_OBJS)
	-$(RM) -rf $(TEMPLATE_INST_DIR)
	-$(RM) $(OUTPUT)
	-$(RM) $(TEST_OUTPUT)

clean-rcs:
	-$(RCSCLEAN) 2> /dev/null

clean-rubbish:
	-$(RM) *~ core* *.bak *.bck $(LOGFILE) *.output	

find-error fe:
	$(EDITOR) -p $(LOGFILE)

checkout co:
	-$(CO) $(COFLAGS) $(HEADERS) $(INLINES) \
             $(SOURCES) $(TEST_SRCS)

checkout-lock col:
	-$(CO) -l $(HEADERS) $(INLINES) \
		$(SOURCES) $(TEST_SRCS) \
		$(YFILES) $(LFILES)

checkin ci: clean-rcs
	-$(CI) -m. *.cpp *.h

replace-headers: $(HEADERS) $(INLINES)
	for X in $(HEADERS) $(INLINES); do \
		$(MV) $$X $$X.old; \
		$(SED) 's/ostream/SCStream/g' $$X.old >> $$X ; done

replace-sources: 
	for X in $(SOURCES); do \
		$(MV) $$X $$X.old; \
		$(SED) 's/msg/sig/g' $$X.old >> $$X ; done

depend: $(HEADERS) $(INLINES) $(SOURCES) $(TMPSRCS) $(TEST_SRCS) $(OBJDIR)
	@echo Building dependency file $(DEPFILE) ...
	$(RM) -f $(DEPFILE)
	$(MAKE_DEPEND) $(SOURCES) $(INCLUDES) $(TMPSRCS) $(TEST_SRCS) $(CFLAGS) > $(DEPFILE)
	$(SED) 's/^\(.*\)\.o/\$$(OBJDIR)\/\1\.o/g' $(DEPFILE) > $(DEPFILE).sed
	$(MV) $(DEPFILE).sed $(DEPFILE)


# Dependencies:
-include $(DEPFILE)
