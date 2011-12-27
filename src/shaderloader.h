/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef SHADERLOADER_H
#define SHADERLOADER_H
//--------------------------------------------------
#include "global.h"
#include "shader.h"
#include <list>
//--------------------------------------------------
/**
 *  Name of a Shader
 */
struct Shadername
{
	string strFrag;
	string strVert;
	Shader *shader;
};
//--------------------------------------------------
/**
 *  Loads shaders and assures not to load them multiple times for different materials.
 */
class Shaderloader
{
private:
	int loadFile(string Name);
	list <Shadername>::iterator nameListIterator;
	list <Shadername> nameList;

public:
	/**
	 *  constructor.
	 */
	Shaderloader();
	/**
	 *  destructor.
	 */
	~Shaderloader();

	/**
	 *  creates a shader program and returns a reference to it.
	 * @param vert name of the vertex shader (without file ending)
	 * @param frag name of the fragment shader (without file ending)
	 * @return reference to the shader object that has been newly created
	 */
	Shader* loadShader(string vert, string frag);
};
//--------------------------------------------------
#endif
