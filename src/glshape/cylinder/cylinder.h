
#ifndef THINSPACE_GLSHAPE_CYLINDER_H_
#define THINSPACE_GLSHAPE_CYLINDER_H_

#include <vector>
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "mesh/mesh.h"

namespace glshape {
namespace cylinder {

typedef struct {
	std::vector<float> vertices;
	std::vector<int> indices;

} Buffer;

gl::MeshPtr Create(

	int res,
	float height,
	int segments
	
);

Buffer CreateBand(

	glm::vec3 origin, 
	glm::vec2 radius, 
	int res, 
	float height,
	float taper,
	int seg_index

);

} // namespace cylinder
} // namespace glshape

#endif // THINSPACE_GLSHAPE_CYLINDER_H_