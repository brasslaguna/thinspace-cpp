
#include "app/app.h"
#include "drm_context/drm_context.h"

int main(int argc, char** argv) {

	context::DRMContext context;

	context.Init();

	auto app = thinspace::App(&argv[0]);

	while(1) {

		app.Draw();

		context.SwapBuffers();

	}

	return 0;

}