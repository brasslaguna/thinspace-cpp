
#ifndef THINSPACE_UTIL_GLLIB_H_
#define THINSPACE_UTIL_GLLIB_H_

#ifdef INCLUDE_GL_MAC

	#define GLFW_INCLUDE_GLCOREARB
	
	#include <GLFW/glfw3.h>
	#include <OpenGl/gl3.h>

#else

	#include <EGL/egl.h>
	#include <GLES3/gl3.h>


#endif

#endif // THINSPACE_UTIL_GLLIB_H_ 
