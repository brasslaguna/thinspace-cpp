
#ifdef INCLUDE_GL_MAC

#ifndef THINSPACE_CONTEXT_GLFW_CONTEXT_H_
#define THINSPACE_CONTEXT_GLFW_CONTEXT_H_

#include <iostream>
#include <GLFW/glfw3.h>

namespace context {

class GLFWContext {

	public:

		bool create(const char* title, const int& width, const int& height);
		void size(int* size) const;
		GLFWwindow* get(void) const;
		int shouldClose(void) const;
		void SetWindowTitle(const char* title);

	private:

		GLFWwindow* window_;
		
};

}

#endif // THINSPACE_CONTEXT_GLFW_CONTEXT_H_

#endif // INCLUDE_GL_MAC