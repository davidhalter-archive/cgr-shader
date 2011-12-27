/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef ObjModel_H
#define ObjModel_H
//--------------------------------------------------
#include "global.h"
#include "vmath.h"
#include "texture.h"
#include "shader.h"
#include "material.h"
#include "camera.h"
#include "light.h"
#include "shaderloader.h"
//--------------------------------------------------
/**
 *  Vertex
 */
struct V  //Vertices
{
	Vector3f pos;
	Vector3f normal;
};
//--------------------------------------------------
/**
 *  Face
 */
struct F  //Faces
{
	V *v1, *v2, *v3, *v4;
	Vector2f *vt1, *vt2, *vt3, *vt4;
	Vector3f normal;
};
//--------------------------------------------------
/**
 *  Sub-Object
 */
struct G  //Sub-Objects
{
	string label;
	F *faces;
	int anzf;
	string texname;
	string texname2;
	string texname3;
	int textur;
	int textur2;
	int textur3;

	Shader *shader;
	Material *material;

	G()
	{
		shader = NULL;
		material = NULL;

		textur = -1;
		textur2 = -1;
		textur3 = -1;
	}

	~G()
	{
		//if (shader != NULL) delete shader;      //its done by the Shaderloader
		if (material != NULL) delete material;
	}

};
//--------------------------------------------------
/**
 *  Represents a 3D object loaded from a wavefront file.
 */
class ObjModel
{
private:
	//Object-Data (Arrays):
	G *teilobj;
	V *points;
	Vector2f *texturpos;
	F *faces;

	//Counters:
	int anzg;
	int anzv;
	int anzvt;
	int anzf;

	float mix;

	GLuint list;

	Material *defaultMat;
	string name;

	void loadMaterial(G* subobj, string name, Texture* loader, Shaderloader *shLoader);
	void computeTangentAndBinormal(const Vector3<float>& v1, const Vector3<float>& v2, const Vector3<float>& v3,
	                               const Vector2<float>& c1, const Vector2<float>& c2, const Vector2<float>& c3,
	                               Vector3<float>& tangent, Vector3<float>& bitangent);
	void glVertexV(Vector3f V);

	//Displaylists:
	void createList();
	void callList();
	bool ceckFront(Vector3f v, Vector3f n, Vector3f p);

public:
	/**
	 * constructor
	 */
	ObjModel();
	/**
	 * destructor
	 */
	~ObjModel();
	/**
	 * Load the Object from the Model-File (.obj)
	 * @param filename Define the used File
	 * @param loader Define the Textureloader
	 * @param shLoader Define the Shaderloader
	 */
	void load(string filename, Texture* loader, Shaderloader *shLoader);
	/**
	 * Draw the model with smooth Normals
	  */
	void showS();
	/**
	 * Draw the model with flat Normals
	 * @param activateShaders Active Shaders defined in the Materialfile
	  */
	void showF(bool activateShaders);

	//Shadowvolumes:
	/**
	 * draw shadowvolumes of the object
	 * @param quelle The Light for rendering the Shadowvolumes
	  * @param modelMatrix The current modelMatrix
	 */
	void renderShadowVolumes(Light *quelle, Matrix4f modelMatrix);
	/**
	 * Counts the amount of Volumes where the camera is inside
	 * @param camera The camera of the scene
	  * @param quelle The Light which for the calculation
	   * @param modelMatrix The Light which for the calculation
	 * @return amount of Volumes where the camera is inside
	 */
	int countInsideVolume(Camera *camera, Light *quelle, Matrix4f modelMatrix);

};
//--------------------------------------------------
#endif
