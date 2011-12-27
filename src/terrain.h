/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef TERRAIN_H
#define TERRAIN_H
//--------------------------------------------------
#include "vmath.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
//--------------------------------------------------
/**
 *  Terrain.
 */
class Terrain: public Object
{
private:
	ObjModel *terrainModel;

public:
	/**
	 *  constructor.
	 * @param tex reference to the texture loader
	*/
	Terrain(Texture* tex);
	/**
	 *  destructor.
	*/
	~Terrain();
	/**
	 *  draw the terrain.
	 *  @param activateShaders enables or disables shaders while rendering
	*/
	void render(bool activateShaders);
};
//--------------------------------------------------
#endif
