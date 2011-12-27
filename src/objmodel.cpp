/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "objmodel.h"
#include "global.h"
#include "errorlog.h"
#include <sstream>
//--------------------------------------------------
ObjModel::ObjModel()
{
	teilobj = NULL;
	points = NULL;
	texturpos = NULL;
	faces = NULL;

	anzg = 0;
	anzv = 0;
	anzvt = 0;
	anzf = 0;

	mix = 1.0;

	defaultMat = new Material();
}
//--------------------------------------------------
ObjModel::~ObjModel()
{
	glDeleteLists(list, 1);

	if (teilobj != NULL) delete [] teilobj;
	if (points != NULL) delete [] points;
	if (texturpos != NULL) delete [] texturpos;
	if (faces != NULL) delete [] faces;

	delete defaultMat;
}
//--------------------------------------------------
void ObjModel::loadMaterial(G* subobj, string name, Texture* loader, Shaderloader *shLoader)
{
	if (subobj->material != NULL)
		delete subobj->material;
	subobj->material = new Material();

	string filename;
	int texIndex = 0;
	char shaderNameV[100];
	bool shaderNameVOk = false;
	char shaderNameF[100];
	bool shaderNameFOk = false;


	filename = "./Daten/Materials/";
	filename.append(name);
	filename.append(".txt");

	//Open File
	FILE *fp = fopen(filename.c_str(), "r");

	// set up stuff to write errors into error log file
	stringstream logStream;
	ErrorLog *log = ErrorLog::getInstance();

	if (!fp)
	{
		logStream << "Couldn't load the material: " << filename.c_str() << endl;
		log->reportError(logStream.str());
		subobj->texname = name;					//save the label of the material
		subobj->textur = loader->loadTexture(subobj->texname); //Load a texture with the same name of the material label
	}
	else
	{
		logStream.str("");
		logStream << "Load material: " << filename.c_str() << endl;
		log->reportError(logStream.str());

		int res = 0;
		while (res != EOF)
		{
			char typ[2] = "";
			typ[1] = '\0';

			res = fscanf(fp, "%c", &typ[0]);	//Read Line

			float values[6];

			switch (typ[0])
			{
			default:
				break;
			case 'a':
				res = fscanf(fp, "%f %f %f %f \n", &values[0], &values[1], &values[2], &values[3]); //Read the line
				subobj->material->setAmbient(values[0], values[1], values[2], values[3]);
				break;
			case 'd':
				res = fscanf(fp, "%f %f %f %f \n", &values[0], &values[1], &values[2], &values[3]); //Read the line
				subobj->material->setDiffuse(values[0], values[1], values[2], values[3]);
				break;
			case 's':
				res = fscanf(fp, "%f %f %f %f \n", &values[0], &values[1], &values[2], &values[3]); //Read the line
				subobj->material->setSpecular(values[0], values[1], values[2], values[3]);
				break;
			case 'e':
				res = fscanf(fp, "%f %f %f %f \n", &values[0], &values[1], &values[2], &values[3]); //Read the line
				subobj->material->setEmission(values[0], values[1], values[2], values[3]);
				break;
			case 'h':
				res = fscanf(fp, "%f \n", &values[0]); //Read the line
				subobj->material->setShininess(values[0]);
				break;
			case 't':
				char texName[100];									//buffer for the label
				res = fscanf(fp, " %[^\n]\n", texName);				//read the line

				switch (texIndex)
				{
				case 0:
					subobj->texname = texName;					//save the label of the material
					subobj->textur = loader->loadTexture(subobj->texname); //Load a texture with the same name of the material label
					break;

				case 1:
					subobj->texname2 = texName;					//save the label of the material
					subobj->textur2 = loader->loadTexture(subobj->texname2); //Load a texture with the same name of the material label
					break;

				case 2:
					subobj->texname3 = texName;					//save the label of the material
					subobj->textur3 = loader->loadTexture(subobj->texname3); //Load a texture with the same name of the material label
					break;
				}

				texIndex++;

				break;
			case 'v':
				res = fscanf(fp, " %[^\n]\n", shaderNameV);					//read the line
				shaderNameVOk = true;
				break;
			case 'f':
				res = fscanf(fp, " %[^\n]\n", shaderNameF);					//read the line
				shaderNameFOk = true;
				break;
			}
		}
	}

	if (shaderNameVOk && shaderNameFOk)
	{
		string shaderNameVPfad = "./Daten/Shaders/";
		shaderNameVPfad.append(shaderNameV);
		shaderNameVPfad.append(".vert");

		string shaderNameFPfad = "./Daten/Shaders/";
		shaderNameFPfad.append(shaderNameF);
		shaderNameFPfad.append(".frag");

		if (shLoader == NULL)
		{
			subobj->shader = new Shader();
			subobj->shader->load(shaderNameVPfad, shaderNameFPfad);
		}
		else
		{
			subobj->shader = shLoader->loadShader(shaderNameVPfad, shaderNameFPfad);
		}
	}
}
//--------------------------------------------------
void ObjModel::load(string filename, Texture* loader, Shaderloader *shLoader)
{
	name = filename;

	filename = "./Daten/Models/";
	filename.append(name);
	filename.append(".obj");

	//Open File
	FILE *fp = fopen(filename.c_str(), "r");

	// set up stuff to report error
	stringstream logStream;
	ErrorLog *log = ErrorLog::getInstance();

	if (!fp)
	{
		logStream << "Couldn't load the File: " << filename.c_str() << endl;
		log->reportError(logStream.str());
	}
	else
	{
		logStream.str("");
		logStream << "Load File: " << filename.c_str() << endl;
		log->reportError(logStream.str());

		//Count elements
		anzg = 0;
		anzv = 0;
		anzvt = 0;
		anzf = 0;

		int res = 0;
		while (res != EOF)
		{
			char typ[3] = "";
			typ[2] = '\0';

			res = fscanf(fp, "%c", &typ[0]);	//Read Line
			if (typ[0] != '\n')
			{
				res = fscanf(fp, "%c", &typ[1]);	//Read Line
			}
			else
			{
				typ[1] = '\n';
			}
			if (typ[1] != '\n')
				res = fscanf(fp, "%*[^\n]\n");	//Read Line

			switch (typ[0])
			{
			default:
				break;
			case 's':
				break;
			case '#':
				break;
			case 'g':
				anzg++;
				break;
			case 'f':
				anzf++;
				break;
			case 'u':
				break;
			case 'v':
				if (typ[1] == 't') anzvt++;
				else anzv++;
				break;
			}

		}

		//Build arrays for all elements
		teilobj = new G[anzg];
		points = new V[anzv];
		texturpos = new Vector2f[anzvt];
		faces = new F[anzf];


		//Reset counters
		int countg = 0;
		int countv = 0;
		int countvt = 0;
		int countf = 0;
		int countfteilobj = 0;

		//Reset file
		rewind(fp);
		res = 0;

		//Read Data
		while (res != EOF)
		{
			char typ[3] = "";
			typ[2] = '\0';
			res = fscanf(fp, "%c", &typ[0]);	//Read Line
			if (typ[0] != '\n')
			{
				res = fscanf(fp, "%c", &typ[1]);	//Read Line
			}
			else
			{
				typ[0] = '\0'; //if there is only a newline
			}


			switch (typ[0])
			{
			default:
				res = fscanf(fp, "%*[^\n]\n");
				break;		//ignore Line if not v, vt, g, us or f
			case '\0':											//case new subobject
			{
				//only newline
			}
			break;
			case 'g':											//case new subobject
			{
				if (countg > 0)										//save the face counter of the last subobj
				{													//bevor loading the next subobject
					teilobj[countg-1].anzf = countfteilobj;
					countfteilobj = 0;
				}

				char bez[100];
				res = fscanf(fp, "%[^\n]\n", bez);					//read label
				teilobj[countg].label = bez;						//save label
				teilobj[countg].faces = &faces[countf];
				countg++;											//increment counter
			}
			break;
			case 'f':											//case new face
			{
				int p[] = {0, 0, 0, 0}, tex[] = {0, 0, 0, 0};			//create variables to store the datas temorary
				res = fscanf(fp, "%i/%i %i/%i %i/%i %i/%i \n", &p[0], &tex[0], &p[1], &tex[1], &p[2], &tex[2], &p[3], &tex[3]); //Read the line
				faces[countf].v1 = &points[p[0] - 1];				//Save datas in the current face
				faces[countf].v2 = &points[p[1] - 1];
				faces[countf].v3 = &points[p[2] - 1];
				if (p[3] > 0)faces[countf].v4 = &points[p[3] - 1];	//Only used for quads (not for triangles)
				else faces[countf].v4 = 0;
				faces[countf].vt1 = &texturpos[tex[0] - 1];		//Save the texturcoordinates for the current face
				faces[countf].vt2 = &texturpos[tex[1] - 1];
				faces[countf].vt3 = &texturpos[tex[2] - 1];
				if (tex[3] > 0)faces[countf].vt4 = &texturpos[tex[3] - 1]; //Only used for quads (not for triangles)
				else faces[countf].vt4 = 0;
				countf++;											//increment the face counter
				countfteilobj++;									//increment the face counter of the subobject
			}
			break;
			case 'u':											//case new material
			{
				if (typ[1] == 's')
				{
					char bez[100];									//buffer for the label
					res = fscanf(fp, "emtl %[^\n]\n", bez);				//read the line

					loadMaterial(&teilobj[countg-1], bez, loader, shLoader);

				}
				else
				{
					res = fscanf(fp, "%*[^\n]\n");				//read the line
				}
			}
			break;
			case 'v':											//case new vertex or texturcoordinate
			{
				if (typ[1] == 't')									//if there is a new texturcoordinate
				{
					float w[3];										//create variables to store the datas temorary
					res = fscanf(fp, "%f %f %f \n", &w[0],  &w[1],  &w[2]);		//read the line
					texturpos[countvt].x = w[0];						//save the x coordinate of the vertex
					texturpos[countvt].y = w[1];						//save the y coordinate of the vertex
					//texturpos[countvt].z=w[2];
					countvt++;
				}
				else												//if there is a new vertex
				{
					float w[3];										//create variables to store the datas temorary
					res = fscanf(fp, "%f %f %f \n", &w[0],  &w[1],  &w[2]);		//read the line
					//points[countv].pos.x = -w[0];				//save the coordinates of a vertes (use "-" to reflect the object,
					//or divide the coordinate by a scalar to scale the model)
					points[countv].pos.x = w[0];
					points[countv].pos.y = w[1];
					points[countv].pos.z = w[2];
					countv++;
				}

			}
			break;
			}
		}

		if (countg > 0)										//save the face counter of the last subobj
		{
			teilobj[countg-1].anzf = countfteilobj;
			countfteilobj = 0;
		}

		//Test for vertexes at same coordinates
		for (int i = 0;i < anzv;i++)
			for (int j = 0;j < anzv;j++)
			{
				if (points[i].pos.x == points[j].pos.x &&  //compare the vector
				        points[i].pos.y == points[j].pos.y &&
				        points[i].pos.z == points[j].pos.z &&
				        i != j)
				{
					//if there is a second vector with same coordinates, remove them
					for (int k = 0;k < anzf;k++) //search all faces where the vertex is used, and replace the old vertex
					{
						if (faces[k].v1 == &points[j])
						{
							faces[k].v1 = &points[i];
						}

						if (faces[k].v2 == &points[j])
						{
							faces[k].v2 = &points[i];
						}

						if (faces[k].v3 == &points[j])
						{
							faces[k].v3 = &points[i];
						}

						if (faces[k].v4 == &points[j])
						{
							faces[k].v4 = &points[i];
						}
					}

					//reset the old vertex
					points[j].pos.x = 0;
					points[j].pos.y = 0;
					points[j].pos.z = 0;

				}
			}

		//Calculate the normals
		for (int i = 0;i < anzf;i++)
		{
			//Calculate the normal of the face
			Vector3f normal;
			//normal=faces[i].v1->pos.normalenvektor(faces[i].v3->pos, faces[i].v2->pos, false);

			normal = (faces[i].v2->pos - faces[i].v1->pos).crossProduct(faces[i].v3->pos - faces[i].v1->pos);

			normal.normalize();

			normal = normal * -1;
			faces[i].normal.x = normal.x;
			faces[i].normal.y = normal.y;
			faces[i].normal.z = normal.z;

			//Add the normal to all vertices for smooth mode
			faces[i].v1->normal = faces[i].normal + normal;
			faces[i].v2->normal = faces[i].normal + normal;
			faces[i].v3->normal = faces[i].normal + normal;


			//Only used for quads
			if (faces[i].v4 != 0)faces[i].v4->normal = faces[i].v4->normal + normal;
		}

	}

	//createList();
}
//--------------------------------------------------
void ObjModel::showS()
{
	float normalLen = 100.0;
	//Draw the Object in smooth mode

	//Draw all trinagles
	for (int i = 0;i < anzg;i++)
	{
		glBindTexture(GL_TEXTURE_2D, teilobj[i].textur);
		glBegin(GL_TRIANGLES);

		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			if (teilobj[i].faces[j].v4 == 0)
			{
				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v2->normal.x, teilobj[i].faces[j].v2->normal.y, teilobj[i].faces[j].v2->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt2->x, teilobj[i].faces[j].vt2->y);
				glVertex3f(teilobj[i].faces[j].v2->pos.x, teilobj[i].faces[j].v2->pos.y, teilobj[i].faces[j].v2->pos.z);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v1->normal.x, teilobj[i].faces[j].v1->normal.y, teilobj[i].faces[j].v1->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt1->x, teilobj[i].faces[j].vt1->y);
				glVertex3f(teilobj[i].faces[j].v1->pos.x, teilobj[i].faces[j].v1->pos.y, teilobj[i].faces[j].v1->pos.z);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v3->normal.x, teilobj[i].faces[j].v3->normal.y, teilobj[i].faces[j].v3->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt3->x, teilobj[i].faces[j].vt3->y);
				glVertex3f(teilobj[i].faces[j].v3->pos.x, teilobj[i].faces[j].v3->pos.y, teilobj[i].faces[j].v3->pos.z);
			}
		}
		glEnd();
	}

	//Draw all quads
	for (int i = 0;i < anzg;i++)
	{
		glBindTexture(GL_TEXTURE_2D, teilobj[i].textur);
		glBegin(GL_QUADS);
		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			if (teilobj[i].faces[j].v4 != 0)
			{
				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v4->normal.x, teilobj[i].faces[j].v4->normal.y, teilobj[i].faces[j].v4->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt4->x, teilobj[i].faces[j].vt4->y);
				glVertex3f(teilobj[i].faces[j].v4->pos.x, teilobj[i].faces[j].v4->pos.y, teilobj[i].faces[j].v4->pos.z);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v3->normal.x, teilobj[i].faces[j].v3->normal.y, teilobj[i].faces[j].v3->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt3->x, teilobj[i].faces[j].vt3->y);
				glVertex3f(teilobj[i].faces[j].v3->pos.x, teilobj[i].faces[j].v3->pos.y, teilobj[i].faces[j].v3->pos.z);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v2->normal.x, teilobj[i].faces[j].v2->normal.y, teilobj[i].faces[j].v2->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt2->x, teilobj[i].faces[j].vt2->y);
				glVertex3f(teilobj[i].faces[j].v2->pos.x, teilobj[i].faces[j].v2->pos.y, teilobj[i].faces[j].v2->pos.z);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				glNormal3f(teilobj[i].faces[j].v1->normal.x, teilobj[i].faces[j].v1->normal.y, teilobj[i].faces[j].v1->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt1->x, teilobj[i].faces[j].vt1->y);
				glVertex3f(teilobj[i].faces[j].v1->pos.x, teilobj[i].faces[j].v1->pos.y, teilobj[i].faces[j].v1->pos.z);
			}
		}
		glEnd();
	}
}
//--------------------------------------------------
void ObjModel::showF(bool activateShaders)
{
	mix -= 0.005f;
	if (mix < 0.0f)
	{
		mix = 1.0f;
	}

	//Draw the Object in flat mode

	//Draw all triangles
	for (int i = 0;i < anzg;i++)
	{
		if (teilobj[i].material != NULL)teilobj[i].material->call();
		else defaultMat->call();

		int tangentLoc = 0, bitangentLoc = 0;
		if (activateShaders)
		{
			if (teilobj[i].shader != NULL)
				teilobj[i].shader->enable();
			else Shader::useDefaultShader();

			if (teilobj[i].shader != NULL && teilobj[i].textur != -1)teilobj[i].shader->loadTextureTU0(GL_TEXTURE_2D, teilobj[i].textur, "base");
			// for students -> if you didn't implement parallax mapping, comment this line
			if (teilobj[i].shader != NULL && teilobj[i].textur2 != -1)teilobj[i].shader->loadTextureTU1(GL_TEXTURE_2D, teilobj[i].textur2, "heightMap");
			// end for students
			if (teilobj[i].shader != NULL && teilobj[i].textur3 != -1)teilobj[i].shader->loadTextureTU2(GL_TEXTURE_2D, teilobj[i].textur3, "normalMap");
			if (teilobj[i].shader != NULL)tangentLoc = teilobj[i].shader->getAttributeLocation("tangent");
			if (teilobj[i].shader != NULL)bitangentLoc = teilobj[i].shader->getAttributeLocation("bitangent");
			glActiveTexture(GL_TEXTURE0);       // activate TU0 again
		}

		glBindTexture(GL_TEXTURE_2D, teilobj[i].textur);

		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			if (teilobj[i].faces[j].v4 == 0)
			{
				Vector3<float> normalVec(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				if (activateShaders)
				{
					Vector3<float> tangent;
					Vector3<float> bitangent;

					computeTangentAndBinormal(teilobj[i].faces[j].v1->pos, teilobj[i].faces[j].v2->pos, teilobj[i].faces[j].v3->pos,
					                          *teilobj[i].faces[j].vt1, *teilobj[i].faces[j].vt2, *teilobj[i].faces[j].vt3, tangent, bitangent);

					//use gram-schmidt
					tangent = tangent - normalVec * tangent.dotProduct(normalVec);
					tangent.normalize();
					bitangent = bitangent - normalVec * bitangent.dotProduct(normalVec);
					bitangent.normalize();

					glVertexAttrib3fARB(tangentLoc, tangent[0], tangent[1], tangent[2]);
					glVertexAttrib3fARB(bitangentLoc, bitangent[0], bitangent[1], bitangent[2]);
					// end gram-schmidt
				}
				glNormal3f(normalVec.x, normalVec.y, normalVec.z);

				glBegin(GL_TRIANGLES);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v1->normal.x, teilobj[i].faces[j].v1->normal.y, teilobj[i].faces[j].v1->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt1->x, teilobj[i].faces[j].vt1->y);
				glVertexV(teilobj[i].faces[j].v1->pos);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v3->normal.x, teilobj[i].faces[j].v3->normal.y, teilobj[i].faces[j].v3->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt3->x, teilobj[i].faces[j].vt3->y);
				glVertexV(teilobj[i].faces[j].v3->pos);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v2->normal.x, teilobj[i].faces[j].v2->normal.y, teilobj[i].faces[j].v2->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt2->x, teilobj[i].faces[j].vt2->y);
				glVertexV(teilobj[i].faces[j].v2->pos);

				glEnd();

			}
		}

		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			if (teilobj[i].faces[j].v4 != 0)
			{
				Vector3<float> normalVec(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				if (activateShaders)
				{
					Vector3<float> tangent;
					Vector3<float> bitangent;

					computeTangentAndBinormal(teilobj[i].faces[j].v1->pos, teilobj[i].faces[j].v2->pos, teilobj[i].faces[j].v3->pos,
					                          *teilobj[i].faces[j].vt1, *teilobj[i].faces[j].vt2, *teilobj[i].faces[j].vt3, tangent, bitangent);

					//use gram-schmidt
					tangent = tangent - normalVec * tangent.dotProduct(normalVec);
					tangent.normalize();
					bitangent = bitangent - normalVec * bitangent.dotProduct(normalVec);
					bitangent.normalize();

					glVertexAttrib3fARB(tangentLoc, tangent[0], tangent[1], tangent[2]);
					glVertexAttrib3fARB(bitangentLoc, bitangent[0], bitangent[1], bitangent[2]);
					// end gram-schmidt
				}
				glNormal3f(normalVec.x, normalVec.y, normalVec.z);

				glBegin(GL_QUADS);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v4->normal.x, teilobj[i].faces[j].v4->normal.y, teilobj[i].faces[j].v4->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt4->x, teilobj[i].faces[j].vt4->y);
				glVertexV(teilobj[i].faces[j].v4->pos);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v3->normal.x, teilobj[i].faces[j].v3->normal.y, teilobj[i].faces[j].v3->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt3->x, teilobj[i].faces[j].vt3->y);
				glVertexV(teilobj[i].faces[j].v3->pos);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v2->normal.x, teilobj[i].faces[j].v2->normal.y, teilobj[i].faces[j].v2->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt2->x, teilobj[i].faces[j].vt2->y);
				glVertexV(teilobj[i].faces[j].v2->pos);

				//glNormal3f(teilobj[i].faces[j].normal.x, teilobj[i].faces[j].normal.y, teilobj[i].faces[j].normal.z);
				//glNormal3f(teilobj[i].faces[j].v1->normal.x, teilobj[i].faces[j].v1->normal.y, teilobj[i].faces[j].v1->normal.z);
				glTexCoord2d(teilobj[i].faces[j].vt1->x, teilobj[i].faces[j].vt1->y);
				glVertexV(teilobj[i].faces[j].v1->pos);

				glEnd();
			}
		}
	}
	Shader::useDefaultShader();
}
//--------------------------------------------------
void ObjModel::createList()
{
	list = glGenLists(1);

	glNewList(list, GL_COMPILE);
	showS();
	glEndList();
}
//--------------------------------------------------
void ObjModel::callList()
{
	glCallList(list);
}
//---------------------------------------------------------------------------
void ObjModel::computeTangentAndBinormal(const Vector3<float>& v1, const Vector3<float>& v2, const Vector3<float>& v3,
        const Vector2<float>& c1, const Vector2<float>& c2, const Vector2<float>& c3,
        Vector3<float>& tangent, Vector3<float>& bitangent)
{
	// first compute vectors between v1, v2; v1, v3
	Vector3<float> v2v1 = v2 - v1;
	Vector3<float> v3v1 = v3 - v1;

	// now compute vectors between c1, c2; c1, c3
	Vector2<float> c2c1 = c2 - c1;
	Vector2<float> c3c1 = c3 - c1;

	// compute determinant
	float det = c2c1.x * c3c1.y - c3c1.x * c2c1.y;

	// this is just to make sure we don't divide by zero
	if (det != 0.0)
	{
		tangent = (v2v1 * c3c1.y - v3v1 * c2c1.y) * (1 / det);
		bitangent = (v2v1 * (-c3c1.x) + v3v1 * c2c1.x) * (1 / det);

		// normalize the vectors
		tangent.normalize();
		bitangent.normalize();

		// use Gram - Schmidt to make tangent and bitangent orthogonal
		tangent = tangent - bitangent * tangent.dotProduct(bitangent);

		// renormalize tangent
		tangent.normalize();

	}
	else
	{
		//if determinant is 0 do nothing
	}
}
//--------------------------------------------------
void ObjModel::renderShadowVolumes(Light *quelle, Matrix4f modelMatrix)
{
	Vector3f richtung;
	Vector3f ursprung;

	richtung.x = quelle->getPosition()[0];
	richtung.y = quelle->getPosition()[1];
	richtung.z = quelle->getPosition()[2];

	ursprung.x = 0;
	ursprung.y = 0;
	ursprung.z = 0;

	ursprung = modelMatrix.inverse() * ursprung;
	richtung = modelMatrix.inverse() * richtung;

	richtung -= ursprung;

	richtung *= -1;
	richtung.normalize();
	richtung = richtung * 5000;

	glBegin(GL_QUADS);
	for (int i = 0;i < anzg;i++)
	{
		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			Vector3f a = richtung;
			Vector3f b = teilobj[i].faces[j].normal;

			a.normalize();
			b.normalize();

			float w = a.dotProduct(b);
			w = acos(w) / M_PI * 180.0f;

			if (w > 90 || w < -90)
				if (teilobj[i].faces[j].v4 == 0)
				{
					Vector3f v1 = teilobj[i].faces[j].v1->pos;
					Vector3f v2 = teilobj[i].faces[j].v2->pos;
					Vector3f v3 = teilobj[i].faces[j].v3->pos;

					glColor4f(1, 0, 0, 0.5);
					glVertex3fv(v1);
					glVertex3fv(v2);
					glVertex3fv(v2 + richtung);
					glVertex3fv(v1 + richtung);

					glColor4f(0, 1, 0, 0.5);
					glVertex3fv(v2);
					glVertex3fv(v3);
					glVertex3fv(v3 + richtung);
					glVertex3fv(v2 + richtung);

					glColor4f(0, 0, 1, 0.5);
					glVertex3fv(v3);
					glVertex3fv(v1);
					glVertex3fv(v1 + richtung);
					glVertex3fv(v3 + richtung);
				}
				else
				{
					Vector3f v1 = teilobj[i].faces[j].v1->pos;
					Vector3f v2 = teilobj[i].faces[j].v2->pos;
					Vector3f v3 = teilobj[i].faces[j].v3->pos;
					Vector3f v4 = teilobj[i].faces[j].v4->pos;

					glColor4f(1, 0, 0, 0.5);

					glVertex3fv(v4 + richtung);
					glVertex3fv(v3 + richtung);
					glVertex3fv(v3);
					glVertex3fv(v4);

					glColor4f(0, 1, 0, 0.5);


					glVertex3fv(v4);
					glVertex3fv(v1);
					glVertex3fv(v1 + richtung);
					glVertex3fv(v4 + richtung);

					glColor4f(0, 0, 1, 0.5);

					glVertex3fv(v2 + richtung);
					glVertex3fv(v1 + richtung);
					glVertex3fv(v1);
					glVertex3fv(v2);

					glColor4f(1, 1, 0, 0.5);

					glVertex3fv(v2);
					glVertex3fv(v3);
					glVertex3fv(v3 + richtung);
					glVertex3fv(v2 + richtung);
				}

		}
	}
	glEnd();
}
//--------------------------------------------------
bool ObjModel::ceckFront(Vector3f v, Vector3f n, Vector3f p)
{
	n.normalize();
	float d = v.dotProduct(n) - p.dotProduct(n);
	if (d > 0)return true;
	else return false;
}
//--------------------------------------------------
int ObjModel::countInsideVolume(Camera *camera, Light *quelle, Matrix4f modelMatrix)
{
	int anz = 0;
	Vector3f richtung;
	Vector3f ursprung;
	Vector3f campos;
	campos.x = camera->getPosition()[0] - 10;
	campos.y = camera->getPosition()[1];
	campos.z = camera->getPosition()[2];
	campos *= -1;

	richtung.x = quelle->getPosition()[0];
	richtung.y = quelle->getPosition()[1];
	richtung.z = quelle->getPosition()[2];

	ursprung.x = 0;
	ursprung.y = 0;
	ursprung.z = 0;

	ursprung = modelMatrix.inverse() * ursprung;
	richtung = modelMatrix.inverse() * richtung;
	campos = modelMatrix.inverse() * campos;
	richtung -= ursprung;

	richtung *= -1;
	richtung.normalize();
	richtung = richtung * 5000;

	for (int i = 0;i	< anzg;i++)
	{
		for (int j = 0;j < teilobj[i].anzf;j++)
		{
			Vector3f a = richtung;
			Vector3f b = teilobj[i].faces[j].normal;

			a.normalize();
			b.normalize();

			float w = a.dotProduct(b);
			w = acos(w) / M_PI * 180.0f;

			Vector3f v1 = teilobj[i].faces[j].v1->pos;
			Vector3f v2 = teilobj[i].faces[j].v2->pos;
			Vector3f v3 = teilobj[i].faces[j].v3->pos;


			bool front = ceckFront(campos, b * -1, v1);

			if (w > 90 || w < -90)
				if (teilobj[i].faces[j].v4 == 0)
				{

					Vector3f n;
					bool a, b, c;

					n = richtung.crossProduct(v2 - v1);
					a = ceckFront(campos, n, v1);

					n = richtung.crossProduct(v3 - v2);
					b = ceckFront(campos, n, v2);

					n = richtung.crossProduct(v1 - v3);
					c = ceckFront(campos, n, v3);

					if (a && b && c && front)
						anz++;

				}
				else
				{
					Vector3f v4 = teilobj[i].faces[j].v4->pos;

					Vector3f n;
					bool a, b, c, d;

					n = richtung.crossProduct(v2 - v1);
					a = ceckFront(campos, n, v1);

					n = richtung.crossProduct(v3 - v2);
					b = ceckFront(campos, n, v2);

					n = richtung.crossProduct(v4 - v3);
					c = ceckFront(campos, n, v3);

					n = richtung.crossProduct(v1 - v4);
					d = ceckFront(campos, n, v4);

					if (a && b && c && d && front)
						anz++;

				}

		}
	}


	return anz;
}
//--------------------------------------------------
void ObjModel::glVertexV(Vector3f V)
{
	glVertex3f(V.x, V.y, V.z);
}
//--------------------------------------------------
