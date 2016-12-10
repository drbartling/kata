#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/18f4303b/unity.o \
	${OBJECTDIR}/_ext/511e4115/generic_circular_buffer.o \
	${OBJECTDIR}/_ext/d2aa2781/test_generic_circular_buffer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/generic_circular_buffer.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/generic_circular_buffer.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/generic_circular_buffer ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/18f4303b/unity.o: ../../../Unity/src/unity.c
	${MKDIR} -p ${OBJECTDIR}/_ext/18f4303b
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/18f4303b/unity.o ../../../Unity/src/unity.c

${OBJECTDIR}/_ext/511e4115/generic_circular_buffer.o: ../src/generic_circular_buffer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/generic_circular_buffer.o ../src/generic_circular_buffer.c

${OBJECTDIR}/_ext/d2aa2781/test_generic_circular_buffer.o: ../test/test_generic_circular_buffer.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d2aa2781
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2aa2781/test_generic_circular_buffer.o ../test/test_generic_circular_buffer.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
