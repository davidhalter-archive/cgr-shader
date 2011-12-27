/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "text.h"
#include "global.h"
//--------------------------------------------------
Text::Text(Texture* tex)
{
	int size = 256;
	textureLoader = tex;
	alphabetTexture = textureLoader->loadTexture("font", true, false);
	screenText = "Text";
}
//--------------------------------------------------
Text::~Text()
{
}
//--------------------------------------------------
void Text::render(bool activateShaders)
{
	float texX = 0;
	float texY = 0;
	float size = 1.0 / 16.0;
	int offset = 0;
	int line = 0;
	float letterHeight = 32;
	float letterWidth = 16;
	float i_offset = 0;

	begin2D();

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, alphabetTexture);
	glBegin(GL_QUADS);

	for (unsigned int i = 0;i < screenText.length();i++)
	{
		if (screenText.at(i) == '\n')
		{
			line++;
			i_offset = 0;
		}
		else
		{
			texX = (((int)screenText.at(i) + offset) % 16) * size;
			texY = (floor(((float)(screenText.at(i) + offset)) / 16.0f) * size);

			//4
			glTexCoord2d(texX + size, texY);
			glVertex2f(i_offset*letterWidth + letterWidth, letterHeight*line);

			//3
			glTexCoord2d(texX, texY);
			glVertex2f(i_offset*letterWidth, letterHeight*line);

			//2
			glTexCoord2d(texX, texY + size);
			glVertex2f(i_offset*letterWidth, letterHeight*line + letterHeight);

			//1
			glTexCoord2d(texX + size, texY + size);
			glVertex2f(i_offset*letterWidth + letterWidth, letterHeight*line + letterHeight);


			i_offset++;
		}
	}
	glEnd();
	end2D();


}
//--------------------------------------------------
void Text::setText(string t)
{
	screenText = t;
}
void Text::begin2D()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
void Text::end2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
//--------------------------------------------------
