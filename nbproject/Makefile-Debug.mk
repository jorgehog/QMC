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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/QMCInitializer.o \
	${OBJECTDIR}/QMCmain.o \
	${OBJECTDIR}/Kinetics.o \
	${OBJECTDIR}/Coulomb.o \
	${OBJECTDIR}/Sampling.o \
	${OBJECTDIR}/OrbitalsOO.o \
	${OBJECTDIR}/lib.o \
	${OBJECTDIR}/functions.o \
	${OBJECTDIR}/Diffusion.o \
	${OBJECTDIR}/System.o \
	${OBJECTDIR}/Jastrow.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-llapack -lblas -larmadillo -O3
CXXFLAGS=-llapack -lblas -larmadillo -O3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../programmer/Armadillo/lib64 -larmadillo

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Orbitals.o: Orbitals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Orbitals.o Orbitals.cpp

${OBJECTDIR}/Walker.o: Walker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Walker.o Walker.cpp

${OBJECTDIR}/Potential.o: Potential.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Potential.o Potential.cpp

${OBJECTDIR}/QMC.o: QMC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMC.o QMC.cpp

${OBJECTDIR}/QMCInitializer.o: QMCInitializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMCInitializer.o QMCInitializer.cpp

${OBJECTDIR}/QMCmain.o: QMCmain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMCmain.o QMCmain.cpp

${OBJECTDIR}/Kinetics.o: Kinetics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Kinetics.o Kinetics.cpp

${OBJECTDIR}/Coulomb.o: Coulomb.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Coulomb.o Coulomb.cpp

${OBJECTDIR}/Sampling.o: Sampling.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sampling.o Sampling.cpp

${OBJECTDIR}/OrbitalsOO.o: OrbitalsOO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/OrbitalsOO.o OrbitalsOO.cpp

${OBJECTDIR}/lib.o: lib.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib.o lib.cpp

${OBJECTDIR}/functions.o: functions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/functions.o functions.cpp

${OBJECTDIR}/Diffusion.o: Diffusion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Diffusion.o Diffusion.cpp

${OBJECTDIR}/System.o: System.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/System.o System.cpp

${OBJECTDIR}/Jastrow.o: Jastrow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Jastrow.o Jastrow.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/VMCtest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -larmadillo -lblas -llapack -larmadillo -lblas -llapack -O3 -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -larmadillo -larmadillo 


${TESTDIR}/tests/VMCtest.o: tests/VMCtest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I../../../programmer/Armadillo/include -MMD -MP -MF $@.d -o ${TESTDIR}/tests/VMCtest.o tests/VMCtest.cpp


${OBJECTDIR}/Orbitals_nomain.o: ${OBJECTDIR}/Orbitals.o Orbitals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Orbitals.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Orbitals_nomain.o Orbitals.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Orbitals.o ${OBJECTDIR}/Orbitals_nomain.o;\
	fi

${OBJECTDIR}/Walker_nomain.o: ${OBJECTDIR}/Walker.o Walker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Walker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Walker_nomain.o Walker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Walker.o ${OBJECTDIR}/Walker_nomain.o;\
	fi

${OBJECTDIR}/Potential_nomain.o: ${OBJECTDIR}/Potential.o Potential.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Potential.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Potential_nomain.o Potential.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Potential.o ${OBJECTDIR}/Potential_nomain.o;\
	fi

${OBJECTDIR}/QMC_nomain.o: ${OBJECTDIR}/QMC.o QMC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/QMC.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMC_nomain.o QMC.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/QMC.o ${OBJECTDIR}/QMC_nomain.o;\
	fi

${OBJECTDIR}/QMCInitializer_nomain.o: ${OBJECTDIR}/QMCInitializer.o QMCInitializer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/QMCInitializer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMCInitializer_nomain.o QMCInitializer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/QMCInitializer.o ${OBJECTDIR}/QMCInitializer_nomain.o;\
	fi

${OBJECTDIR}/QMCmain_nomain.o: ${OBJECTDIR}/QMCmain.o QMCmain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/QMCmain.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/QMCmain_nomain.o QMCmain.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/QMCmain.o ${OBJECTDIR}/QMCmain_nomain.o;\
	fi

${OBJECTDIR}/Kinetics_nomain.o: ${OBJECTDIR}/Kinetics.o Kinetics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Kinetics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Kinetics_nomain.o Kinetics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Kinetics.o ${OBJECTDIR}/Kinetics_nomain.o;\
	fi

${OBJECTDIR}/Coulomb_nomain.o: ${OBJECTDIR}/Coulomb.o Coulomb.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Coulomb.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Coulomb_nomain.o Coulomb.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Coulomb.o ${OBJECTDIR}/Coulomb_nomain.o;\
	fi

${OBJECTDIR}/Sampling_nomain.o: ${OBJECTDIR}/Sampling.o Sampling.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Sampling.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sampling_nomain.o Sampling.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Sampling.o ${OBJECTDIR}/Sampling_nomain.o;\
	fi

${OBJECTDIR}/OrbitalsOO_nomain.o: ${OBJECTDIR}/OrbitalsOO.o OrbitalsOO.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/OrbitalsOO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/OrbitalsOO_nomain.o OrbitalsOO.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/OrbitalsOO.o ${OBJECTDIR}/OrbitalsOO_nomain.o;\
	fi

${OBJECTDIR}/lib_nomain.o: ${OBJECTDIR}/lib.o lib.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib_nomain.o lib.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lib.o ${OBJECTDIR}/lib_nomain.o;\
	fi

${OBJECTDIR}/functions_nomain.o: ${OBJECTDIR}/functions.o functions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/functions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/functions_nomain.o functions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/functions.o ${OBJECTDIR}/functions_nomain.o;\
	fi

${OBJECTDIR}/Diffusion_nomain.o: ${OBJECTDIR}/Diffusion.o Diffusion.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Diffusion.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Diffusion_nomain.o Diffusion.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Diffusion.o ${OBJECTDIR}/Diffusion_nomain.o;\
	fi

${OBJECTDIR}/System_nomain.o: ${OBJECTDIR}/System.o System.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/System.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/System_nomain.o System.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/System.o ${OBJECTDIR}/System_nomain.o;\
	fi

${OBJECTDIR}/Jastrow_nomain.o: ${OBJECTDIR}/Jastrow.o Jastrow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Jastrow.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I../../../programmer/Armadillo/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Jastrow_nomain.o Jastrow.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Jastrow.o ${OBJECTDIR}/Jastrow_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qmc

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
