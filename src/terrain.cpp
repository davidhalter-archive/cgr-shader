/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "terrain.h"
#include "global.h"
#include <time.h>
//--------------------------------------------------
Terrain::Terrain(Texture* tex)
{
	terrainModel = new ObjModel();
	terrainModel->load("mountain3", tex, NULL);
}
//--------------------------------------------------
Terrain::~Terrain()
{
	delete terrainModel;
}
//--------------------------------------------------
void Terrain::render(bool activateShaders)
{
	terrainModel->showS();
}
//--------------------------------------------------
