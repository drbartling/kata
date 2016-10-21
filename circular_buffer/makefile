# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
elseifeq ($(OSTYPE),msys)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.exe
elseifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

#Path Definitions
PATHU = ../../Unity/src/
PATHS = src/
PATHI = inc/
PATHT = test/
PATHB = build/

#determine our source files
SRCU = $(PATHU)unity.c
SRCS = $(wildcard $(PATHS)*.c)
SRSI = $(wildcard $(PATHI)*.c)
SRCT = $(wildcard $(PATHT)*.c)
SRC = $(SRCU) $(SRCS) $(SRCI) $(SRCT)

#Files We Are To Work With
OBJU = $(patsubst $(PATHU)%.c,$(PATHB)%.o,$(SRCU))
OBJS = $(patsubst $(PATHS)%.c,$(PATHB)%.o,$(SRCS))
OBJI = $(patsubst $(PATHI)%.c,$(PATHB)%.o,$(SRCI))
OBJT = $(patsubst $(PATHT)%.c,$(PATHB)%.o,$(SRCT))
OBJ = $(OBJU) $(OBJS) $(OBJI) $(OBJT)

#Other files we care about
DEP  = $(PATHU)unity.h
DEP += $(PATHU)unity_internals.h
TGT  = $(PATHB)test$(TARGET_EXTENSION)

#Tool Definitions
C_COMPILER = gcc
CFLAGS  = -std=c99
CFLAGS += -D TEST

INC_DIRS  = -I .
INC_DIRS += -I $(PATHU)
INC_DIRS += -I $(PATHS) 
INC_DIRS += -I $(PATHI) 

COMPILE = $(C_COMPILER) -c $(CFLAGS) $(INC_DIRS) $< -o $@

all: clean default

default: $(PATHB) $(TGT)
	./$(TGT)

$(PATHB)%.o:: $(PATHS)%.c $(DEP)
	$(COMPILE)

$(PATHB)%.o:: $(PATHI)%.c $(DEP)
	$(COMPILE)

$(PATHB)%.o:: $(PATHT)%.c $(DEP)
	$(COMPILE)

$(PATHB)%.o:: $(PATHU)%.c $(DEP)
	$(COMPILE)

$(TGT): $(OBJ)
	$(C_COMPILER) -o $@ $^

clean:
	$(CLEANUP) $(PATHB)*.o
	$(CLEANUP) $(TGT)

$(PATHB):
	$(MKDIR) $(PATHB)
