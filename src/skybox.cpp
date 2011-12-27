/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "skybox.h"
#include "global.h"
//--------------------------------------------------
Skybox::Skybox(Texture* tex)
{
	textureLoader = tex;
	lighting = true;
	dayTime = 0.1f;
	currentGlare = 0.0;

	skymodel = new ObjModel();
	skymodel->load("sky", textureLoader, NULL);

	weapon = new ObjModel();
	weapon->load("sword1", textureLoader, NULL);

	sunTexture = textureLoader->loadTexture("sun", true, false);
}
//--------------------------------------------------
Skybox::~Skybox()
{
	delete skymodel;
	delete weapon;
}
//--------------------------------------------------
void Skybox::render(bool activateShaders)
{
	Shader::disable();
	//configuration:
	float skySize = 30000.0f;
	float sunOrbit = 28000.0f;
	float orbitBias = 0.05f;
	float orbitRotation = 0.1f;
	int numberOfStars = 1000;

	//Rotate the sun ----------------------------------------
	Vector3f sunPosition = Vector3f(sunOrbit, 0.0f, 0.0f);

	Matrix3f m3 = Matrix3f::createRotationAroundAxis(0.0f, orbitRotation * 2.0f * (float)M_PI, 0.0f);
	Matrix3f m1 = Matrix3f::createRotationAroundAxis(0.0f, 0.0f, dayTime * 2.0f * (float)M_PI);
	Matrix3f m2 = Matrix3f::createRotationAroundAxis(orbitBias * 2.0f * (float)M_PI, 0.0f, 0.0f);

	sunPosition = m1 * sunPosition;
	sunPosition = m2 * sunPosition;
	sunPosition = m3 * sunPosition;

	//direction:
	sunDirection = sunPosition;
	sunDirection.normalize();

	//sky colors:
	Vector4f blue = Vector4f(0.2f, 0.4f, 0.8f, 1.0f);
	Vector4f white = Vector4f(0.52f, 0.63f, 0.87f, 1.0f);

	Vector4f orange = Vector4f(0.75f, 0.35f, 0.0f, 1.0f);
	Vector4f red = Vector4f(0.85f, 0.15f, 0.0f, 1.0f);

	Vector4f black = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

	//mix sky colors:
	Vector4f color1 = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4f color2 = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	float d = sunDirection.y;

	if (d >= 0.3f)
	{
		color1 = blue;
		color2 = white;
	}
	else
	{
		if (d >= 0.2f)
		{
			color1 = blue * (d - 0.2f) * 10.0f + orange * (1 - (d - 0.2f) * 10.0f);
			color2 = white * (d - 0.2f) * 10.0f + red * (1 - (d - 0.2f) * 10.0f);
		}
		else
		{
			color1 = orange * d * 5.0f + black * (1 - d * 5.0f);
			color2 = red * d * 5.0f  + black * (1 - d * 5.0f);
		}
	}

	//weapon (this is an easter egg)
	/*glPushMatrix();
	glLoadIdentity();
	glRotatef(20.0, 0, 0, 1);
	glRotatef(-20.0, 1, 0, 0);
	glTranslatef(20.0, 10.0, -50.0);
	weapon->showS();
	glPopMatrix();*/

	//draw everything ------------------------------------------
	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SMOOTH);

	resetTranslation();
	drawStars(numberOfStars);
	drawSky(skySize, color1, color2);
	drawSun(sunPosition);

	//restore matrix and attributes
	glPopAttrib();
	glPopMatrix();
	Shader::useDefaultShader();
}
//--------------------------------------------------
void Skybox::drawStars(int numberOfStars)
{
	//draws some stars (not very efficient)
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int oldRand = rand();
	srand(42);
	for (int i = 0;i < numberOfStars;i++)
	{
		int ang1 = (rand() % 360);
		int ang2 = (rand() % 360);
		int ang3 = (rand() % 360);
		glPushMatrix();
		glPointSize(rand() % 30 / 10.0f + 0.1f);
		glRotatef((float)ang1, 1.0, 0.0, 0.0);
		glRotatef((float)ang2, 0.0, 1.0, 0.0);
		glRotatef((float)ang3, 0.0, 0.0, 1.0);
		glTranslatef(31000.0, 0.0 , 0.0);

		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();
		glPopMatrix();
	}
	srand(oldRand);
}
//--------------------------------------------------
void Skybox::drawSky(float size, Vector4f color1, Vector4f color2)
{
	//draw the skydome
	float diff = 30.0f;
	float offset1 = diff * 0.5f;
	float offset2 = diff * 0.5f;

	Vector4f col = Vector4f(0.0, 0.0, 0.0, 0.0);

	for (float h = -0.5f;h < 1.0f;h += 0.1f)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0;i <= 360;i += diff)
		{
			col = color1 * (h + 0.1f) + color2 * (1.0f - (h + 0.1f));
			glColor4f(col.r, col.g, col.b, col.a);

			Vector3f p1 = Vector3f((float)cos(DEG2RAD(i)) * (1.0f - h - 0.1f), h + 0.1f, (float)sin(DEG2RAD(i)) * (1.0f - h - 0.1f));
			p1.normalize();
			glVertex3f(p1.x*size, p1.y*size, p1.z*size);

			col = color1 * h + color2 * (1.0f - h);
			glColor4f(col.r, col.g, col.b, col.a);
			Vector3f p2 = Vector3f((float)cos(DEG2RAD(i)) * (1.0f - h), h, (float)sin(DEG2RAD(i)) * (1.0f - h));
			p2.normalize();
			glVertex3f(p2.x*size, p2.y*size, p2.z*size);

		}
		glEnd();
	}
}
//--------------------------------------------------
void Skybox::drawSun(Vector3f sunPosition)
{
	float qSize = 1200.0;

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glPushMatrix();
	glTranslatef(sunPosition.x, sunPosition.y, sunPosition.z);
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	modelview[0] = 1;
	modelview[1] = 0;
	modelview[2] = 0;
	modelview[4] = 0;
	modelview[5] = 1;
	modelview[6] = 0;
	modelview[8] = 0;
	modelview[9] = 1;
	modelview[10] = 0;
	glLoadMatrixf(modelview);

	glBindTexture(GL_TEXTURE_2D, sunTexture);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(qSize, qSize, 0);
	glTexCoord2d(1, 0);
	glVertex3f(-qSize, qSize, 0);
	glTexCoord2d(1, 1);
	glVertex3f(-qSize, -qSize, 0);
	glTexCoord2d(0, 1);
	glVertex3f(qSize, -qSize, 0);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------
void Skybox::drawGlare()
{
	glPushMatrix();
	glLoadIdentity();
	glColor4f(1.0, 1.0, 8.0, currentGlare);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();
	glPopMatrix();
}
//--------------------------------------------------
void Skybox::resetTranslation()
{
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	modelview[12] = 0.0;
	modelview[13] = 0.0;
	modelview[14] = 0.0;
	glLoadMatrixf(modelview);
}
//--------------------------------------------------
Vector3f Skybox::getSunDirection()
{
	return sunDirection;
}
//--------------------------------------------------
void Skybox::update(double timeDifference)
{
	dayTime -= 0.000005f * (float)timeDifference;

	//wrap time:
	if (dayTime < 0.5)
	{
		dayTime += 0.5;
	}
	if (dayTime >= 1.0)
	{
		dayTime -= 1.0;
	}
}
//--------------------------------------------------
