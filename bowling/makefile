# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

group?=
CFLAGS?=

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP          = rm -f
	MKDIR            = mkdir -p
	TARGET_EXTENSION =.out
elseifeq ($(OSTYPE),msys)
	CLEANUP          = rm -f
	MKDIR            = mkdir -p
	TARGET_EXTENSION =.exe
elseifeq ($(OS),Windows_NT)
	CLEANUP          = del /F /Q
	MKDIR            = mkdir
	TARGET_EXTENSION =.exe
else
	CLEANUP          = rm -f
	MKDIR            = mkdir -p
	TARGET_EXTENSION =.out
endif

dir_guard=@mkdir -p $(@D)

PATH_LIB            = lib/
PATH_BUILD          = build/

PATH_UNITY  = $(PATH_LIB)unity/src/
INC_DIRS   += -I $(PATH_UNITY)
HDR_ALL    += $(wildcard $(PATH_UNITY)*.h)
SRC_UNITY   = $(wildcard $(PATH_UNITY)*.c)
SRC_ALL    += $(SRC_UNITY)
OBJ_UNITY   = $(patsubst $(PATH_UNITY)%.c,$(PATH_BUILD)%.o,$(SRC_UNITY))
OBJ_ALL    += $(OBJ_UNITY)

PATH_SRC  = src/
INC_DIRS += -I $(PATH_SRC)
HDR_ALL  += $(wildcard $(PATH_SRC)*.h)
SRC_SRC   = $(wildcard $(PATH_SRC)*.c)
SRC_ALL  += $(SRC_SRC)
OBJ_SRC   = $(patsubst $(PATH_SRC)%.c,$(PATH_BUILD)%.o,$(SRC_SRC))
OBJ_ALL  += $(OBJ_SRC)

PATH_TEST  = test/
INC_DIRS  += -I $(PATH_TEST)
SRC_TEST   = $(wildcard $(PATH_TEST)*.c)
SRC_ALL   += $(SRC_TEST)
OBJ_TEST   = $(patsubst $(PATH_TEST)%.c,$(PATH_BUILD)%.o,$(SRC_TEST))
OBJ_ALL   += $(OBJ_TEST)

CHECK_SRC += $(filter src% test%,$(SRC_ALL))
CHECK_SRC += $(filter src% test%,$(HDR_ALL))

TGT     = $(PATH_BUILD)test$(TARGET_EXTENSION)
RESULTS = $(PATH_BUILD)results.txt

#Tool Definitions
C_COMPILER = clang
CFLAGS    += -std=c99
CFLAGS    += -g
CFLAGS    += -O0
CFLAGS    += -Wall
CFLAGS    += -ferror-limit=5

COV_FLAGS += -fprofile-instr-generate
COV_FLAGS += -fcoverage-mapping

RUN_FLAGS=-g "$(group)"
ifeq ($(group),)
	COV_REP_FLAGS=$(TGT)
else
	COV_REP_FLAGS=$(PATH_BUILD)*$(group)*.o
endif

COMPILE     = $(C_COMPILER) -c $(CFLAGS) $(INC_DIRS) $< -o $@
COMPILE_COV = $(C_COMPILER) -c $(CFLAGS) $(COV_FLAGS)  $(INC_DIRS) $< -o $@
LINK        = $(C_COMPILER) $(COV_FLAGS) -o $@ $^

#Result formatting
NO_COLOR = sgr0
GREEN    = setaf 2
RED      = setaf 1
YELLOW   = setaf 3

PASSED_TESTS = echo; \
	echo ----Passed--------------------------; \
	grep -s -E '.*PASS' ./$(RESULTS); true

IGNORED_TESTS = echo; \
	echo ----Ignored-------------------------; \
	grep -s -E '.*IGNORE' ./$(RESULTS); true

FAILED_TESTS = echo; \
	echo ----Failed--------------------------; \
	grep -s -E '.*FAIL' ./$(RESULTS); true

RESULT_SUMMARY = echo; \
	echo -----------------------------------; \
	grep -s Ignored ./$(RESULTS)

FINAL_RESULT = if grep -q FAIL ./$(RESULTS); \
	then tput $(RED);   echo ==============FAIL==============; tput $(NO_COLOR); \
	else tput $(GREEN); echo ==============PASS==============; tput $(NO_COLOR); \
	fi

default: cov-summary
	@$(IGNORED_TESTS)
	@$(FAILED_TESTS)
	@$(RESULT_SUMMARY)
	@$(FINAL_RESULT)

debug: $(TGT)
	gdb ./$(TGT)

$(PATH_BUILD)default.profraw: $(TGT)
	./$(TGT) -v $(RUN_FLAGS) > $(RESULTS)
	mv default.profraw $(PATH_BUILD)default.profraw

$(PATH_BUILD)default.profdata: $(PATH_BUILD)default.profraw
	llvm-profdata merge $(PATH_BUILD)default.profraw -o \
		$(PATH_BUILD)default.profdata

cov-summary: $(PATH_BUILD)default.profdata
	llvm-cov report -instr-profile=$(PATH_BUILD)default.profdata \
		$(COV_REP_FLAGS)

coverage: $(PATH_BUILD)default.profdata
	llvm-cov show  -instr-profile=$(PATH_BUILD)default.profdata \
		-line-coverage-lt=100 $(COV_REP_FLAGS)

lint:
	@echo ----CPPCHECK-----------------------------
	@cppcheck --enable=all --check-config --suppress=missingIncludeSystem      \
		$(INC_DIRS) $(CHECK_SRC) >/dev/null
	@echo ----CLANG-TIDY---------------------------
	@clang-tidy $(CHECK_SRC) -- $(INC_DIRS)                    \
		2>/dev/null

clean:
	$(CLEANUP) $(PATH_BUILD)*.o
	$(CLEANUP) $(TGT)

clean-all:
	$(CLEANUP) -r $(PATH_LIB)
	$(CLEANUP) -r $(PATH_BUILD)

$(PATH_LIB)unity:
	$(dir_guard)
	git clone https://github.com/ThrowTheSwitch/Unity.git lib/unity
	git --git-dir=lib/unity/.git --work-tree=lib/unity/ checkout "v2.4.3"

all: clean-all lib test docs coverage lint

build_dep = $(PATH_LIB)unity $(HDR_ALL)

$(PATH_BUILD)%.o:: $(PATH_SRC)%.c $(build_dep)
	$(dir_guard)
	$(COMPILE_COV)

$(PATH_BUILD)%.o:: $(PATH_TEST)%.c $(build_dep)
	$(dir_guard)
	$(COMPILE)

$(PATH_BUILD)%.o:: $(PATH_UNITY)%.c $(build_dep)
	$(dir_guard)
	$(COMPILE)

$(TGT): $(OBJ_ALL)
	$(dir_guard)
	$(LINK)
