#+
# Makefile
#
# Maintains the tcs utilities build directory.
#
# D L Terrett  28 February 2003
#
# Copyright CCLRC 2003
#+

# Locations of libraries.
SLALIB_DIR = ../slalib

# Default compiler flags.
CFLAGS = -Wall -Wno-uninitialized -O
DFLAGS = -M

# Utility programs.
programs = ptconv

# Additional Libraries required for applications.
libraries = -lsla -lm

# Library and include file search paths.
include_path = -I. -I$(SLALIB_DIR)
library_path = -L$(SLALIB_DIR)

# Default target 
all: programs

# Install library
INSTALL_DIR = ..
install:
	@if test -e $(INSTALL_DIR)/bin; then true; \
			else mkdir $(INSTALL_DIR)/bin; fi
	cp ptconv $(INSTALL_DIR)/bin


programs: 
	$(MAKE) -f Makefile.build $(programs)

# Remove intermediate files.
clean:
	- rm -f $(objects) depends

# Remove built files as well.
distclean: clean
	- rm -f $(programs)

# C source files.
program_sources = ptconv.c

sources = $(program_sources)

SHELL = /bin/sh
.SUFFIXES: .c .o .a
.EXPORT_ALL_VARIABLES:
