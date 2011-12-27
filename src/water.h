/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef WATER_H
#define WATER_H
//--------------------------------------------------
#include "vmath.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "shader.h"
//--------------------------------------------------
/**
 *  Water.
 */
class Water: public Object
{
private:
	Texture* textureLoader;
	int waterTexture;
	int displacementTexture;
	Shader *displacementShader;

public:
	/**
	*  constructor
	* @param tex reference to the texture loader
	*/
	Water(Texture* tex);
	/**
	*  destrucor
	*/
	~Water();
	/**
	*  render the water
	*/
	void render();
};
//--------------------------------------------------
#endif
