
#include "glfw_context.h"

namespace context {

static void error_callback(int error, const char* description) {

    std::cerr << "Error: " << description << std::endl;

}

bool GLFWContext::create(const char* title, const int& width, const int& height) {

	glfwSetErrorCallback(error_callback);

	if(glfwInit()) {

		glfwWindowHint(GLFW_SAMPLES, 4);
	 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
 		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
 		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    	if(!window_)

    		glfwTerminate();

    	glfwMakeContextCurrent(window_);

    	return true;

	} else {

		return false;
		
	}

}

void GLFWContext::SetWindowTitle(const char* title) {

	glfwSetWindowTitle(window_, title);

}

GLFWwindow* GLFWContext::get(void) const {

	return window_;

}

int GLFWContext::shouldClose(void) const {

    return glfwWindowShouldClose(window_);

}

void GLFWContext::size(int* size) const {

	glfwGetFramebufferSize(window_, &size[0], &size[1]);

}

} // namespace context