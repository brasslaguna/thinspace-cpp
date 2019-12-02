
#include "app.h"
#include "glfw_context/glfw_context.h"

int main(int argc, char** argv) {

	context::GLFWContext context;

	context.create(

		std::string("").c_str(),
		300,
		300

	);

	auto app = thinspace::App(&argv[0]);

	while(!context.shouldClose()) {

		app.Draw();

		glfwSwapBuffers(context.get());

		glfwPollEvents();

	}

	return 0;

}