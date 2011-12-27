/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef LIGHT_H
#define LIGHT_H
//--------------------------------------------------
/**
 * Saves all the information of a light. It can be turned on and off.
 */
class Light
{
private:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float direction[4];
	int lightNumber;

public:
	/**
	* true, if the light is active.
	*/
	bool active;
	/**
	* clear color of the framebuffer
	*/
	float clear[3];
	/**
	 * constructor
	 * @param pNumber OpenGL number of the light
	 */
	Light(int pNumber);
	/**
	 * destructor
	 */
	~Light();
	/**
	 * Set the ambient color of the light.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setAmbient(float r, float g, float b, float a);
	/**
	 * Set the diffuse color of the light.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setDiffuse(float r, float g, float b, float a);
	/**
	 * Set the specular color of the light.
	 * @param r red part
	 * @param g green part
	 * @param b blue part
	 * @param a alpha part
	 */
	void setSpecular(float r, float g, float b, float a);
	/**
	 * Set the position and type of the light.
	 * @param x x position
	 * @param y y position
	 * @param z z position
	 * @param w type (0=directional)
	 */
	void setPosition(float x, float y, float z, float w);
	/**
	 * Set the direction and type of the light.
	 * THIS FUNCTION IS NOT IN USE ATM!
	 * @param x x direction
	 * @param y y direction
	 * @param z z direction
	 * @param w type (0=directional)
	 */
	void setDirection(float x, float y, float z, float w);
	/**
	 * Returns the ambient color.
	 * @return color array
	 */
	float* getAmbient();
	/**
	 * Returns the diffuce color.
	 * @return color array
	 */
	float* getDiffuse();
	/**
	 * Returns the specular color.
	 * @return color array
	 */
	float* getSpecular();
	/**
	 * Returns the current position.
	 * @return position array
	 */
	float* getPosition();
	/**
	 * Returns the current direction.
	 * THIS FUNCTION IS NOT IN USE ATM!
	 * @return direction array
	 */
	float* getDirection();
	/**
	 * Executes all OpenGL calls to set the light colors and position.
	 */
	void call();
};
//--------------------------------------------------
#endif
