/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "material.h"
#include "global.h"
//--------------------------------------------------
Material::Material()
{
	setAmbient(0.2f, 0.2f, 0.2f, 1);
	setDiffuse(1, 1, 1, 1);
	setSpecular(0, 0, 0, 0);
	setEmission(0, 0, 0, 0);
	shininess = 30;
}
//--------------------------------------------------
Material::~Material()
{
}
//--------------------------------------------------
void Material::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
//--------------------------------------------------
void Material::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
//--------------------------------------------------
void Material::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
//--------------------------------------------------
void Material::setEmission(float r, float g, float b, float a)
{
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
}
//--------------------------------------------------
void Material::setShininess(float s)
{
	shininess = s;
}
//--------------------------------------------------
void Material::call()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
//--------------------------------------------------
