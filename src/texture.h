/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H
//--------------------------------------------------
#include "global.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
//--------------------------------------------------
/**
 *  Texturename
 */
struct Texturename
{
	string str;
	int i;
};
//--------------------------------------------------
/**
 *  This class is a texture loader.
 */
class Texture
{
private:
	/**
	 * Load a bmp file into a texture and return its handler.
	 * @param name name of the texture file (without file ending)
	 */
	int loadFile(string name);
	//If the function can't find the bmp file, it will call loadPNGFile automatically to try to load a png file with the same name.
	/**
	 * Load a png file into a texture and return its handler.
	 * @param name name of the texture file (without file ending)
	 */
	int loadPNGFile(string Name, bool nearest);
	list <Texturename>::iterator nameListIterator;
	list <Texturename> nameList;

	int decodePNG(std::vector<unsigned char>& out_image_32bit, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, unsigned long in_size);
	int getPNGFile(std::vector<unsigned char>& buffer, const std::string& filename);

public:
	/**
	 * constructor
	 */
	Texture();
	/**
	 * destructor
	 */
	~Texture();

	/**
	 * Load a texture and save it in OpenGL
	 * @param Name filename of the texture without file ending
	 * @return the texture handler
	 */
	int loadTexture(string Name);
	/**
	 * Load a texture and save it in OpenGL
	 * @param Name filename of the texture without file ending
	 * @param png directly load a png (without trying to load the bmp with the same name first)
	 * @param nearest filter the texture with "nearest" option (used for displacement mapping)
	 * @return the texture handler
	 */
	int loadTexture(string Name, bool png, bool nearest);
};
//--------------------------------------------------
#endif
