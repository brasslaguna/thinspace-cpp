
#ifndef THINSPACE_GLSHAPE_PLANE_H_
#define THINSPACE_GLSHAPE_PLANE_H_

#include <functional>
#include "mesh/mesh.h"

namespace glshape {
namespace plane {

const int kVertexSize = 14;

void Generate(
	int resolution_x, 
	int resolution_y, 
	float* vertices, 
	int* indices, 
	const std::function<void (int index, int x, int y, int size, int vertex_size, float* vertices)> callback = 0
);

gl::MeshPtr Create(
	
	int resolution_x, 
	int resolution_y, 
	const std::function<void (int index, int x, int y, int size, int vertex_size, float* vertices)> callback = 0

);

} // namespace plane
} // namespace glshape

#endif // THINSPACE_GLSHAPE_PLANE_H_