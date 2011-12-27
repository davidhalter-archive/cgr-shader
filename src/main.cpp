/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "main.h"
#include "global.h"
#include "errorlog.h"
#include "exception.h"
#include <sstream>
#ifdef WIN32
#include <ctime>
#include <windows.h>
#else
#include <unistd.h>
#endif
//--------------------------------------------------
// Main
int main(int argc, char* argv[])
{
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;

	//maintain an exact frame rate
	const double frameDifferenceTime = 1.0 / FPS * 1000;      // time to render a frame at a specific frame rate (in milliseconds)
	double timeLastFrame = 0;
	double timeThisFrame = 0;
	double timeDifference = 0;


	if (!initSDL())
	{
		logStream << "error initializing SDL!!" << endl;
		log->reportError(logStream.str());
		return -1;
	}

	if (!initOpenGL())
	{
		logStream << "error initializing OpenGL!!" << endl;
		log->reportError(logStream.str());
		return -1;
	}

	if (!initGLEW())
	{
		logStream << "error initializing GLEW!!" << endl;
		log->reportError(logStream.str());
		return -1;
	}

	logStream.str("");
	logStream << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl << endl;
	log->reportError(logStream.str());

	if (GLEW_VERSION_2_0)
	{
		logStream.str("");
		logStream << "OpenGL 2.0 available" << endl << endl;
		log->reportError(logStream.str());
	}
	else
	{
		logStream.str("");
		logStream << "OpenGL 2.0 not available" << endl << endl;
		log->reportError(logStream.str());
	}

	// check if necessary extensions to run the shader are available
	if (!glewIsSupported("GL_ARB_shader_objects GL_ARB_vertex_shader GL_ARB_fragment_shader GL_ARB_vertex_program"))
	{
		logStream.str("");
		logStream << "one or more extensions to run the shader are not available!!" << endl;
		log->reportError(logStream.str());
		return -1;
	}

	// check if necessary extensions to run cube mapping are available
	if (!GL_ARB_texture_cube_map)
	{
		logStream.str("");
		logStream << "GL_ARB_texture_cube_map extension not available!!" << endl;
		log->reportError(logStream.str());
		return -1;
	}

	input = new Input();
	try
	{
		scene = new Scene(input);
	}
	catch (Exception e)
	{
		logStream.str("");
		logStream << e.getMessage() << endl;
		log->reportError(logStream.str());
		return -1;
	}

	while (!input->keyPressed(SDLK_ESCAPE))
	{
		timeThisFrame = SDL_GetTicks();                                     // get time in ms
		timeDifference = timeThisFrame - timeLastFrame;

		// if time difference between this and the last frame is greater
		// or equal than the specified frame time difference then render
		// the frame
		if (timeDifference >= frameDifferenceTime)
		{
			timeLastFrame = timeThisFrame;
			input->update();							// Process any ocuring events
			scene->update(timeDifference);
			scene->render();							// Draw your graphics
		}
		else                        // if the timedifference is smaller, than sleep for a specified time
		{
			int timeToSleep = (int) (frameDifferenceTime - timeDifference);           // in milliseconds

			// the following stuff is a little bit ugly but there are different
			// sleep functions for Unix and Windows systems
#ifdef WIN32
			Sleep(timeToSleep);
#else
			usleep(1000 * timeToSleep);
#endif
		}
	}

	delete input;
	delete scene;
	SDL_Quit();

	return 0;
}
//--------------------------------------------------
// Init OpenGL
// Returnvalue: true if init was successful
bool initOpenGL()
{
	float ratio = (float)width / (float)height;			// Calculate and store the aspect ratio of the display
	glMatrixMode(GL_PROJECTION);					// Change to the projection matrix
	gluPerspective(50.0, ratio, 1, 100000.0);		// Set view perspective
	glMatrixMode(GL_MODELVIEW);						// Change to the modelview matrix
	return true;
}
//--------------------------------------------------
// Init SDL
// Returnvalue: true if init was successful
bool initSDL()
{
	const SDL_VideoInfo* info = NULL;				// Information about the current video settings
	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;

	int bpp = 0;									// Color depth in bits of our window
	int flags = 0;									// Flags we will pass into SDL_SetVideoMode



	if (SDL_Init(SDL_INIT_VIDEO) < 0)					// First, initialize SDL's video subsystem (video only)
	{
		logStream << "Video initialization failed: " << SDL_GetError() << endl;
		log->reportError(logStream.str());
		// fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		return false;
	}

	info = SDL_GetVideoInfo();						// Get some video information

	if (!info)										// This should probably never happen
	{
		logStream.str("");
		logStream << "Video query failed: " << SDL_GetError() << endl;
		log->reportError(logStream.str());
		// fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		return false;
	}

	bpp = info->vfmt->BitsPerPixel;					// Get color depth

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);		// Sets the color-depth of the red, green and blue color-part
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);		// to 8bit (standard today)
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		// Set depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	// Sets wether to enable or disable doublebuffering

	flags = SDL_OPENGL | SDL_RESIZABLE;/* | SDL_DOUBLEBUF;*/				// Set flags for SDL OpenGL

	if (fullscreen)
	{
		flags = flags | SDL_FULLSCREEN;					// Set flag for fullscreen or windowed mode
	}

	if (!SDL_SetVideoMode(width, height, bpp, flags))	// Set the video mode
	{													// If failed, print error message
		logStream.str("");
		logStream << "Video mode set failed: " << SDL_GetError() << endl;
		log->reportError(logStream.str());
		return false;
	}


	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}
//--------------------------------------------------
// Init GLEW
// Returnvalue: true if init was successful
bool initGLEW()
{
	// initialize GLEW and shaders
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return false;
	}
	return true;
}
//--------------------------------------------------
