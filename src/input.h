/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef INPUT_H
#define INPUT_H
//--------------------------------------------------
#include "global.h"
#include <list>
//--------------------------------------------------
/**
 *  Manages the user input.
 */
class Input
{
private:
	bool keys[312];
	bool keysEvent[312];
	int mouseRel[2];
	/**
	 * Event for key pressed.
	 * @param key code of the pressed key
	 */
	void eventKeyUp(int key);
	/**
	 * Event for key released.
	 * @param key code of the released key
	 */
	void eventKeyDown(int key);

public:
	/**
	 * constructor
	 */
	Input();
	/**
	 * Returns true, as long as the requested key is pressed.
	 * @param key Key code
	 * @return true if the key is pressed down
	 */
	bool isKeyDown(int key);
	/**
	 * Returns true only once, if the requested key is pressed.
	 * @param key Key code
	 * @return true if the key is pressed down
	 */
	bool keyPressed(int key);
	/**
	 * Returns the number of pixels the mouse has moved in x direction since the last poll.
	 * @return number of pixels the mouse has moved in x direction
	 */
	int getMouseMotionX();
	/**
	 * Returns the number of pixels the mouse has moved in y direction since the last poll.
	 * @return number of pixels the mouse has moved in y direction
	 */
	int getMouseMotionY();
	/**
	 * Poll the key events from sdl.
	 */
	void update();
};
//--------------------------------------------------
#endif
