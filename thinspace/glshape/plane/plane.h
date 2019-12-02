
#ifndef GLSHAPE_PLANE_H_
#define GLSHAPE_PLANE_H_

#include <functional>
#include "mesh/mesh.h"

namespace glshape {
namespace plane {

gl::MeshPtr Create(
	
	int resolution_x, 
	int resolution_y, 
	const std::function<void (int index, int x, int y, int size, int vertex_size, float* vertices)> callback = 0

);

} // namespace plane
} // namespace glshape

#endif // GLSHAPE_PLANE_H_