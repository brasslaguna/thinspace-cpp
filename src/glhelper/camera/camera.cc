
#include "camera.h"

namespace gl {

glm::mat4 Camera::LookAt(void) const {

	return glm::lookAt(translation_, center_, up_);

}

glm::mat4 Camera::Perspective(void) const {

	return glm::perspective(field_of_view_, aspect_ratio_, near_, far_);

}

glm::mat4 Camera::View(void) const {

	return glm::inverse(Matrix());
	
}

} // namespace gl