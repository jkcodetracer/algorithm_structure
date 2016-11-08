####################
#  @filename:
#  @creator: wzj
##
#  @date: Tue Nov  8 07:28:07 AEST 2016
##
#####################

#free flags
MY_CFLAGS = 

#free linker
MY_LIBS = 

#pre-processor option for cpp
CPPFLAGS = -Wall

#the opt used in linking ..fress ld
LDFLAGS = 

#your engin dir
SRCDIRS = ./ 

# to use gcov:
# 1. name your target with the source file name. 
# 2. gcov 'program name'
# the srcfile_dir include the *.gdca
# 3. lcov -c -d srcfile_dir -o srcfile.info
# then genhtml -o report_dir srcfile.info
# 4. use the firefox open the report!
#your target
PROGRAM = ./test

#
# Implicit Section: change if necessary 
###========================================

#The source file types
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp

#The header file types
HDREXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp

# compiler options
CFLAGS += -g -O2 -fprofile-arcs -ftest-coverage 
CXXFLAGS += -g -O2

#The C program compiler.
#CC		= gcc

#The C++ compiler.
#CXX	= g++

#compile C programs as C++ ones
#CC		= $(CXX)

#rm ...
#RM		= rm -f

ETAGS = etags
ETAGSFLAGS = 

CTAGS = ctags
CTAGSFLAGS =

#### stable section: you can add , but it rearly need a change
##===========================================================
SHELL = /bin/sh
EMPTY = 
SPACE = $(EMPTY) $(EMPTY)
ifeq ($(PROGRAM),)
  CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
  PROGRAM = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))
  ifeq ($(PROGRAM),)
  	PROGRAM = a.out
  endif
endif
ifeq ($(SRCDIRS),)
	SRCDIRS = .
endif

SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
SRC_CXX = $(filter-out %.c,$(SOURCES))
OBJS	= $(addsuffix .o, $(basename $(SOURCES)))
#DEPS	= $(OBJS: .o=.d)
DEPS	= $(addsuffix .d, $(basename $(SOURCES)))

##define some variables
DEP_OPT = $(shell if `$(CC) --version | grep "GCC" >/dev/null`; then \
				echo "-MM -MP"; else echo "-M"; fi)
DEPEND	= $(CC) $(DEP_OPT) $(MY_CFLAGS) $(CFLAGS) $(CPPFLAGS)

#获取依赖关系
DEPEND.d = $(subst -g ,,$(DEPEND))
COMPILE.c = $(CC) $(MY_CFLAGS) $(CFLAGS)  $(CPPFLAGS) -c
COMPILE.cxx = $(CXX) $(MY_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.c	= $(CC) $(MY_CFLAGS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cxx = $(CXX) $(MY_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: all dep objs tags ctags clean distclean help show

#delete the default suffixes
.SUFFIXES:

all: $(DEPS)	\
	$(PROGRAM)

#rules for creating dependency files.
#--------------------------------------

dep:$(DEPS)

%.d:%.c
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.C
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cc
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cpp
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.CPP
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.c++
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cp
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cxx
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

#Rules for generating object files (.o)
#-----------------------------------------
objs:$(OBJS)

%.o:%.c
	$(COMPILE.c) $< -o $@

%.o:%.C
	$(COMPILE.cxx) $< -o $@

%.o:%.cc
	$(COMPILE.cxx) $< -o $@

%.o:%.cpp
	$(COMPILE.cxx) $< -o $@

%.o:%.CPP
	$(COMPILE.cxx) $< -o $@

%.o:%.c++
	$(COMPILE.cxx) $< -o $@

%.o:%.cp
	$(COMPILE.cxx) $< -o $@

%.o:%.cxx
	$(COMPILE.cxx) $< -o $@

# Rules for generating the tags.
#-------------------------------------
tags: $(HEADERS) $(SOURCES) 
	$(ETAGS) $(ETAGSFLAGS) $(HEADERS) $(SOURCES) 

ctags: $(HEADERS) $(SOURCES)
	$(CTAGS) $(CTAGSFLAGS) $(HEADERS) $(SOURCES) 

# Rules for generating the executable.
#------------------------------------- 
$(PROGRAM):$(OBJS) 
ifeq ($(SRC_CXX),)              # C program 
	$(LINK.c)   $(OBJS) $(MY_LIBS) -o $@ 
	@echo Type ./$@ to execute the program.
else                            # C++ program 
	$(LINK.cxx) $(OBJS) $(MY_LIBS) -o $@ 
	@echo Type ./$@ to execute the program.
endif

ifneq ($(DEPS),)
#-include $(DEPS)
endif

clean:
	$(RM) $(OBJS) $(PROGRAM) $(PROGRAM).exe *.gcda *.gcno 
  
distclean: clean
	$(RM) $(DEPS) TAGS 

help:

show: 
