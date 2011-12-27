/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "light.h"
#include "global.h"
//--------------------------------------------------
Light::Light(int pNumber)
{
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	active = true;

	clear[0] = 0;
	clear[1] = 0;
	clear[2] = 0;

	lightNumber = pNumber;

	setAmbient(1, 1, 1, 1);                 // just temporary
	setDiffuse(1, 1, 1, 1);
	setSpecular(1, 1, 1, 1);
	setPosition(1, 1, 1, 0);		 //Standardmässig Paralellstraler
}
//--------------------------------------------------
Light::~Light()
{
}
//--------------------------------------------------
void Light::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
//--------------------------------------------------
void Light::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
//--------------------------------------------------
void Light::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
//--------------------------------------------------
void Light::setPosition(float x, float y, float z, float w)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	position[3] = w;
}
//--------------------------------------------------
void Light::setDirection(float x, float y, float z, float w)
{
	direction[0] = x;
	direction[1] = y;
	direction[2] = z;
	direction[3] = w;
}
//--------------------------------------------------
float* Light::getAmbient()
{
	return ambient;
}
//--------------------------------------------------
float* Light::getDiffuse()
{
	return diffuse;
}
//--------------------------------------------------
float* Light::getSpecular()
{
	return specular;
}
//--------------------------------------------------
float* Light::getPosition()
{
	return position;
}
//--------------------------------------------------
float* Light::getDirection()
{
	return direction;
}
//--------------------------------------------------
void Light::call()
{
	glDisable(lightNumber);
	if (active)
	{
		glEnable(lightNumber);

		glLightfv(lightNumber, GL_AMBIENT, getAmbient());
		glLightfv(lightNumber, GL_DIFFUSE, getDiffuse());
		glLightfv(lightNumber, GL_SPECULAR, getSpecular());
		glLightfv(lightNumber, GL_POSITION, getPosition());
	}
}
//--------------------------------------------------
