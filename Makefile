SHELL := /bin/bash
CC ?= gcc
LD ?= gcc

SRCDIR = ./src
OBJDIR = ./obj

BUILD := debug
BUILD_DIR := ${CURDIR}/${BUILD}
CFLAGS := ${CFLAGS} -std=gnu99 -pedantic -Werror -Wall -Wextra -Wcast-align\
	-Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self\
	-Wmissing-include-dirs -Wredundant-decls -Wshadow\
	-Wstrict-overflow=5 -Wundef -fdiagnostics-show-option -Wconversion -g
CLFAGS.debug := ${CFLAGS} -O0 -fstack-protector-all -g
CLFAGS.release := ${CFLAGS} -O3 -DNDEBUG

BINARY := $(BUILD_DIR)/eventing

PREFIX  ?= /usr/local
BINDIR  ?= ${PREFIX}/bin
DATADIR ?= ${PREFIX}/share
MANDIR  ?= ${DATADIR}/man

# Add source epoch date for reporducible builds
DATE_FMT = %Y-%m-%d
ifdef SOURCE_DATE_EPOCH
        BUILD_DATE ?= $( date -u -d "@$(SOURCE_DATE_EPOCH)" "+$(DATE_FMT)"  2>/dev/null || date -u -r "$(SOURCE_DATE_EPOCH)" "+$(DATE_FMT)" 2>/dev/null || date -u "+$(DATE_FMT)")
else
        BUILD_DATE ?= $(shell date "+$(DATE_FMT)")
endif

SRCS = $(sort $(wildcard $(SRCDIR)/*.c)) 
OBJS = $(SRCS:.c=.o)

all: $(BUILD_DIR) $(SRCS) $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS.debug) $(OBJS) -o $@
.o:
	$(CC) $(CFLAGS.debug) $< -o $@ 

# Make build dir
${BUILD_DIR}:
	mkdir $@

run: $(BINARY)
	$(BINARY)
	

.PHONEY = clean
clean:
	rm -rf ${BUILD_DIR}
	rm -rf $(SRCDIR)/*.o
