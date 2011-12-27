/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
//--------------------------------------------------
#include "vmath.h"
#include "camera.h"
#include "object.h"
#include "shader.h"
#include "texture.h"

struct Particle  //Particles
{
	Vector3f position, direction;
	Vector4f color;
	float age, velocity, phase1, phase2;
};
//--------------------------------------------------
/**
 *  A particle system.
 */
class ParticleSystem: public Object
{
private:
	int numberOfParticles;
	Particle *particles;
	Vector3f position;
	int fireTexture1;
	int fireTexture2;
	int smokeTexture;
	float rand1()
	{
		return ((float)rand() / (float)RAND_MAX);
	}
	float randMinMax(float x, float y)
	{
		return (rand1()*((y) - (x)) + (x));
	}

public:
	/**
	 *  constructor.
	 *  @param tex a reference to the texture loader
	 *  @param pos the position of the particle in the world
	 */
	ParticleSystem(Texture* tex, Vector3f pos);
	/**
	 *  destructor.
	 */
	~ParticleSystem();
	/**
	 * render the system.
	 * @param activateShaders states if shaders are active while rendering
	 */
	void render(bool activateShaders);
	/**
	 * update the system.
	 * @param timeDifference time passed since the last update
	 */
	void update(float timeDifference);

};
//---------------------------------------------------------------------------
#endif
