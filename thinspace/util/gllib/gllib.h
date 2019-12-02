
#ifndef UTIL_GLLIB_H_
#define UTIL_GLLIB_H_

#ifdef INCLUDE_GL_MAC

	#define GLFW_INCLUDE_GLCOREARB
	
	#include <GLFW/glfw3.h>
	#include <OpenGl/gl3.h>

#else
	
	#include <GL/gl.h>

#endif

#endif // UTIL_GLLIB_H_ 