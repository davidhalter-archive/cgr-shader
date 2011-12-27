/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H
//--------------------------------------------------
#include "global.h"
//--------------------------------------------------
/**
 *  Represents an OpenGL material.
 */
class Material
{
private:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shininess;

public:
	/**
	 * constructor
	 */
	Material();
	/**
	 * destructor
	 */
	~Material();

	/**
	 * Set the ambient color of the material.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setAmbient(float r, float g, float b, float a);
	/**
	 * Set the diffuse color of the material.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setDiffuse(float r, float g, float b, float a);
	/**
	 * Set the specular color of the material.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setSpecular(float r, float g, float b, float a);
	/**
	 * Set the emission color of the material.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setEmission(float r , float g, float b, float a);
	/**
	 * Set the shininess of the material.
	 * @param shininess New shininess of the material
	 */
	void setShininess(float shininess);
	/**
	 * Set all the material parameters
	 */
	void call();
};
//--------------------------------------------------
#endif
