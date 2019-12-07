
#ifndef THINSPACE_GLSHAPE_SPHERE_H_
#define THINSPACE_GLSHAPE_SPHERE_H_

#include <vector>
#include <cmath>

#include "mesh/mesh.h"

namespace glshape {
namespace sphere {

gl::MeshPtr Create(int res_x, int res_y);

} // namespace icosphere
} // namespace glshape

#endif // THINSPACE_GLSHAPE_SPHERE_H_