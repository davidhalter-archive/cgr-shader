/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
//--------------------------------------------------
#ifdef WIN32
#include <windows.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_byteorder.h>
#else
#include <stdarg.h>
#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>
#include <SDL/SDL_byteorder.h>
#endif
//--------------------------------------------------
#include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//--------------------------------------------------
using namespace std;
extern int width;
extern int height;
//--------------------------------------------------
#endif
