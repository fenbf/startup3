/** @file utils.cpp
 *  @brief impleentation of useful utilities for opengl based apps
 *
 *	Effects in Games, June 2012
 */

#include "stdafx.h"

#include "utils.h"

namespace utils
{

///////////////////////////////////////////////////////////////////////////////
bool initGL(bool vsync)
{
    //
    // load opengl 3.3 + some basic WGL etxensions:
    //
    int didLoad = ogl_LoadFunctions();
    int didWGLLoad = wgl_LoadFunctions(wglGetCurrentDC());

    LOG("- - - - - - - - - - - - - - - - - - - - - - - ");
    LOG("OpenGL 3.3 Compatibility \t%s", didLoad == ogl_LOAD_SUCCEEDED ? "Loaded!" : "not loaded!");    
    LOG("WGL basic extensions     \t%s", didWGLLoad == ogl_LOAD_SUCCEEDED? "Loaded!" : "not loaded!");   

	// print some GL info:
	int majorVersion = -1;
	int minorVersion = -1;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	LOG("- - - - - - - - - - - - - - - - - - - - - - - ");
	LOG("OpenGL Version:  %d.%d", majorVersion, minorVersion);
	LOG("OpenGL Renderer: %s", (char *)glGetString(GL_RENDERER));
	LOG("OpenGL Vendor:   %s", (char *)glGetString(GL_VENDOR));
	LOG("GLSL Version:    %s", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
	LOG("- - - - - - - - - - - - - - - - - - - - - - - \n");

#ifdef WIN32
	wglSwapIntervalEXT(vsync ? 1 : 0);
#endif

	return true;
}

///////////////////////////////////////////////////////////////////////////////
void calculateFps(float *fps)
{
	static unsigned int frame = 0;
	static int timeBase = 0;
	
	frame++;

	int t = glutGet(GLUT_ELAPSED_TIME);
	if (t - timeBase > 1000) 
	{
		*fps = 0.5f*(*fps) + 0.5f*(frame*1000.0f/(float)(t - timeBase));
		timeBase = t;		
		frame = 0;
	}

}

///////////////////////////////////////////////////////////////////////////////
void updateTimer(double *deltaTime, double *appTime, const double REFRESH_TIME)
{
	static double lastDeltas[3] = { 0.0, 0.0, 0.0 };
	
	// in milisec
	int t = glutGet(GLUT_ELAPSED_TIME);
	double newTime = (double)t*0.001;

	*deltaTime = newTime - *appTime;
	if ((*deltaTime) < 0) *deltaTime = 0.0;
    if ((*deltaTime) > REFRESH_TIME) *deltaTime = REFRESH_TIME;

	// average:
	*deltaTime = ((*deltaTime) + lastDeltas[0] + lastDeltas[1] + lastDeltas[2]) * 0.25;

	*appTime = (*appTime) + (*deltaTime);

	// save delta:
	lastDeltas[0] = lastDeltas[1];
	lastDeltas[1] = lastDeltas[2];
	lastDeltas[2] = *deltaTime;
}

///////////////////////////////////////////////////////////////////////////////
bool checkGLErrors(const char *func, const char * file, int line)
{
	GLenum err;
    bool good = true;

    err = glGetError();
    while (err != GL_NO_ERROR)
    {
		const char * message = "";
		switch( err )
		{
		case GL_INVALID_ENUM:
			message = "Invalid enum";
			break;
		case GL_INVALID_VALUE:
			message = "Invalid value";
			break;
		case GL_INVALID_OPERATION:
			message = "Invalid operation";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			message = "Invalid framebuffer operation";
			break;
		case GL_OUT_OF_MEMORY:
			message = "Out of memory";
			break;
		default:
			message = "Unknown error";
		}

        LOG("OpenGL ERROR in [%s] %s(%d): %s\n", func, fileNameFromPath(file), line, message);
        good = false;
        err = glGetError();
	}
	return good;
}

} // namespace utils