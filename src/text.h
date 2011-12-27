/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef TEXT_H
#define TEXT_H
//--------------------------------------------------
#include "vmath.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include <string>
//--------------------------------------------------
/**
 *  Makes text on the scree possible.
 */
class Text: public Object
{
private:
	Texture* textureLoader;
	int alphabetTexture;
	string screenText;
	void begin2D();
	void end2D();

public:
	/**
	*  constructor
	* @param tex reference to the texture loader
	*/
	Text(Texture* tex);
	/**
	*  destructor
	*/
	~Text();
	/**
	* render the text onto the screen
	* @param activateShaders state of the shader (normally false)
	*/
	void render(bool activateShaders);
	/**
	* set a new text
	* @param t the new string
	*/
	void setText(string t);
};
//--------------------------------------------------
#endif
