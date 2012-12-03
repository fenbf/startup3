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

// attributes:
// the same values should be placed in "layout(location=N)" in the vertex shaders
#define VERTEX_ATTRIB_TEXCOORD0 3
#define VERTEX_ATTRIB_COLOR 1

// shaders:
ShaderProgram mProgram;

// tunel params:
const float TUNEL_LEN = 12.0f;
const float TUNEL_RAD = 0.5f;
const int TUNEL_SIDES = 32;
const int TUNEL_RINGS = 24;

float gAnimParam = 0.0f;

// todo: add texture indices...

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
    gCamPos[2] = 10.0f;

    //
    // generate texture:
    //

    // todo: load textures... using soil

    //
    // shaders
    //
    shaderUtils::loadAndBuildShaderPairFromFile(&mProgram, "shaders/w03_tunel.vs", "shaders/w03_tunel.fs");

    //
    // UI:
    //
    TwAddVarRW(Globals::sMainTweakBar, "camera Z", TW_TYPE_FLOAT, &gCamPos[2], "min=0.0 max=12.0 step=0.1");

	return true;
}

///////////////////////////////////////////////////////////////////////////////
void cleanUp()
{
    // cleanup textures...
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
    gAnimParam += 1.0f * (float)deltaTime;
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

    
    // update "animParam" uniform...
    mProgram.uniform1f("animParam", gAnimParam);

    // todo: setup texture uniforms...
    mProgram.uniformMatrix4f("matProjection", glm::value_ptr(gProjectionMatrix));
    mProgram.uniformMatrix4f("matModelview",  glm::value_ptr(gModelViewMatrix));
    

    // draw faces of the tunnel:
    const float dz = TUNEL_LEN/(float)TUNEL_RINGS;
    const float da = ((float)M_PI*2.0f)/(float)TUNEL_SIDES;
    const float du = 1.0f/(float)TUNEL_SIDES;
    const float dv = 1.0f/(float)TUNEL_RINGS;

    // left:
    // todo: activate proper texture units...

    // todo: draw tunnel

    mProgram.disable();
}
