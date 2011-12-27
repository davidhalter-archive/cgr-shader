/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef CAMERA_H
#define CAMERA_H
//--------------------------------------------------
#include "global.h"
#include "vmath.h"
//--------------------------------------------------
/**
 *  Represents the camera and saves its position as well as rotation.
 */
class Camera
{
private:
	Vector2f rotation;
	Vector3f position;

public:
	/**
	 * Moves the camera to a position relative to the current position
	 * @param x New x position
	 * @param y New y position
	 * @param z New z position
	 */
	void move(float x, float y, float z);
	/**
	 * Rotates the camera only around x and y axis.
	 * @param x New x rotation
	 * @param y New y rotation
	 */
	void rotate(float x, float y);
	/**
	 * Get the current camera position as Vector3f
	 * @return current camera position
	 */
	Vector3f getPosition()
	{
		return position;
	}
	/**
	 * Get the current camera rotation as Vector2f
	 * @return current camera rotation
	 */
	Vector2f getRotation()
	{
		return rotation;
	}
	/**
	 * constructor
	 */
	Camera();
	/**
	 * destructor
	 */
	~Camera();
	/**
	 * Executes all rotations and translations before
	 * rendering the scene.
	 */
	void call();
};
//--------------------------------------------------
#endif
