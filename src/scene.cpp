/**************************************************/
/*  Authors:                Benjamin Bachmann     */
/*                          Marco Koster          */
/*                          Richard Steiner       */
/*                                                */
/*  Date:                   14.05.2009            */
/**************************************************/
#include "global.h"
#include "scene.h"
#include "vmath.h"
#include "errorlog.h"
#include <sstream>
//#include "main.h"           // so we have width and height of screen
///--------------------------------------------------
// this stuff sets up some necessary data structures for environment mapping

// targets for the cube map
GLuint cubeMapDefines[6] =
{
	GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
};

//--------------------------------------------------
Scene::Scene(Input *input)
{
	camera = new Camera();
	cameraSpeed = 0.3f;
	this->input = input;

	sun = new Light(GL_LIGHT0);

	//SetupOpenGL

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	glDisable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	texturLoader = new Texture();
	shLoader = new Shaderloader();

	mainObj = new Object();
	loadObjects("default", mainObj);

	terrain = new Terrain(texturLoader);
	skybox = new Skybox(texturLoader);
	water = new Object();
	ObjModel* watermod = new ObjModel();
	watermod->load("water", texturLoader, shLoader);
	water->addModel(watermod);

	armor = new ObjModel();
	armor->load("ruestung_old", texturLoader, shLoader);
	armorRotation = 0.0;

	torch1 = new ParticleSystem(texturLoader, Vector3f(15.0 - 300, 202.0, 26.0 + 700));
	torch2 = new ParticleSystem(texturLoader, Vector3f(287.0 - 300, 202.0, 26.0 + 700));

	helpText = new Text(texturLoader);

	//Save ModelMatrix
	glLoadIdentity();
	mainObj->saveModelMatrix();


	camera->move(200, -170, -500);

	// for students: uncomment this if you implemented environment mapping
	/*envShader = new Shader();
	envShader->load("./Daten/Shaders/Env_Mapping.vert", "./Daten/Shaders/Env_Mapping.frag");*/
	// end for students

	// set up our dynamic cubemap
	// uncomment this if you implemented environment mapping
	/*glEnable(GL_TEXTURE_CUBE_MAP_ARB);
	glGenTextures(1, &envText);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, envText);*/
	// end

	// set up some parameters
	// uncomment this if you implemented environment mapping
	/*glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);*/
	//end

	// set up min and max filters
	// uncomment this if you implemented environment mapping
	/*glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(cubeMapDefines[i], 0, GL_RGBA, CUBE_MAP_SIZE, CUBE_MAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}

	glDisable(GL_TEXTURE_CUBE_MAP_ARB);*/

	shadowMode = 0;

	//create shadowmap-texture

	shMapW = width;
	shMapH = height;

	shadowMap = 0;
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32_ARB, shMapW, shMapH, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	shadowMapping = new Shader();
	shadowMapping->load("./Daten/Shaders/Shadow_Mapping.vert", "./Daten/Shaders/Shadow_Mapping.frag");
}
//--------------------------------------------------
Scene::~Scene()
{
	delete texturLoader;
	delete shLoader;
	delete camera;
	delete mainObj;
	delete sun;
	delete skybox;
	delete terrain;
	delete water;
	delete armor;
	delete helpText;
	delete envShader;
	delete shadowMapping;

	glDeleteTextures(1, &envText);
	glDeleteTextures(1, &shadowMap);
}
//--------------------------------------------------
void Scene::renderShadowMapping()
{
	sun->setPosition(sun->getPosition()[0]*7000, sun->getPosition()[1]*7000, sun->getPosition()[2]*7000, 1); //Don't remove!!

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// Clear the screen and the depth buffer
	glLoadIdentity();

	camera->call();
	draw(true);	

	Shader::disable();

	//show shadowmap
	if (shadowMode == 3)
	{
		glLoadIdentity();
		glPushAttrib(GL_ENABLE_BIT);
		glColor3f(1, 1, 1);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, -10);
		glTexCoord2f(1, 0);
		glVertex3f(4, 0, -10);
		glTexCoord2f(1, 1);
		glVertex3f(4, 3, -10);
		glTexCoord2f(0, 1);
		glVertex3f(0, 3, -10);
		glEnd();
		glPopAttrib();
	}

	SDL_GL_SwapBuffers();
}
//--------------------------------------------------
void Scene::renderShadowVolumes()
{
	//Shadowvolumes
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// Clear the screen and the depth buffer

	int i = countInsideVolume();

	glEnable(GL_STENCIL_TEST);
	glClearDepth(1);
	glClearStencil(i);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);

	glLoadIdentity();
	camera->call();
	draw(true);												// Draw 3D stuff

	glClear(GL_STENCIL_BUFFER_BIT);

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);

	glCullFace(GL_BACK);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	drawShadowVolumes();

	glCullFace(GL_FRONT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

	drawShadowVolumes();

	glDepthMask( GL_TRUE );
	glCullFace(GL_BACK);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

	//begin2d

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1024, 0, 768);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor4f(0, 0, 0, 0.6f);
	glBegin(GL_QUADS);
	glVertex2f(0, 768);
	glVertex2f(1024, 768);
	glVertex2f(1024, 0);
	glVertex2f(0, 0);
	glEnd();

	//end 2d
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();

	SDL_GL_SwapBuffers();
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
}
//--------------------------------------------------
void Scene::renderNormal()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// Clear the screen and the depth buffer
	glLoadIdentity();
	camera->call();
	draw(true);												// Draw 3D stuff
	SDL_GL_SwapBuffers();								// Swap the front buffer with the back buffer
}
//--------------------------------------------------
void Scene::render()
{
	static int frameCount = -1;

	// now update the cube map
	// because our scene is pretty much static, we need to do this
	// every couple of frames only
	
	// uncomment this if you implemented environment mapping
	/*frameCount = (frameCount + 1) % 500;
	if (frameCount == 0)
	{
		updateCubeMap();
	}*/

	switch (shadowMode)
	{
	default:
		renderNormal();
		break;
	case 1:
		renderShadowVolumes();
		break;
	case 2:
	case 3:
		renderShadowMapping();
		break;
	}
}
//--------------------------------------------------
void Scene::update(double timeDifference)
{
	float cameraMovement = (float) timeDifference * cameraSpeed;

	if (input->isKeyDown(SDLK_w) || input->isKeyDown(SDLK_UP))
	{
		camera->move(0, 0, cameraMovement);
	}

	if (input->isKeyDown(SDLK_s) || input->isKeyDown(SDLK_DOWN))
	{
		camera->move(0, 0, -cameraMovement);
	}

	if (input->isKeyDown(SDLK_a) || input->isKeyDown(SDLK_LEFT))
	{
		camera->move(cameraMovement, 0, 0);
	}

	if (input->isKeyDown(SDLK_d) || input->isKeyDown(SDLK_RIGHT))
	{
		camera->move(-cameraMovement, 0, 0);
	}

	if (input->isKeyDown(SDLK_r))
	{
		camera->move(0, -cameraMovement, 0);
	}

	if (input->isKeyDown(SDLK_f))
	{
		camera->move(0, cameraMovement, 0);
	}

	if (input->isKeyDown(SDLK_1))
	{
		shadowMode = 0;
		Shader::setDefaultShader(NULL);
	}

	if (input->isKeyDown(SDLK_2))
	{
		shadowMode = 1;
		Shader::setDefaultShader(NULL);
	}

	if (input->isKeyDown(SDLK_3))
	{
		shadowMode = 2;
		Shader::setDefaultShader(shadowMapping);
	}

	if (input->isKeyDown(SDLK_4))
	{
		shadowMode = 3;
		Shader::setDefaultShader(shadowMapping);
	}


	if (input->isKeyDown(SDLK_h))
	{
		helpText->setText("==Computer Grafik: OpenGL Shader Praktikum==\n\nBewegen:        WASD- oder Pfeiltasten\nHöhe ändern:    R/F-Tasten\nKamera drehen:  Maus\nSchatten-Modus: Tasten 1-4\nBeenden:        ESC\n");
	}
	else
	{
		stringstream fpsText;
		fpsText << "FPS:" << (floor(1000.0 / timeDifference + 0.5)) << "\nHilfe einblenden: H-Taste gedrückt halten";
		helpText->setText(fpsText.str());
	}


	camera->rotate((float)(input->getMouseMotionY()*0.2), (float)(input->getMouseMotionX()*0.2));

	Vector3f tempPos = skybox->getSunDirection();
	sun->setPosition(tempPos.x, tempPos.y, tempPos.z, 0.0);

	sun->setDiffuse(tempPos.y + 0.2f, tempPos.y, tempPos.y, 1);

	torch1->update((float)(timeDifference / 30.0));
	torch2->update((float)(timeDifference / 30.0));
	skybox->update(timeDifference);

	armorRotation += (float)timeDifference * 0.004f;
}
//--------------------------------------------------
void Scene::draw(bool activateShaders)
{
	sun->call();

	// now let's draw our armor right here
	// to perform environment mapping, we need to set up our shader now

	if (activateShaders)
	{
		float modelPosition[3];

		modelPosition[0] = -1200;
		modelPosition[1] = -42;
		modelPosition[2] = -1200;

		// uncomment this if you implemented environment mapping
		/*envShader->enable();

		glMatrixMode(GL_TEXTURE);
		glActiveTexture(GL_TEXTURE3);
		glPushMatrix();

		glLoadIdentity();*/
		// end

		//Here is the view point corrected. NOTE we're in Texture matrix mode!
		// uncomment this if you implemented environment mapping
		/*glRotatef(camera->getRotation().y, 0.0f, 1.0f, 0.0f);
		glRotatef(camera->getRotation().x, 1.0f, 0.0f, 0.0f);

		glMatrixMode(GL_MODELVIEW);

		envShader->loadTextureTU3(GL_TEXTURE_CUBE_MAP_ARB, envText, "envMap");
		float values[] = {0.4f, 0.4f, 0.4f};

		envShader->loadUniform3f("baseColor", values);
		envShader->loadUniform1f("mixRatio", 0.5f);

		glPushMatrix();
		glTranslatef(modelPosition[0], modelPosition[1], modelPosition[2]);


		glRotatef(armorRotation, 0, 1, 0);

		armor->showS();

		glPopMatrix();

		envShader->useDefaultShader();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);*/
		// end
	}

	glActiveTexture(GL_TEXTURE0);

	skybox->render(false);
	terrain->render(false);
	water->render(false);
	mainObj->render(activateShaders);

	Shader::disable();
	torch1->render(false);
	torch2->render(false);
	Shader::defaultShader;

	Shader::disable();
	helpText->render(false);
	Shader::useDefaultShader();
}
//--------------------------------------------------
void Scene::drawShadowVolumes()
{
	mainObj->renderShadowVolumes(sun);
}
//--------------------------------------------------
int Scene::countInsideVolume()
{
	return mainObj->countInsideVolume(camera, sun);
}
//--------------------------------------------------
void Scene::updateCubeMap()
{
	// we need to render the scene six times from different angles
	// to do this we need a fov of 90 degrees
	// we also have to reduce the viewport to sth. like 256 x 256

	glViewport(0, 0, CUBE_MAP_SIZE, CUBE_MAP_SIZE);     // so we don't get huge cubemaps
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.0f, 1, 50000);  // get a 90 deg. fov with an
	// aspect ratio of 1
	glMatrixMode(GL_MODELVIEW);

	// now render the scene six times
	for (int i = 0; i < 6; i++)
	{
		// Clear the depth buffer!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset modelview matrix.
		glLoadIdentity();

		// -> set camera for rendering
		// TODO:
		// ******
		switch (i)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		}

		//to avoid uneven lighting in the cube map, we have to call the light again here (after changing the camera)
		sun->call();

		glTranslated(1200.0, -42.0, 1200.0);      // this is just temporary


		// now render the objects
		skybox->render(false);
		mainObj->render(false);
		terrain->render(false);
		water->render(false);

		// alright, now enable cube mapping and update the cube map
		glEnable(GL_TEXTURE_CUBE_MAP_ARB);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, envText);    // bind cube map


		// copy read buffer to target part of cube map
		// TODO:
		// ******
    /*
		glCopyTexSubImage2D( ,							   // target
		                     ,                             // level
		                     ,                             // xoffset
		                     ,                             // yoffset
		                     ,                             // x
		                     ,                             // y
		                     ,							   // width
		                     );							   // height

    
    */
		glFlush();
		glDisable(GL_TEXTURE_CUBE_MAP_ARB);
	}

	// now set back viewport und projection matrix to default values
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (float)width / (float)height, 1, 100000);
	glMatrixMode(GL_MODELVIEW);
}
//--------------------------------------------------
void Scene::loadObjects(string filename, Object* obj)
{
	string name;
	name = "./Daten/Groups/";
	name.append(filename);
	name.append(".txt");

	ErrorLog *log = ErrorLog::getInstance();
	stringstream logStream;
	logStream << endl;
	logStream << "loading objects..." << endl << endl;
	log->reportError(logStream.str());

	FILE *fp = fopen(name.c_str(), "r");

	if (!fp)
	{
		logStream.str("");
		logStream << "Error, no input file!" << endl;
		log->reportError(logStream.str());
		return;
	}

	int res = 0;
	while (res != EOF)
	{
		char name[256] = "";
		float plz[6];
		res = fscanf(fp, "%s %f %f %f %f %f %f\n", &name, &plz[0], &plz[1], &plz[2], &plz[3], &plz[4], &plz[5]);

		ObjModel *model = new ObjModel();
		model->load(name, texturLoader, shLoader);

		Object *newObj = new Object();
		newObj->addModel(model);
		newObj->setPosition(plz[0], plz[1], plz[2]);
		newObj->setRotation(plz[3], plz[4], plz[5]);

		obj->addObject(newObj);
	}
}
//--------------------------------------------------
