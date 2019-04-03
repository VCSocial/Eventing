SHELL := /bin/bash
CC ?= gcc
LD ?= gcc

SRCDIR = src
DAEMON_SRCDIR= ${SRCDIR}/daemon
CLIENT_SRCDIR= ${SRCDIR}/client

OBJDIR = obj
DAEMON_OBJDIR=${OBJDIR}/daemon
CLIENT_OBJDIR=${OBJDIR}/client

BUILD := debug
BUILD_DIR := ${CURDIR}/${BUILD}

TEST := test
TEST_DIR := ${CURDIR}/${TEST}
BUILD_TEST_DIR := ${BUILD_DIR}/${TEST}

CFLAGS := ${CFLAGS} -std=gnu99 -pedantic -Werror -Wall -Wextra -Wcast-align\
	-Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self\
	-Wmissing-include-dirs -Wredundant-decls -Wshadow\
	-Wstrict-overflow=5 -Wundef -fdiagnostics-show-option -Wconversion -g \
	-O0 -fstack-protector-all -pthread
CLFAGS_RELEASE := ${CFLAGS} -O3 -DNDEBUG
TEST_FLAGS := -lcriterion
LDFLAGS := -lm

BINARY := $(BUILD_DIR)/eventing
DAEMON_BINARY := $(BUILD_DIR)/daemon
CLIENT_BINARY := $(BUILD_DIR)/client

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
DAEMON_SRCS = $(sort $(wildcard $(DAEMON_SRCDIR)/*.c)) 
CLIENT_SRCS = $(sort $(wildcard $(CLIENT_SRCDIR)/*.c)) 

DAEMON_OBJS = $(patsubst $(DAEMON_SRCDIR)/%.c,$(DAEMON_OBJDIR)/%.o,$(DAEMON_SRCS))
CLIENT_OBJS = $(patsubst $(CLIENT_SRCDIR)/%.c,$(CLIENT_OBJDIR)/%.o,$(CLIENT_SRCS))

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
TSTS = $(filter-out $(TEST_DIR)/unit_main.c, $(patsubst $(SRCDIR)/%.c,$(TEST_DIR)/unit_%.c,$(SRCS)))
TST_SRCS = $(filter-out $(SRCDIR)/main.c, $(SRCS))
TST_BINS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_TEST_DIR)/%,$(TSTS))

all: daemon client
test: $(TST_BINS)
daemon: $(DAEMON_BINARY)
client: $(CLIENT_BINARY)

$(DAEMON_BINARY): $(DAEMON_OBJS)
	@echo "Building Daemon Binary"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(LDFLAGS) -o $@ $+

$(DAEMON_OBJS): $(DAEMON_OBJDIR)/%.o: $(DAEMON_SRCDIR)/%.c
	@echo Compiling $<
	@mkdir -p $(DAEMON_OBJDIR)
	@$(CC) ${CFLAGS} -c $< -o $@

$(CLIENT_BINARY): $(CLIENT_OBJS)
	@echo "Building Client Binary"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(LDFLAGS) -o $@ $+

$(CLIENT_OBJS): $(CLIENT_OBJDIR)/%.o: $(CLIENT_SRCDIR)/%.c
	@echo Compiling $<
	@mkdir -p $(CLIENT_OBJDIR)
	@$(CC) ${CFLAGS} -c $< -o $@

$(BINARY): $(OBJS) 
	@echo "Building binary"
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(LDFLAGS) -o $@ $+

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	@mkdir -p $(OBJDIR)
	@$(CC) ${CFLAGS} -c $< -o $@

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
