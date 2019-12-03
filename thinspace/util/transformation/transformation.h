
#ifndef GL_TRANSFORMATION_H_
#define GL_TRANSFORMATION_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl {

class Transformation {

	public:

		glm::vec3 translation_, rotation_, scale_ = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4 Matrix(void) const;
		glm::mat4 CalculateRotation(void) const;
		
};

} // namespace gl

#endif // GL_TRANSFORMATION_H_