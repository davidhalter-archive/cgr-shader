/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "shaderloader.h"
#include "global.h"
#include <list>
//--------------------------------------------------
Shaderloader::Shaderloader()
{
}
//--------------------------------------------------
Shaderloader::~Shaderloader()
{
	for (nameListIterator = nameList.begin(); nameListIterator != nameList.end(); nameListIterator++) //Search name in namelist
	{
		Shadername shadername = *nameListIterator;  //Get current name
		delete shadername.shader;
	}
}
//--------------------------------------------------
Shader* Shaderloader::loadShader(string vert, string frag)
{
	Shader* ret = 0;

	bool newShader = true;

	for (nameListIterator = nameList.begin();nameListIterator != nameList.end();nameListIterator++) //Search name in namelist
	{
		Shadername shadername = *nameListIterator;  //Get current name

		if (!shadername.strFrag.compare(frag) && !shadername.strVert.compare(vert) )         //Compare the currant name with the list
		{
			ret = shadername.shader;                      //found the name in the list
			newShader = false;
			break;
		}
	}

	if (newShader)
	{
		Shadername *shadername = new Shadername();	//create new item
		ret = new Shader();
		ret->load(vert, frag);
		shadername->strFrag = frag;						//save the name in the new item
		shadername->strVert = vert;
		shadername->shader = ret;							//save the texturindex in the new itme

		nameList.push_back(*shadername);				//save the new item in the list
	}

	return ret;								//return the texurindex
}
//---------------------------------------------------------
