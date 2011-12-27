/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef SKYBOX_H
#define SKYBOX_H
//--------------------------------------------------
#include "vmath.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "vmath.h"
//--------------------------------------------------
/**
 *  Represents the sky (dome).
 */
class Skybox: public Object
{
private:
	bool lighting;
	Texture* textureLoader;
	float currentGlare;
	Vector3f sunDirection;
	ObjModel *skymodel;
	ObjModel *weapon;
	int sunTexture;

	void drawStars(int numberOfStars);
	void drawSky(float size, Vector4f color1, Vector4f color2);
	void drawSun(Vector3f sunPosition);
	void drawGlare();
	void resetTranslation();

public:
	/**
	 *  constructor.
	 * @param tex reference to the texture loader
	*/
	Skybox(Texture* tex);
	/**
	 *  destructor.
	*/
	~Skybox();
	/**
	 *  draw the skybox.
	 *  @param activateShaders enables or disables shaders while rendering
	*/
	void render(bool activateShaders);
	/**
	 *  update the skybox.
	 *  @param timeDifference time passed since the last frame
	*/
	void update(double timeDifference);
	/**
	 *  returns the current sun direction.
	 *  @return Vector3f vector with the sun direction
	*/
	Vector3f getSunDirection();
	/**
	 *  contains the current day time.
	*/
	float dayTime;
};
//--------------------------------------------------
#endif
