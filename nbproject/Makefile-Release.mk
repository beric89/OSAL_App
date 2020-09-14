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
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/Windows/OSALInit.o \
	${OBJECTDIR}/Windows/clock.o \
	${OBJECTDIR}/Windows/console.o \
	${OBJECTDIR}/Windows/filesystem.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f10 \
	${TESTDIR}/TestFiles/f11 \
	${TESTDIR}/TestFiles/f12 \
	${TESTDIR}/TestFiles/f16 \
	${TESTDIR}/TestFiles/f13 \
	${TESTDIR}/TestFiles/f14 \
	${TESTDIR}/TestFiles/f15

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/test_OSAL_APIInit.o \
	${TESTDIR}/tests/test_OSAL_Close.o \
	${TESTDIR}/tests/test_OSAL_Console_File_Open.o \
	${TESTDIR}/tests/test_OSAL_Create.o \
	${TESTDIR}/tests/test_OSAL_Create_Directory.o \
	${TESTDIR}/tests/test_OSAL_GetLocalTime.o \
	${TESTDIR}/tests/test_OSAL_Open.o \
	${TESTDIR}/tests/test_OSAL_Open_Directory.o \
	${TESTDIR}/tests/test_OSAL_Printf.o \
	${TESTDIR}/tests/test_OSAL_PrintfDIsable.o \
	${TESTDIR}/tests/test_OSAL_PrintfEnable.o \
	${TESTDIR}/tests/test_OSAL_Read.o \
	${TESTDIR}/tests/test_OSAL_Remove.o \
	${TESTDIR}/tests/test_OSAL_Remove_Directory.o \
	${TESTDIR}/tests/test_OSAL_SetLocalTime.o \
	${TESTDIR}/tests/test_OSAL_Write.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osal_app.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osal_app.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osal_app ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Windows/OSALInit.o: Windows/OSALInit.c
	${MKDIR} -p ${OBJECTDIR}/Windows
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/OSALInit.o Windows/OSALInit.c

${OBJECTDIR}/Windows/clock.o: Windows/clock.c
	${MKDIR} -p ${OBJECTDIR}/Windows
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/clock.o Windows/clock.c

${OBJECTDIR}/Windows/console.o: Windows/console.c
	${MKDIR} -p ${OBJECTDIR}/Windows
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/console.o Windows/console.c

${OBJECTDIR}/Windows/filesystem.o: Windows/filesystem.c
	${MKDIR} -p ${OBJECTDIR}/Windows
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/filesystem.o Windows/filesystem.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/test_OSAL_APIInit.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/test_OSAL_Close.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/test_OSAL_Console_File_Open.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/test_OSAL_Create.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/test_OSAL_Create_Directory.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/test_OSAL_GetLocalTime.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/test_OSAL_Open.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/test_OSAL_Open_Directory.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f9: ${TESTDIR}/tests/test_OSAL_Printf.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f10: ${TESTDIR}/tests/test_OSAL_PrintfDIsable.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f10 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f11: ${TESTDIR}/tests/test_OSAL_PrintfEnable.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f11 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f12: ${TESTDIR}/tests/test_OSAL_Read.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f12 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f16: ${TESTDIR}/tests/test_OSAL_Remove.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f16 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f13: ${TESTDIR}/tests/test_OSAL_Remove_Directory.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f13 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f14: ${TESTDIR}/tests/test_OSAL_SetLocalTime.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f14 $^ ${LDLIBSOPTIONS}   -lcunit 

${TESTDIR}/TestFiles/f15: ${TESTDIR}/tests/test_OSAL_Write.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f15 $^ ${LDLIBSOPTIONS}   -lcunit 


${TESTDIR}/tests/test_OSAL_APIInit.o: tests/test_OSAL_APIInit.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_APIInit.o tests/test_OSAL_APIInit.c


${TESTDIR}/tests/test_OSAL_Close.o: tests/test_OSAL_Close.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Close.o tests/test_OSAL_Close.c


${TESTDIR}/tests/test_OSAL_Console_File_Open.o: tests/test_OSAL_Console_File_Open.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Console_File_Open.o tests/test_OSAL_Console_File_Open.c


