#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/input.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/light.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/text.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/errorlog.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/water.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/camera.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/vmath.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/objmodel.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/material.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/skybox.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/scene.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/object.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/terrain.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/particlesystem.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/texture.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/textfile.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shader.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/main.o \
	${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shaderloader.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/muster

dist/Debug/GNU-Linux-x86/muster: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Debug/GNU-Linux-x86/muster ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/input.o: ../../../Sourcecode/src/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/input.o ../../../Sourcecode/src/input.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/light.o: ../../../Sourcecode/src/light.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/light.o ../../../Sourcecode/src/light.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/text.o: ../../../Sourcecode/src/text.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/text.o ../../../Sourcecode/src/text.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/errorlog.o: ../../../Sourcecode/src/errorlog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/errorlog.o ../../../Sourcecode/src/errorlog.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/water.o: ../../../Sourcecode/src/water.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/water.o ../../../Sourcecode/src/water.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/camera.o: ../../../Sourcecode/src/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/camera.o ../../../Sourcecode/src/camera.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/vmath.o: ../../../Sourcecode/src/vmath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/vmath.o ../../../Sourcecode/src/vmath.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/objmodel.o: ../../../Sourcecode/src/objmodel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/objmodel.o ../../../Sourcecode/src/objmodel.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/material.o: ../../../Sourcecode/src/material.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/material.o ../../../Sourcecode/src/material.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/skybox.o: ../../../Sourcecode/src/skybox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/skybox.o ../../../Sourcecode/src/skybox.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/scene.o: ../../../Sourcecode/src/scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/scene.o ../../../Sourcecode/src/scene.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/object.o: ../../../Sourcecode/src/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/object.o ../../../Sourcecode/src/object.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/terrain.o: ../../../Sourcecode/src/terrain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/terrain.o ../../../Sourcecode/src/terrain.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/particlesystem.o: ../../../Sourcecode/src/particlesystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/particlesystem.o ../../../Sourcecode/src/particlesystem.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/texture.o: ../../../Sourcecode/src/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/texture.o ../../../Sourcecode/src/texture.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/textfile.o: ../../../Sourcecode/src/textfile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/textfile.o ../../../Sourcecode/src/textfile.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shader.o: ../../../Sourcecode/src/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shader.o ../../../Sourcecode/src/shader.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/main.o: ../../../Sourcecode/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/main.o ../../../Sourcecode/src/main.cpp

${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shaderloader.o: ../../../Sourcecode/src/shaderloader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/_ext/media/disk/Data/Semester6/BA/CD/Linux/Muster/Muster/../../../Sourcecode/src/shaderloader.o ../../../Sourcecode/src/shaderloader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/muster

# Subprojects
.clean-subprojects:
