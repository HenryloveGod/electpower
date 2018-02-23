SUBDIRS=epplib
#CURRENTPATH=$(shell /bin/pwd)
AM_CPPFLAGS=-I$(top_srcdir)/epplib -I$(top_srcdir)/epplib 
#export INCLUDES
noinst_PROGRAMS=test
test_SOURCES=main.c 
test_LDADD=$(top_srcdir)/epplib/libepp.a
test_LDFLAGS=-D_GNU_SOURCE
DEFS+=-D_GNU_SOURCE
#LIBS=-lpthread
