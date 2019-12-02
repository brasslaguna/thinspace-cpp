
#include "transformation.h"

namespace gl {

glm::mat4 Transformation::CalculateRotation(void) const {

	auto rotation_x = glm::angleAxis(glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
	auto rotation_y = glm::angleAxis(glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
	auto rotation_z = glm::angleAxis(glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return glm::mat4_cast(rotation_x * rotation_y * rotation_z);

}

glm::mat4 Transformation::Matrix(void) const {

	return (glm::translate(translation_) * CalculateRotation() * glm::scale(scale_));
	
}

} // namespace gl