/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "object.h"
#include "global.h"
//--------------------------------------------------
Object::Object()
{
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	position.x = 0;
	position.y = 0;
	position.z = 0;
	renderStatic = false;
	lighting = true;
}
//--------------------------------------------------
Object::~Object()
{
	for (objectListIterator = objectList.begin();objectListIterator != objectList.end();objectListIterator++) //Search name in namelist
	{
		delete (*objectListIterator);
	}

	for (modelListIterator = modelList.begin();modelListIterator != modelList.end();modelListIterator++) //Search name in namelist
	{
		delete (*modelListIterator);
	}
}
//--------------------------------------------------
void Object::addObject(Object* o)
{
	objectList.push_back(o);
}
//--------------------------------------------------
void Object::addModel(ObjModel* m)
{
	modelList.push_back(m);
}
//--------------------------------------------------
Vector3f Object::getPosition()
{
	return position;
}
//--------------------------------------------------
Vector3f Object::getRotation()
{
	return rotation;
}
//--------------------------------------------------
void Object::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
//--------------------------------------------------
void Object::setPosition(Vector3f v)
{
	position = v;
}
//--------------------------------------------------
void Object::setRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}
//--------------------------------------------------
void Object::setRotation(Vector3f v)
{
	rotation = v;
}
//--------------------------------------------------
void Object::render(bool activateShaders)
{

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);


	for (objectListIterator = objectList.begin();objectListIterator != objectList.end();objectListIterator++) //Search name in namelist
	{
		(*objectListIterator)->render(activateShaders);
	}


	for (modelListIterator = modelList.begin();modelListIterator != modelList.end();modelListIterator++) //Search name in namelist
	{
		(*modelListIterator)->showF(activateShaders);
	}


	glPopMatrix();
}
//--------------------------------------------------
void Object::renderShadowVolumes(Light *sun)
{
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);

	for (objectListIterator = objectList.begin();objectListIterator != objectList.end();objectListIterator++) //Search name in namelist
	{
		(*objectListIterator)->renderShadowVolumes(sun);
	}

	for (modelListIterator = modelList.begin();modelListIterator != modelList.end();modelListIterator++) //Search name in namelist
	{
		(*modelListIterator)->renderShadowVolumes(sun, modelMatrix);
	}

	glPopMatrix();
}
//--------------------------------------------------
int Object::countInsideVolume(Camera *camera, Light *sun)
{
	int anz = 0;

	for (objectListIterator = objectList.begin();objectListIterator != objectList.end();objectListIterator++) //Search name in namelist
	{
		anz += (*objectListIterator)->countInsideVolume(camera, sun);
	}

	for (modelListIterator = modelList.begin();modelListIterator != modelList.end();modelListIterator++) //Search name in namelist
	{
		anz += (*modelListIterator)->countInsideVolume(camera, sun, modelMatrix);
	}

	return anz;
}
//--------------------------------------------------
void Object::saveModelMatrix()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);

	for (objectListIterator = objectList.begin();objectListIterator != objectList.end();objectListIterator++) //Search name in namelist
	{
		(*objectListIterator)->saveModelMatrix();
	}

	glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);

	glPopMatrix();
}
//--------------------------------------------------
