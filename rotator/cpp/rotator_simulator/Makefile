#----------------------------------------------------------------------------
#       Macros
#----------------------------------------------------------------------------
CFG = Release

ifeq ($(CFG), Release)
CC            = gcc
CXX           = g++
LD            = $(CXX) $(CCFLAGS) $(CPPFLAGS)
AR            = ar
PICFLAGS      = -fPIC
CPPFLAGS      = $(PICFLAGS) $(GENFLAGS) -g $(SAL_CPPFLAGS) -D_REENTRANT -Wall -I"." -I"$(OSPL_HOME)/examples/include" -I"$(OSPL_HOME)/examples" -I"$(OSPL_HOME)/include" -I"$(OSPL_HOME)/include/sys" -I"$(OSPL_HOME)/include/dcps/C++/SACPP" -I"$(SAL_HOME)/include" -I"$(SAL_WORK_DIR)/rotator/cpp/src" -I"$(SAL_WORK_DIR)/rotator/cpp" -I"$(SAL_WORK_DIR)/include" -Wno-write-strings #-DSAL_SUBSYSTEM_ID_IS_KEYED
OBJEXT        = .o
OUTPUT_OPTION = -o "$@"
COMPILE.c     = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc    = $(CXX) $(CCFLAGS) $(CPPFLAGS) -c
LDFLAGS       = -L"." -L"$(OSPL_HOME)/lib" -Wl,-rpath,\$$ORIGIN -Wl,-rpath,\$$ORIGIN/$(OSPL_HOME)/lib -L"$(SAL_HOME)/lib"
CCC           = $(CXX)
MAKEFILE      = Makefile
DEPENDENCIES  = .depend.$(MAKEFILE)
BTARGETDIR    = ./
BIN           = $(BTARGETDIR)rotator_simulator$(EXESUFFIX)$(EXEEXT)
CAT           = cat
MV            = mv -f
RM            = rm -rf
CP            = cp -p
NUL           = /dev/null
MKDIR         = mkdir -p
TESTDIRSTART  = test -d
TESTDIREND    = ||
TOUCH         = touch
EXEEXT        = 
LIBPREFIX     = lib
LIBSUFFIX     = 
GENFLAGS      = 
LDLIBS        = -l"sacpp_rotator_types$(LIBSUFFIX)" -l"dcpssacpp" -l"dcpsgapi" -l"ddsuser" -l"ddskernel" -l"ddsserialization" -l"ddsconfparser" -l"ddsconf" -l"ddsdatabase" -l"ddsutil" -l"ddsos" -ldl $(subst lib,-l,$(sort $(basename $(notdir $(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread
OBJS          = .obj/CheckStatus$(OBJEXT) .obj/SAL_rotator$(OBJEXT) .obj/Rotator$(OBJEXT) .obj/rotatorTrackSubscriber$(OBJEXT) .obj/rotatorPositionDataPublisher$(OBJEXT) .obj/sharedInfo$(OBJEXT) .obj/main$(OBJEXT)
SRC           = ../src/CheckStatus.cpp ../src/SAL_rotator.cpp ./rotator/Rotator.cpp ./rotatorTrackSubscriber.cpp ./rotatorPositionDataPublisher.cpp ./sharedInfo.cpp ./main.cpp
LINK.cc       = $(LD) $(LDFLAGS)
EXPORTFLAGS   = 
endif
ifeq ($(CFG), Debug)
CC            = gcc
CXX           = g++
LD            = $(CXX) $(CCFLAGS) $(CPPFLAGS)
AR            = ar
PICFLAGS      = -fPIC
CPPFLAGS      = $(PICFLAGS) $(GENFLAGS) $(SAL_CPPFLAGS) -D_REENTRANT -Wall -I"." -I"$(OSPL_HOME)/examples/include" -I"$(OSPL_HOME)/examples" -I"$(OSPL_HOME)/include" -I"$(OSPL_HOME)/include/sys" -I"$(OSPL_HOME)/include/dcps/C++/SACPP"
OBJEXT        = .o
OUTPUT_OPTION = -o "$@"
COMPILE.c     = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc    = $(CXX) $(CCFLAGS) $(CPPFLAGS) -c
LDFLAGS       = -L"." -L"$(OSPL_HOME)/lib" -Wl,-rpath,\$$ORIGIN -Wl,-rpath,\$$ORIGIN/$(OSPL_HOME)/lib
CCC           = $(CXX)
MAKEFILE      = Makefile
DEPENDENCIES  = .depend.$(MAKEFILE)
BTARGETDIR    = ./
BIN           = $(BTARGETDIR)rotator_simulator$(EXESUFFIX)$(EXEEXT)
CAT           = cat
MV            = mv -f
RM            = rm -rf
CP            = cp -p
NUL           = /dev/null
MKDIR         = mkdir -p
TESTDIRSTART  = test -d
TESTDIREND    = ||
TOUCH         = touch
EXEEXT        = 
LIBPREFIX     = lib
LIBSUFFIX     = 
GENFLAGS      = -g
LDLIBS        = -l"sacpp_rotator_types$(LIBSUFFIX)" -l"dcpssacpp" -l"dcpsgapi" -l"ddsuser" -l"ddskernel" -l"ddsserialization" -l"ddsconfparser" -l"ddsconf" -l"ddsdatabase" -l"ddsutil" -l"ddsos" -ldl $(subst lib,-l,$(sort $(basename $(notdir $(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread
OBJS          = .obj/CheckStatus$(OBJEXT) .obj/SAL_rotator$(OBJEXT) .obj/Rotator$(OBJEXT) .obj/rotatorTrackSubscriber$(OBJEXT) .obj/rotatorPositionDataPublisher$(OBJEXT) .obj/sharedInfo$(OBJEXT) .obj/main$(OBJEXT)
SRC           = ../src/CheckStatus.cpp ../src/SAL_rotator.cpp ./rotatorTrackSubscriber.cpp ./rotatorPositionDataPublisher.cpp ./sharedInfo.cpp ./main.cpp 
LINK.cc       = $(LD) $(LDFLAGS)
EXPORTFLAGS   = 
endif

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

all: $(BIN)

$(BIN): $(OBJS)
	@$(TESTDIRSTART) "$(BTARGETDIR)" $(TESTDIREND) $(MKDIR) "$(BTARGETDIR)"
	$(LINK.cc) $(OBJS) $(LDLIBS) $(OUTPUT_OPTION)

generated: $(GENERATED_DIRTY)
	@-:

.obj/CheckStatus$(OBJEXT): ../src/CheckStatus.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ../src/CheckStatus.cpp

.obj/SAL_rotator$(OBJEXT): ../src/SAL_rotator.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ../src/SAL_rotator.cpp

.obj/rotatorTrackSubscriber$(OBJEXT): ./rotatorTrackSubscriber.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ./rotatorTrackSubscriber.cpp

.obj/rotatorPositionDataPublisher$(OBJEXT): ./rotatorPositionDataPublisher.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ./rotatorPositionDataPublisher.cpp
	
.obj/sharedInfo$(OBJEXT): ./sharedInfo.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ./sharedInfo.cpp
	
.obj/Rotator$(OBJEXT): ./rotator/Rotator.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ./rotator/Rotator.cpp
	
.obj/main$(OBJEXT): ./main.cpp
	@$(TESTDIRSTART) ".obj/../src" $(TESTDIREND) $(MKDIR) ".obj/../src"
	$(COMPILE.cc) $(EXPORTFLAGS) $(OUTPUT_OPTION) ./main.cpp

clean:
	-$(RM) $(OBJS)

realclean: clean
	-$(RM) $(BIN)
	-$(RM) .obj/

check-syntax:
	$(COMPILE.cc) $(EXPORTFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)

#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------

$(DEPENDENCIES):
	@$(TOUCH) $(DEPENDENCIES)

depend:
	-VDIR=.obj/ $(MPC_ROOT)/depgen.pl  $(CFLAGS) $(CCFLAGS) $(CPPFLAGS) -f $(DEPENDENCIES) $(SRC) 2> $(NUL)

include $(DEPENDENCIES)
