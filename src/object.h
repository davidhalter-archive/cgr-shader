/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef OBJECT_H
#define OBJECT_H
//--------------------------------------------------
#include "objmodel.h"
#include <list>
#include "vmath.h"
//--------------------------------------------------
/**
 *  Represents an object countaining sub objects and models. rotation and position is also defined.
 */
class Object
{
private:
	Vector3f position;
	Vector3f rotation;
	list <ObjModel*>::iterator modelListIterator;
	list <ObjModel*> modelList;
	list <Object*>::iterator objectListIterator;
	list <Object*> objectList;
	Matrix4f modelMatrix;

	bool renderStatic;
	bool lighting;

public:
	/**
	 * constructor
	 */
	Object();
	/**
	 * destructor
	 */
	virtual ~Object();
	/**
	 * Adds a objekt to the objectlist
	 */
	void addObject(Object* o);
	/**
	 * Adds a model to the objectlist
	 */
	void addModel(ObjModel* m);
	/**
	 * draw all models and all subobject
	 * @param activateShaders Activate shaders
	 */
	virtual void render(bool activateShaders);
	/**
	 * Set the rotation of the object
	 * @param x Set the rotation around the x axis
	 * @param y Set the rotation around the y axis
	 * @param z Set the rotation around the z axis
	 */
	void setRotation(float x, float y, float z);
	/**
	 * Set the rotation of the object
	 * @param v Set the rotation around all axis
	 */
	void setRotation(Vector3f v);
	/**
	 * Returns the current object rotation
	 * @return current object rotation
	 */
	Vector3f getRotation();
	/**
	 * Set the position of the object
	 * @param x Set the x-position
	 * @param y Set the y-position
	 * @param z Set the z-position
	 */
	void setPosition(float x, float y, float z);
	/**
	 * Set the position of the object
	 * @param v Set the position
	 */
	void setPosition(Vector3f v);
	/**
	 * Returns the object position
	 * @return the object position
	 */
	Vector3f getPosition();
	/**
	 * draw shadowvolumes of the object
	 * @param sun The Light for rendering the Shadowvolumes
	 */
	void renderShadowVolumes(Light *sun);
	/**
	 * save the ModelMatrix
	 */
	void saveModelMatrix();
	/**
	 * Counts the amount of Volumes where the camera is inside
	 * @param camera The camera of the scene
	  * @param sun The Light which for the calculation
	 * @return amount of Volumes where the camera is inside
	 */
	int countInsideVolume(Camera *camera, Light *sun);
};
//--------------------------------------------------
#endif
