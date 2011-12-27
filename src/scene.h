/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#ifndef SCENE_H
#define SCENE_H
//--------------------------------------------------
#include "input.h"
#include "light.h"
#include "camera.h"
#include "objmodel.h"
#include "object.h"
#include "vmath.h"
#include "shader.h"
#include "skybox.h"
#include "terrain.h"
#include "particlesystem.h"
#include "text.h"
#include "water.h"
//--------------------------------------------------
/**
 *  The 3D scene is the main class which manage all objects and inputs of the Scene.
 */
class Scene
{
private:
	Shaderloader *shLoader;
	void draw(bool activateShaders);
	Input *input;
	Camera *camera;
	Light *sun;
	Object *mainObj;
	Texture *texturLoader;
	Shader *envShader;
	float cameraSpeed;
	Skybox* skybox;
	Terrain* terrain;
	Object* water;
	ObjModel* armor;
	float armorRotation;
	ParticleSystem* torch1;
	ParticleSystem* torch2;
	Text* helpText;
	GLuint envText;
	static const int CUBE_MAP_SIZE = 512;
	/**
	 * this method updates the cube map -> dynamic cube mapping
	 */
	void updateCubeMap();

	unsigned int shadowMap;
	Shader *shadowMapping;
	int shMapW;
	int shMapH;

	int shadowMode;
	void drawShadowVolumes();

	int countInsideVolume();
public:
	/**
	 * constructor
	 */
	Scene(Input *input);
	/**
	 * destructor
	 */
	~Scene();
	/**
	 * Render the Szene with all Objects
	 */
	void render();
	/**
	 * Render the Szene with Shadow Mapping
	 */
	void renderShadowMapping();
	/**
	 * Render the Szene with Shadow Volumes
	 */
	void renderShadowVolumes();
	/**
	 * Render the Szene without Shadow
	 */
	void renderNormal();
	/**
	 * Update the Scene
	 * @param timeDifference The timediffernece between two Frames
	 */
	void update(double timeDifference);
	/**
	 * Load all default scene Objects
	 * @param filename The filename of the objectgroup
	  * @param obj The main object, in which all subobjects are stored
	 */
	void loadObjects(string filename, Object *obj);
};
//--------------------------------------------------
#endif
