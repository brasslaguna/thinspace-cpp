
#ifndef THINSPACE_GLSHAPE_CONE_H_
#define THINSPACE_GLSHAPE_CONE_H_

#include <vector>
#include <cmath>

#include "mesh/mesh.h"
#include "cylinder/cylinder.h"

namespace glshape {
namespace cone {

gl::MeshPtr Create(

	int res,
	float height,
	float taper,
	int segments
	
);

} // namespace cone
} // namespace glshape

#endif // THINSPACE_GLSHAPE_CONE_H_