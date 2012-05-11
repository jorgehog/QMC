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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Orbitals.o \
	${OBJECTDIR}/Walker.o \
	${OBJECTDIR}/Potential.o \
	${OBJECTDIR}/QMC.o \
	${OBJECTDIR}/QMCmain.o \
	${OBJECTDIR}/Kinetics.o \
	${OBJECTDIR}/DMC_old.o \
	${OBJECTDIR}/lib.o \
	${OBJECTDIR}/System.o \
	${OBJECTDIR}/vmc_old.o \
	${OBJECTDIR}/Jastrow.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Orbitals.o: nbproject/Makefile-${CND_CONF}.mk Orbitals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Orbitals.o Orbitals.cpp

${OBJECTDIR}/Walker.o: nbproject/Makefile-${CND_CONF}.mk Walker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Walker.o Walker.cpp

${OBJECTDIR}/Potential.o: nbproject/Makefile-${CND_CONF}.mk Potential.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Potential.o Potential.cpp

${OBJECTDIR}/QMC.o: nbproject/Makefile-${CND_CONF}.mk QMC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMC.o QMC.cpp

${OBJECTDIR}/QMCmain.o: nbproject/Makefile-${CND_CONF}.mk QMCmain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMCmain.o QMCmain.cpp

${OBJECTDIR}/Kinetics.o: nbproject/Makefile-${CND_CONF}.mk Kinetics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Kinetics.o Kinetics.cpp

${OBJECTDIR}/DMC_old.o: nbproject/Makefile-${CND_CONF}.mk DMC_old.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DMC_old.o DMC_old.cpp

${OBJECTDIR}/lib.o: nbproject/Makefile-${CND_CONF}.mk lib.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib.o lib.cpp

${OBJECTDIR}/System.o: nbproject/Makefile-${CND_CONF}.mk System.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/System.o System.cpp

${OBJECTDIR}/vmc_old.o: nbproject/Makefile-${CND_CONF}.mk vmc_old.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/vmc_old.o vmc_old.cpp

${OBJECTDIR}/Jastrow.o: nbproject/Makefile-${CND_CONF}.mk Jastrow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Jastrow.o Jastrow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
