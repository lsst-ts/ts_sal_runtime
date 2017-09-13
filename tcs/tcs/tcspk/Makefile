#+
# Makefile
#
# Builds and installs TCSpk
#
# D L Terrett  1 February 2007
#
# Copyright CCLRC 2005
#+

CSRC = addtrm.c aim2enc.c aim2s_c.c aim2xe.c aimtrk.c astup.c \
       bs.c \
       casspa.c \
       enc2aim.c \
       fast.c \
       g2po.c g2tar.c \
       init2.c intpm.c iterm.c \
       length.c \
       medium.c minit.c \
       pmt.c porup.c posture.c probev.c ptappl.c pterm.c ptermg.c pterml.c \
           pterms.c ptpre.c ptran.c ptrani.c pup.c \
       refsub.c rotator.c \
       scomp.c sky2a_c.c sky2aim.c slow.c spm.c sterm.c \
       targup.c tartran.c tartr_c.c term.c time.c track.c track_c.c \
       trmgen.c trmloc.c trmstd.c \
       vtenc.c vtenc_c.c vtsky.c vtsky_c.c vtxe.c vtxe_c.c vtxy.c vtxy_c.c \
       xe2xy.c xy2xe.c \

COBJ = $(CSRC:.c=.o)

INCLUDES = -I../slalib

CFLAGS = -Wall $(INCLUDES) -g -fPIC

LIBS = -L../slalib -lsla -lm

all: tcs_demo tcs_dsa tcs_equ tcs_pa tcs_test tcs_tpt tcs_zt

libtcs.a: $(COBJ)
	$(AR) -r $@ $?

# Install library
INSTALL_DIR = ..
install:
	@if test -e $(INSTALL_DIR)/lib; then true; \
			else mkdir $(INSTALL_DIR)/lib; fi
	@if test -e $(INSTALL_DIR)/include; then true; \
			else mkdir $(INSTALL_DIR)/include; fi
	cp libtcs.a $(INSTALL_DIR)/lib
	cp tcs.h $(INSTALL_DIR)/include
	cp tcsmac.h $(INSTALL_DIR)/include
	cp tcsctx.h $(INSTALL_DIR)/include
	cp dsactx.h $(INSTALL_DIR)/include


tcs_demo: tcs_demo.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_demo.o $(COBJ) -o $@ $(LIBS)

tcs_dsa: tcs_dsa.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_dsa.o $(COBJ) -o $@ $(LIBS)

tcs_equ: tcs_equ.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_equ.o $(COBJ) -o $@ $(LIBS)

tcs_pa: tcs_pa.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_pa.o $(COBJ) -o $@ $(LIBS)

tcs_test: tcs_test.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_test.o $(COBJ) -o $@ $(LIBS)

tcs_tpt: tcs_tpt.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_tpt.o $(COBJ) -o $@ $(LIBS)

tcs_zt: tcs_zt.o $(COBJ) 
	$(CC) $(CFLAGS) tcs_zt.o $(COBJ) -o $@ $(LIBS)

clean:
	- rm -f tcs_demo.o tcs_dsa.o tcs_equ.o tcs_pa.o tcs_test.o \
                tcs_tpt.o tcs_zt.o $(COBJ) depends

depends:
	$(CC) $(INCLUDES) -MM $(CSRC) >> depends

include depends
