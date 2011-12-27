# -------------------------------------------------------
# Makefile to build scene
# -------------------------------------------------------

# macros
CC = g++
FLAGS = -lGL -lGLU -lSDL -lGLEW
SRC_DIR = src/
# additional flags -> enable optimizer
COMP_FLAGS = -c -O2
FILES = camera.o errorlog.o input.o light.o main.o material.o object.o objmodel.o \
	particlesystem.o scene.o shader.o shaderloader.o skybox.o terrain.o text.o \
	texture.o vmath.o water.o

main:			$(FILES)
			$(CC) $(FLAGS) -o main.out $(FILES)

camera.o:		$(SRC_DIR)camera.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)camera.cpp

errorlog.o:		$(SRC_DIR)errorlog.h	
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)errorlog.cpp

input.o:		$(SRC_DIR)global.h $(SRC_DIR)input.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)input.cpp

light.o:		$(SRC_DIR)light.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)light.cpp

main.o:			$(SRC_DIR)main.h $(SRC_DIR)global.h $(SRC_DIR)errorlog.h $(SRC_DIR)exception.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)main.cpp

material.o:		$(SRC_DIR)material.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)material.cpp

object.o:		$(SRC_DIR)object.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)object.cpp

objmodel.o:		$(SRC_DIR)objmodel.h $(SRC_DIR)global.h $(SRC_DIR)errorlog.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)objmodel.cpp

particlesystem.o:	$(SRC_DIR)particlesystem.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)particlesystem.cpp

scene.o:		$(SRC_DIR)global.h $(SRC_DIR)scene.h $(SRC_DIR)vmath.h $(SRC_DIR)errorlog.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)scene.cpp

shader.o:		$(SRC_DIR)shader.h $(SRC_DIR)errorlog.h $(SRC_DIR)exception.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)shader.cpp

shaderloader.o:		$(SRC_DIR)shaderloader.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)shaderloader.cpp

skybox.o:		$(SRC_DIR)skybox.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)skybox.cpp

terrain.o:		$(SRC_DIR)terrain.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)terrain.cpp

text.o:			$(SRC_DIR)text.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)text.cpp

texture.o:		$(SRC_DIR)texture.h $(SRC_DIR)errorlog.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)texture.cpp

vmath.o:		$(SRC_DIR)vmath.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)vmath.cpp

water.o:		$(SRC_DIR)water.h $(SRC_DIR)global.h
			$(CC) $(FLAGS) $(COMP_FLAGS) -o $@ $(SRC_DIR)water.cpp

# clean directory
clean:
			rm main.out
			echo "directory cleared"

# rebuild everything
build:
			touch $(SRC_DIR)*.cpp
			make main
			rm *.o
			echo "project successfully compiled"
		
