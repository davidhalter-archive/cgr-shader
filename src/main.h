/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef MAIN_H
#define MAIN_H
//--------------------------------------------------
#include "scene.h"
#include "input.h"
#include "shader.h"
//--------------------------------------------------
/**
 * @mainpage OpenGL-Shader-Praktikum
 * Main file
 */
//int	width = 320;								// Dimensions of our window
//int height = 240;
int	width = 1024;									// Dimensions of our window
int height = 768;
bool fullscreen = true;							// Fullscreen or windowed mode
Scene* scene;
Input* input;
Shader* shader;
int FPS = 60;
//--------------------------------------------------
int main(int argc, char* argv[]);					// Main
bool initOpenGL();								    // Init OpenGL
bool initSDL();										// Init SDL Engine
bool initGLEW();									// Init GLEW
//--------------------------------------------------
#endif
