rm Makefile.am;
echo '
#+----------------------------------------------------------------------------+
#| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
#| Copyright:    (C) 2001 - 2008 Twan van Laarhoven and "coppro"              |
#| License:      GNU General Public License 2 or later (see file COPYING)     |
#+----------------------------------------------------------------------------+

# This file is generated by MakeAM.sh. DO NOT EDIT!

# This flag allows us to use subdirectories:
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = magicseteditor
AM_CXXFLAGS = @WX_CXXFLAGS@ $(BOOST_CXXFLAGS) -I. -Wall
AM_LDFLAGS  = @WX_LIBS@ $(BOOST_LDFLAGS)

.hpp.gch:
	target=`echo $@ | sed "s|.gch$$|.hpp|"`;\
	depbase=`echo $$target | sed "s|[^/]*\$$|$(DEPDIR)/&|;s|\\.hpp\$$||"`;\
	$(CXXCOMPILE) -MT $@ -MD -MP -MF $$depbase.Tpch -x c++-header -c $$target &&\
	$(am__mv) $$depbase.Tpch $$depbase.Pch
	touch $@
.gch.o:
	gcc -x c - -c -o $@ <<<""

magicseteditor_LDADD = $(BOOST_REGEX_LIB)
magicseteditor_CXXFLAGS = -fpch-deps $(AM_CXXFLAGS)
magicseteditor_SOURCES = 

if GLIBCPP_BUILD_PCH
clean-local:
	rm -f ./src/util/prec.hpp.gch
	rm -f ./src/util/prec.gch
include ./src/util/$(DEPDIR)/prec.Pch
magicseteditor_SOURCES += ./src/util/prec.gch
endif

# The script used to generate is MakeAM.sh' > Makefile.am;

find . -name *.cpp | sed "s/\./magicseteditor_SOURCES += ./" >> Makefile.am;
