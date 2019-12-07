
#ifndef THINSPACE_GL_SCENE_H_
#define THINSPACE_GL_SCENE_H_

#include <string>
#include <memory>

#include "scene_component/scene_component.h"
#include "pass_pipeline/pass_pipeline.h"

namespace gl {

typedef struct {

	std::string name;
	glm::vec3 clear_color;
	int width;
	int height;

} SceneConfig;

class Scene : public SceneComponent<Scene> {

	public:

		Scene(const SceneConfig& config) 
			: config_(config) {

				Init();

			};

		void Draw(void) const;
		void AddPasses(std::map<std::string, glhelper::Pass>);

		void ComponentLoop(void) {

			if(component_loop_)

				component_loop_(*this);

		};

		FramebufferPtr framebuffer_;
		TexturePtr screen_texture_;
		SceneConfig config_;

	private:
		
		void Init(void);
		glhelper::PassPipelinePtr pipeline_;
		
};

typedef std::shared_ptr<Scene> ScenePtr;

} // namespace gl

#endif // THINSPACE_GL_SCENE_H_