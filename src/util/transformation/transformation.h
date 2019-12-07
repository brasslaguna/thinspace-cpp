
#ifndef THINSPACE_GL_TRANSFORMATION_H_
#define THINSPACE_GL_TRANSFORMATION_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl {

class Transformation {

	public:

		glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f), rotation_ = glm::vec3(0.0f, 0.0f, 0.0f), scale_ = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4 Matrix(void) const;
		glm::mat4 CalculateRotation(void) const;
		
};

} // namespace gl

#endif // THINSPACE_GL_TRANSFORMATION_H_
