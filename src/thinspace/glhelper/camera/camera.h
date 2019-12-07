
#ifndef THINSPACE_GL_CAMERA_H_
#define THINSPACE_GL_CAMERA_H_

#include <memory>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "scene_component/scene_component.h"
#include "transformation/transformation.h"

namespace gl {

typedef struct {

	std::string name;
	float field_of_view;
	float aspect_ratio;
	float near;
	float far;

} CameraConfig;

class Camera 
	: public SceneComponent<Camera>,
	  public Transformation {

	public:

		Camera(const CameraConfig& config)
			: field_of_view_(config.field_of_view),
			  aspect_ratio_(config.aspect_ratio),
			  near_(config.near),
			  far_(config.far) {};

		void ComponentLoop(void) {

			if(component_loop_)

				component_loop_(*this);

		};

		float field_of_view_, aspect_ratio_, near_, far_;

		glm::mat4 Perspective(void) const;
		glm::mat4 LookAt(void) const;
		glm::mat4 View(void) const;

	private:

		glm::vec3 center_;
		glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
		
};

typedef std::shared_ptr<Camera> CameraPtr;

} // namespace gl

#endif // THINSPACE_GL_CAMERA_H_