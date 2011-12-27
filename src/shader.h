/**************************************************/
/*  Authors:                Richard Steiner		  */
/*  Date:                   19.09.2008            */
/**************************************************/
#ifndef SHADER_H
#define SHADER_H
//--------------------------------------------------
#include "global.h"
#include <string>
#include "vmath.h"
//--------------------------------------------------
/**
 *  This class allows you to load and use custom shaders. You can disable
 *  the shader to use standard OpenGL shading again.
 *  Furthermore, you can pass variables over to the shader.
 */
class Shader
{
private:
	string vertShaderName;
	string fragShaderName;
	/**
	 * handle to the shader program.
	 */
	GLuint p;
	/**
	 * handles for vertex and fragment shaders.
	 */
	GLuint v, f;
	char* textFileRead(const char *fn);
	/**
	 * Print the shader info log to see whether compilation succeeded
	 * @param shader Handle to the shader object
	 */
	void printShaderInfoLog(GLuint shader, string shaderName);
	/**
	 * Print program info log to see whether the vertex and fragment
	 * shaders successfully linked
	 * @param program Handle to program object
	 * @param shaderName Complete path of the shader source file
	 */
	void printProgramInfoLog(GLuint program);
	int location;
public:
	/**
	 * Define a defaultShader. Disable will use this Shader, if a
	 * defaultShader is set
	 */
	static Shader *defaultShader;
	/**
	 * constructor
	 */
	Shader();
	/**
	 * Loads, compiles and links a shader specified by vertex and fragment
	 * @param vertex Path and filename of vertex shader
	 * @param fragment Path and filename of fragment shader
	 */
	void load(string vertex, string fragment);
	/**
	 * Enables the shader, i.e. the functionality of the shader is used instead of
	 * the fixed function palette of OpenGL
	 */
	void enable();
	/**
	 * Setup the Defaultshader.
	 */
	static void setDefaultShader(Shader *defaultShaderp);
	/**
	 * Disables current shader, and use the default Shader
	 */
	static void useDefaultShader();
	/**
	 * Disables the shader, i.e. the fixed function palette of OpenGL is used again
	 */
	static void disable();
	/**
	 * Loads the texture specified by texID into TU0 and initializes the uniform sampler variable name with
	 * 0
	 * @param target Specifies type of texture (e.g. GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_ARB, etc.)
	 * @param texID Handle to the texture to load
	 * @param name Name of the uniform sampler variable in the shader
	 */
	void loadTextureTU0(int target, int texID, string name);
	/**
	 * Loads the texture specified by texID into TU1 and initializes the uniform sampler variable name with
	 * 1
	 * @param target Specifies type of texture (e.g. GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_ARB, etc.)
	 * @param texID Handle to the texture to load
	 * @param name Name of the uniform sampler variable in the shader
	 */
	void loadTextureTU1(int target, int texID, string name);
	/**
	 * Loads the texture specified by texID into TU2 and initializes the uniform sampler variable name with
	 * 2
	 * @param target Specifies type of texture (e.g. GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_ARB, etc.)
	 * @param texID Handle to the texture to load
	 * @param name Name of the uniform sampler variable in the shader
	 */
	void loadTextureTU2(int target, int texID, string name);
	/**
	 * Loads the texture specified by texID into TU3 and initializes the uniform sampler variable name with
	 * 3
	 * @param target Specifies type of texture (e.g. GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_ARB, etc.)
	 * @param texID Handle to the texture to load
	 * @param name Name of the uniform sampler variable in the shader
	 */
	void loadTextureTU3(int target, int texID, string name);
	/**
	 * Loads the texture specified by texID into TU4 and initializes the uniform sampler variable name with
	 * 4
	 * @param target Specifies type of texture (e.g. GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP_ARB, etc.)
	 * @param texID Handle to the texture to load
	 * @param name Name of the uniform sampler variable in the shader
	 */
	void loadTextureTU4(int target, int texID, string name);
	/**
	 * Set uniform variable name to the value specified by value. With this function you can set shader variables of type
	 * bool, int and samplerx (all types of samplers)
	 * @param name Name of uniform variable in the shader
	 * @param value Value to be set
	 */
	void loadUniform1i(string name, int value);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * bvec2 and ivec2
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type int[2])
	 */
	void loadUniform2i(string name, int value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * bvec3 and ivec3
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type int[3])
	 */
	void loadUniform3i(string name, int value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * bvec4 and ivec4
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type int[4])
	 */
	void loadUniform4i(string name, int value[]);
	/**
	 * Set uniform variable name to the value specified by value. With this function you can set shader variables of type
	 * float
	 * @param name Name of uniform variable in the shader
	 * @param value Value to be set
	 */
	void loadUniform1f(string name, float value);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * vec2
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type float[2])
	 */
	void loadUniform2f(string name, float value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * vec3
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type float[3])
	 */
	void loadUniform3f(string name, float value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * vec4 and mat2
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type float[4])
	 */
	void loadUniform4f(string name, float value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * mat3
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type float[9])
	 */
	void loadUniform9f(string name, float value[]);
	/**
	 * Set uniform variable name to the value specified by value[]. With this function you can set shader variables of type
	 * mat4
	 * @param name Name of uniform variable in the shader
	 * @param value[] Value to be set (array of type float[16])
	 */
	void loadUniform16f(string name, float value[]);
	/**
	 * Get location of attribute variable specified by name
	 * @param name Name of attribute variable in the shader
	 * @return Location of the attribute variable in the shader. You can use this location in the function glVertexAttrib
	 */
	int getAttributeLocation(string name);
	/**
	 * destructor
	 */
	~Shader();
};
//--------------------------------------------------
#endif
