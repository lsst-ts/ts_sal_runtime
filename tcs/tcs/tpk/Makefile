#+
# Makefile
#
# Builds and installs tpk
#
# D L Terrett  20 July 2007
#
# Copyright CCLRC 2005
#+

MUTEX = PosixMutex

LIBOBJ = AffineTransform.o AzElRefSys.o AzElTarget.o ApptRefSys.o \
             ApptTarget.o AutoGuider.o AvgFilter.o AltAzLimitCalc.o \
             AltAzRotLimitCalc.o \
         BaseVt.o \
         Coordinates.o \
         DawdleFilter.o \
	 FK5RefSys.o FK5Target.o \
         GalacticRefSys.o GalacticTarget.o \
	 ICRefSys.o ICRSTarget.o \
         KalmanFilter.o Kernel.o KernelAzElRefSys.o KernelFK5RefSys.o \
             KernelGalacticRefSys.o KernelWcs.o \
         LimitCalc.o \
         MountVt.o \
         OpticsVt.o \
         PiFilter.o PiFilter2D.o Planet.o PointCat.o PointingControl.o \
             PointingLog.o PointingModel.o PointingObs.o PointingOrigin.o \
         RotaryAxis.o \
         Site.o SpiralTarget.o SolSysTargets.o \
         Target.o TcsLib.o TcspkRefSys.o TopoApptRefSys.o TopoApptTarget.o \
             TimeKeeper.o TrackingTarget.o \
         UnixClock.o \
         Wcs.o

INCLUDE_FILES = AffineTransform.h ApptRefSys.h ApptTarget.h AutoGuider.h \
                    AvgFilter2D.h AvgFilter.h AzElRefSys.h AzElTarget.h \
                    AltAzLimitCalc.h AltAzRotLimitCalc.h \
                BaseVt.h \
                Clock.h Coordinates.h \
                DawdleFilter.h \
                Filter2D.h Filter.h FK5RefSys.h FK5Target.h \
                GalacticRefSys.h GalacticTarget.h \
                ICRefSys.h ICRSTarget.h \
                KalmanFilter.h KernelAzElRefSys.h KernelFK5RefSys.h \
                    KernelGalacticRefSys.h KernelRefSys.h KernelWcs.h \
                LimitCalc.h \
                MountType.h MountVt.h \
                OpticsVt.h \
                PiFilter2D.h PiFilter.h Planet.h PointCat.h \
                    PointingControl.h PointingLog.h PointingModel.h \
                    PointingObs.h PointingOrigin.h \
                RefSys.h RotatorLoc.h RotaryAxis.h \
                Site.h SolSysTargets.h SpiralTarget.h \
                Target.h TclClock.h TcsLib.h TcsMutex.h TimeKeeper.h \
                    TopoApptRefSys.h TopoApptTarget.h TrackingTarget.h \
                    Trajectory.h Transform.h \
                UnixClock.h \
                Wcs.h  WrapControl.h \
                tpk.h \
		SAL_tcs.h ccpp_sal_tcs.h os.h example_main.h

all: check_mutex libtpk.a

# Install library
INSTALL_DIR = ..
install:
	@if test -e $(INSTALL_DIR)/lib; then true; \
			else mkdir $(INSTALL_DIR)/lib; fi
	@if test -e $(INSTALL_DIR)/include; then true; \
			else mkdir $(INSTALL_DIR)/include; fi
	cp libtpk.a $(INSTALL_DIR)/lib
	cp $(INCLUDE_FILES) $(INSTALL_DIR)/include

libtpk.a : $(LIBOBJ) TcsMutex.h
	-rm $@
	$(AR) -r $@ $(LIBOBJ)


check_mutex:
	@if diff -q TcsMutex.h $(MUTEX).h ; then true "" ; else \
          echo "Different mutex implementation - please make dist_clean"; \
        fi

TcsMutex.h:
	ln -s $(MUTEX).h TcsMutex.h

clean:
	-rm $(LIBOBJ) .depends

dist_clean: clean
	-rm libtpk.a TcsMutex.h

CXXFLAGS = -Wall -g -I../tcspk -I../slalib -fPIC

.depends: TcsMutex.h
	-rm .depends
	-$(CXX) $(CXXFLAGS) -MM *.cpp >> .depends

include .depends

