SHELL := /bin/bash
CC ?= gcc
LD ?= gcc

SRCDIR = src
OBJDIR = obj
BUILD := debug
BUILD_DIR := ${CURDIR}/${BUILD}

TEST := test
TEST_DIR := ${CURDIR}/${TEST}

BUILD_TEST_DIR := ${BUILD_DIR}/${TEST}

CFLAGS := ${CFLAGS} -std=gnu99 -pedantic -Werror -Wall -Wextra -Wcast-align\
	-Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self\
	-Wmissing-include-dirs -Wredundant-decls -Wshadow\
	-Wstrict-overflow=5 -Wundef -fdiagnostics-show-option -Wconversion -g\
	-luuid
CLFAGS.debug := ${CFLAGS} -O0 -fstack-protector-all -g
CLFAGS.release := ${CFLAGS} -O3 -DNDEBUG
TEST_FLAGS := -lcriterion
LDFLAGS := -lm

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
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
TSTS = $(filter-out $(TEST_DIR)/unit_main.c, $(patsubst $(SRCDIR)/%.c,$(TEST_DIR)/unit_%.c,$(SRCS)))
TST_SRCS = $(filter-out $(SRCDIR)/main.c, $(SRCS))
TST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%,$(TSTS))

all: $(BINARY) $(TST_BINS) run_tests
test: $(TST_BINS)

$(BINARY): $(OBJS) 
	@echo "Building binary"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(LDFLAGS) -o $@ $+

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS.debug) -c $< -o $@

$(TST_BINS): $(TSTS) $(TST_SRCS) 
	@echo Running all tests
	@mkdir -p $(BUILD_TEST_DIR)
	@$(CC) $(TEST_FLAGS) $+ -o $@

run: $(BINARY) 
	$(BINARY)

run_tests: $(TST_BINS)
	$(TST_BINS)

.PHONEY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJDIR)
