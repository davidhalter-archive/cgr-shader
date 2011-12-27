/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "water.h"
#include "global.h"
//--------------------------------------------------
Water::Water(Texture* tex)
{
	textureLoader = tex;
	waterTexture = textureLoader->loadTexture("water", true, false);
	displacementTexture = textureLoader->loadTexture("water", true, true);

	displacementShader = new Shader();
	displacementShader->load("./Daten/Shaders/Displacement_Mapping.vert", "./Daten/Shaders/Displacement_Mapping.frag");
}
//--------------------------------------------------
Water::~Water()
{
	delete displacementShader;
}
//--------------------------------------------------
void Water::render()
{
	displacementShader->enable();
	displacementShader->loadTextureTU0(GL_TEXTURE_2D, waterTexture, "base");
	displacementShader->loadTextureTU1(GL_TEXTURE_2D, displacementTexture, "displacementMap");

	int segments = 100;
	float xPos = -12000;
	float yPos = -12000;
	float segmentTexSize = 20.0f / segments;
	float height = -500;
	float segmentSize = 300;
	glBindTexture(GL_TEXTURE_2D, waterTexture);
	glBegin(GL_QUADS);

	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			glNormal3f(0.0, 1.0, 0.0);

			glTexCoord2f(segmentTexSize*j + segmentTexSize, segmentTexSize*i + segmentTexSize);
			glVertex3f(xPos + j*segmentSize + segmentSize, height, yPos + i*segmentSize + segmentSize);

			glTexCoord2f(segmentTexSize*j + segmentTexSize, segmentTexSize*i);
			glVertex3f(xPos + j*segmentSize + segmentSize, height, yPos + i*segmentSize);

			glTexCoord2f(segmentTexSize*j, segmentTexSize*i);
			glVertex3f(xPos + j*segmentSize, height, yPos + i*segmentSize);

			glTexCoord2f(segmentTexSize*j, segmentTexSize*i + segmentTexSize);
			glVertex3f(xPos + j*segmentSize, height, yPos + i*segmentSize + segmentSize);
		}
	}

	glEnd();

	displacementShader->disable();

}
//--------------------------------------------------