${TESTDIR}/tests/test_OSAL_Create.o: tests/test_OSAL_Create.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Create.o tests/test_OSAL_Create.c


${TESTDIR}/tests/test_OSAL_Create_Directory.o: tests/test_OSAL_Create_Directory.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Create_Directory.o tests/test_OSAL_Create_Directory.c


${TESTDIR}/tests/test_OSAL_GetLocalTime.o: tests/test_OSAL_GetLocalTime.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_GetLocalTime.o tests/test_OSAL_GetLocalTime.c


${TESTDIR}/tests/test_OSAL_Open.o: tests/test_OSAL_Open.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Open.o tests/test_OSAL_Open.c


${TESTDIR}/tests/test_OSAL_Open_Directory.o: tests/test_OSAL_Open_Directory.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Open_Directory.o tests/test_OSAL_Open_Directory.c


${TESTDIR}/tests/test_OSAL_Printf.o: tests/test_OSAL_Printf.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Printf.o tests/test_OSAL_Printf.c


${TESTDIR}/tests/test_OSAL_PrintfDIsable.o: tests/test_OSAL_PrintfDIsable.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_PrintfDIsable.o tests/test_OSAL_PrintfDIsable.c


${TESTDIR}/tests/test_OSAL_PrintfEnable.o: tests/test_OSAL_PrintfEnable.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_PrintfEnable.o tests/test_OSAL_PrintfEnable.c


${TESTDIR}/tests/test_OSAL_Read.o: tests/test_OSAL_Read.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Read.o tests/test_OSAL_Read.c


${TESTDIR}/tests/test_OSAL_Remove.o: tests/test_OSAL_Remove.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Remove.o tests/test_OSAL_Remove.c


${TESTDIR}/tests/test_OSAL_Remove_Directory.o: tests/test_OSAL_Remove_Directory.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Remove_Directory.o tests/test_OSAL_Remove_Directory.c


${TESTDIR}/tests/test_OSAL_SetLocalTime.o: tests/test_OSAL_SetLocalTime.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_SetLocalTime.o tests/test_OSAL_SetLocalTime.c


${TESTDIR}/tests/test_OSAL_Write.o: tests/test_OSAL_Write.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/test_OSAL_Write.o tests/test_OSAL_Write.c


${OBJECTDIR}/Windows/OSALInit_nomain.o: ${OBJECTDIR}/Windows/OSALInit.o Windows/OSALInit.c 
	${MKDIR} -p ${OBJECTDIR}/Windows
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Windows/OSALInit.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/OSALInit_nomain.o Windows/OSALInit.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Windows/OSALInit.o ${OBJECTDIR}/Windows/OSALInit_nomain.o;\
	fi

${OBJECTDIR}/Windows/clock_nomain.o: ${OBJECTDIR}/Windows/clock.o Windows/clock.c 
	${MKDIR} -p ${OBJECTDIR}/Windows
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Windows/clock.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/clock_nomain.o Windows/clock.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Windows/clock.o ${OBJECTDIR}/Windows/clock_nomain.o;\
	fi

${OBJECTDIR}/Windows/console_nomain.o: ${OBJECTDIR}/Windows/console.o Windows/console.c 
	${MKDIR} -p ${OBJECTDIR}/Windows
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Windows/console.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/console_nomain.o Windows/console.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Windows/console.o ${OBJECTDIR}/Windows/console_nomain.o;\
	fi

${OBJECTDIR}/Windows/filesystem_nomain.o: ${OBJECTDIR}/Windows/filesystem.o Windows/filesystem.c 
	${MKDIR} -p ${OBJECTDIR}/Windows
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Windows/filesystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Windows/filesystem_nomain.o Windows/filesystem.c;\
	else  \
	    ${CP} ${OBJECTDIR}/Windows/filesystem.o ${OBJECTDIR}/Windows/filesystem_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f10 || true; \
	    ${TESTDIR}/TestFiles/f11 || true; \
	    ${TESTDIR}/TestFiles/f12 || true; \
	    ${TESTDIR}/TestFiles/f16 || true; \
	    ${TESTDIR}/TestFiles/f13 || true; \
	    ${TESTDIR}/TestFiles/f14 || true; \
	    ${TESTDIR}/TestFiles/f15 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
