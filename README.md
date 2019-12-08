
# Thinspace

A lightweight, C++ OpenGL Library

## Get Started on Mac

main.cc

`
	
	#include "app.h"
	#include "glfw_context/glfw_context.h"

	int main(int argc, char** argv) {

		context::GLFWContext context;

		context.create(

			std::string("My App").c_str(),
			640, // width
			360 // height

		);

		auto app = App(&argv[0]);

		app.Init();

		while(!context.shouldClose()) {

			app.Draw();

			glfwSwapBuffers(context.get());

			glfwPollEvents();

		}

		return 0;

	}

`

Compile:

`
	make -f thinspace/make/mac/makefile
`

## Get Started on Raspberry Pi 4

main.cc

`
	
	#include "app.h"
	#include "drm_context/drm_context.h"

	int main(int argc, char** argv) {

		context::DRMContext context;

		context.Init();

		auto app = thinspace::App(&argv[0]);

		app.Init();

		while(1) {

			app.Draw();

			context.SwapBuffers();

		}

		return 0;

	}

`

Compile:

`
	make -f thinspace/make/pi/makefile
`
