/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
//Vorlage
#include "particlesystem.h"
#include "global.h"
#include <time.h>
//--------------------------------------------------
ParticleSystem::ParticleSystem(Texture* tex, Vector3f pos)
{
	//Loading the textures
	fireTexture1 = tex->loadTexture("fire", true, false);
	fireTexture2 = tex->loadTexture("fire2", true, false);
	smokeTexture = tex->loadTexture("smoke", true, false);

	//Position of the whole System (Vector3f)
	position = pos;

	numberOfParticles = 700;

	particles = new Particle[numberOfParticles];


	//Code Aufgaben: ----------------------------------------
	
	//-------------------------------------------------------
}
//--------------------------------------------------
ParticleSystem::~ParticleSystem()
{
	delete [] particles;
}
//--------------------------------------------------
void ParticleSystem::render(bool activateShaders)
{
	//Code Aufgaben: ----------------------------------------
	
	//-------------------------------------------------------
}
//--------------------------------------------------
void ParticleSystem::update(float timeDifference)
{
	//Code Aufgaben: ----------------------------------------
	
	//-------------------------------------------------------
}
//--------------------------------------------------
