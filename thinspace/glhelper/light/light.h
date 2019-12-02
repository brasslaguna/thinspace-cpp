
#ifndef GL_LIGHT_H_
#define GL_LIGHT_H_

#include <memory>
#include <vector>

#include <glm/gtx/matrix_decompose.hpp> 

#include "scene_component/scene_component.h"
#include "transformation/transformation.h"
#include "camera/camera.h"

namespace gl {

typedef struct {

	int width;
	int height;
	float field_of_view;
	float near;
	float far;
	float distance;
	int pcf;
	glm::vec3 color;

} ShadowConfig;

typedef struct {

	std::string name;
	glm::vec3 color;
	float intensity;
	float quadratic;
	float falloff;

	ShadowConfig shadow;

} LightConfig;

class Light 
	: public SceneComponent<Light>,
	  public Transformation {

		public:

			Light(LightConfig config)
				: config_(config) {};

			glm::mat4 OrthographicProjection(float left, float right, float bottom, float top, float near, float far) const;
			std::vector<glm::mat4> CubeMapProjection(void) const;
			glm::mat4 View(void) const;

			void ComponentLoop(void) {

				if(component_loop_)

					component_loop_(*this);
				
			};

			LightConfig config_;
};

typedef std::shared_ptr<Light> LightPtr;

} // namespace gl

#endif // GL_LIGHT_H_