/** @file w03_walls.cpp
 *  @brief walls application, texture usage demonstration
 *
 *	OpenGL Programming, November 2012
 */

#include "stdafx.h"
#include "main.h"
#include "utils.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderUtils.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// globals

// transformations & camera
glm::vec3 gCamPos;
glm::mat4 gModelViewMatrix;
glm::mat4 gProjectionMatrix;

// textures:
// todo: add texture id

// attributes:
// the same values should be placed in "layout(location=N)" in the vertex shaders
#define VERTEX_ATTRIB_TEXCOORD0 3
#define VERTEX_ATTRIB_COLOR 1

// shaders:
ShaderProgram mProgram;

///////////////////////////////////////////////////////////////////////////////

bool initApp() 
{
    //
    // some global GL states
    //
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //
    // camera pos
    //
    gCamPos[0] = 0.0f;
    gCamPos[1] = 0.0f;
    gCamPos[2] = 2.2f;

    //
    // generate texture:
    //
    // todo: add texture data generation...

    // nearest
    // todo: create first texture... 

    // linear
    // todo: create second texture...

    //
    // shaders
    //
    shaderUtils::loadAndBuildShaderPairFromFile(&mProgram, "shaders/w03_shader.vs", "shaders/w03_shader.fs");

    //
    // UI:
    //
    TwAddVarRW(Globals::sMainTweakBar, "camera Z", TW_TYPE_FLOAT, &gCamPos[2], "min=0.0 max=10.0 step=0.1");

	return true;
}

///////////////////////////////////////////////////////////////////////////////
void cleanUp()
{
    // todo: cleanup textures...
}

///////////////////////////////////////////////////////////////////////////////
void changeSize(int w, int h)
{
    float aspect = (float)w/(float)h;

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // setup projection matrix
	gProjectionMatrix = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
}

///////////////////////////////////////////////////////////////////////////////
void processNormalKeys(unsigned char key, int x, int y) 
{
	if (key == 27) 
		exit(0);
}

///////////////////////////////////////////////////////////////////////////////
void pressSpecialKey(int key, int x, int y) 
{
    if (key == GLUT_KEY_UP)
        gCamPos[2] += 1;
    else if (key == GLUT_KEY_DOWN)
        gCamPos[2] -= 1;

	else if (key == GLUT_KEY_LEFT)
        gCamPos[0] += 0.1f;
    else if (key == GLUT_KEY_RIGHT)
        gCamPos[0] -= 0.1f;
}


///////////////////////////////////////////////////////////////////////////////
void releaseSpecialKey(int key, int x, int y) 
{
	
}

///////////////////////////////////////////////////////////////////////////////
void processMouse(int button, int state, int x, int y)
{
	// todo: add some custom code...
}

///////////////////////////////////////////////////////////////////////////////
void processMouseMotion(int x, int y)
{
	// todo: add some custom code...	
}

///////////////////////////////////////////////////////////////////////////////
void processMousePassiveMotion(int x, int y)
{
	// todo: add some custom code...	
}

///////////////////////////////////////////////////////////////////////////////
void updateScene(double deltaTime) 
{
	
}

///////////////////////////////////////////////////////////////////////////////
void renderScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// camera
	//
	gModelViewMatrix = glm::lookAt(gCamPos, glm::vec3(0.0f, 0.0f, gCamPos[2]-2), glm::vec3(0.0f, 1.0f, 0.0f)); 

    //
    // shader setup
    //
    mProgram.use();
    // todo: setup texture unit...
    mProgram.uniformMatrix4f("matProjection", glm::value_ptr(gProjectionMatrix));
    mProgram.uniformMatrix4f("matModelview",  glm::value_ptr(gModelViewMatrix));
    

    // draw faces of the tunnel:
    const float TUNEL_LEN = 7.0f;
    const float TUNEL_H = 0.5f;
    const float TUNEL_W = 0.5f;

    // todo: add walls drawing code...

    mProgram.disable();
}
