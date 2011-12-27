/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "camera.h"
#include "global.h"
//--------------------------------------------------
Camera::Camera()
{
}
//--------------------------------------------------
Camera::~Camera()
{
}
//--------------------------------------------------
void Camera::move(float x, float y, float z)
{
	position.z += x * (float) sin(-rotation.y / 180 * 3.141) + z * (float) cos(-rotation.y / 180 * 3.141);
	position.x += z * (float) sin(rotation.y / 180 * 3.141) + x * (float) cos(rotation.y / 180 * 3.141);

	position.y += y;
}
//--------------------------------------------------
void Camera::rotate(float x, float y)
{
	rotation.x -= x;
	if (rotation.x > 90)rotation.x = 90;
	if (rotation.x < -90)rotation.x = -90;

	rotation.y -= y;
	if (rotation.y > 180)rotation.y -= 360;
	if (rotation.y < -180)rotation.y += 360;
}
//--------------------------------------------------
void Camera::call()
{
	glRotatef(-rotation.x, 1, 0, 0);
	glRotatef(-rotation.y, 0, 1, 0);

	glTranslatef(position.x, position.y, position.z);
}
//--------------------------------------------------
