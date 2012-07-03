#
# Makefile for Billing Agent
#
# $Id: Makefile 125 2009-03-01 16:37:11Z cdsheen $

OSNAME=centos5

DEFINES=


TARGET=FTAAA.so

CC=g++

RM=rm


CFLAGS=-Wall -g -fPIC -I $(DEFINES) -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

LDFLAGS=-lpthread  -shared -fPIC

OBJS=FTAAA.o compat_windows.o dictionary.o iniparser.o


.SUFFIXES:	.cpp

.c.o:	
	$(CC) $(CFLAGS) -c $<

.cpp.o:	
	$(CC) $(CFLAGS) -c $<

all:	$(TARGET)

FTAAA.so:	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)


clean:
	$(RM) *.o *~ $(TARGET)
