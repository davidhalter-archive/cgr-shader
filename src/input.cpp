/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "global.h"
#include "input.h"
//--------------------------------------------------
Input::Input()
{
	mouseRel[0] = 0;
	mouseRel[1] = 0;

	for (int i = 0;i < 312;i++)
	{
		keys[i] = false;
		keysEvent[i] = false;
	}
}
//--------------------------------------------------
void Input::update()
{
	SDL_Event event;										// SDL event placeholder

	while (SDL_PollEvent(&event))							// Grab all the events off the queue
	{
		switch (event.type)
		{
		case SDL_QUIT:
			eventKeyDown(SDLK_ESCAPE);
			break;

		case SDL_KEYDOWN:								// Handle each Keydown

			eventKeyDown(event.key.keysym.sym);

			break;

		case SDL_KEYUP:

			eventKeyUp(event.key.keysym.sym);

			break;

		case SDL_MOUSEMOTION:
			mouseRel[0] += event.motion.xrel;
			mouseRel[1] += event.motion.yrel;
			break;

		default:
			break;
		}
	}
}
//--------------------------------------------------
void Input::eventKeyUp(int key)
{
	if (key < 0)return;
	if (key > 311)return;
	keys[key] = false;
}
//--------------------------------------------------
void Input::eventKeyDown(int key)
{
	if (key < 0)return;
	if (key > 311)return;
	keys[key] = true;
	keysEvent[key] = true;
}
//--------------------------------------------------
bool Input::isKeyDown(int key)
{
	return keys[key];
}
//--------------------------------------------------
int Input::getMouseMotionX()
{
	int motion = mouseRel[0];
	mouseRel[0] = 0;
	return motion;
}
//--------------------------------------------------
int Input::getMouseMotionY()
{
	int motion = mouseRel[1];
	mouseRel[1] = 0;
	return motion;
}
//--------------------------------------------------
bool Input::keyPressed(int key)
{
	bool status = keysEvent[key];
	keysEvent[key] = false;
	return status;
}
//--------------------------------------------------
