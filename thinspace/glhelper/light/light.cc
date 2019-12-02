
#include "light.h"

namespace gl {

glm::mat4 Light::OrthographicProjection(float left, float right, float bottom, float top, float near, float far) const {

	return glm::ortho(
		left,
		right,
		bottom,
		top,
		near,
		far
	);
}

std::vector<glm::mat4> Light::CubeMapProjection(void) const {

	float aspect_ratio = (float)config_.shadow.width / (float)config_.shadow.height;

	auto perspective = glm::perspective(
		config_.shadow.field_of_view,
		aspect_ratio,
		config_.shadow.near,
		config_.shadow.far
	);

	return {
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		perspective * glm::lookAt(translation_, translation_ + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))
	};

}

glm::mat4 Light::View(void) const {

	return glm::lookAt(
		translation_,
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

} // namespace gl