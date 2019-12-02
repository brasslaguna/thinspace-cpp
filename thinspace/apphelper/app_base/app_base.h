
#ifndef APP_BASE_H_
#define APP_BASE_H_

#include <string>
#include <memory>
#include <map>

#include <glm/gtc/type_ptr.hpp>

#include "timer/timer.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "shader_program/shader_program.h"
#include "light/light.h"
#include "model/model.h"
#include "motion_factory/motion_factory.h"

namespace apphelper {

typedef struct {

	glm::mat4 transformation;
	gl::TexturePtr texture;

} RenderViewConfig;

typedef std::map<std::string, gl::ScenePtr> SceneMap;
typedef std::map<std::string, gl::CameraPtr> CameraMap;
typedef std::map<std::string, gl::TexturePtr> TextureMap;
typedef std::map<std::string, gl::ShaderPtr> ShaderMap;
typedef std::map<std::string, gl::ShaderProgramPtr> ShaderProgramMap;
typedef std::map<std::string, gl::LightPtr> LightMap;
typedef std::map<std::string, gl::ModelPtr> ModelMap;

class AppBase {

	public:

		AppBase(std::string root_dir);

		void Render(void);
		void GetViewportSize(int& width, int& height) const;

		gl::ScenePtr Create(gl::SceneConfig config);
		gl::CameraPtr Create(gl::CameraConfig config);
		gl::TexturePtr Create(gl::TextureConfig config);
		bool Create(gl::ShaderConfig config);
		gl::ShaderProgramPtr Create(gl::ShaderProgramConfig config);
		gl::LightPtr Create(gl::LightConfig config);
		gl::ModelPtr Create(gl::ModelConfig config);

		util::MotionFactoryPtr motion_factory_;

		std::vector<RenderViewConfig> views_;

	private:

		void RenderViews(int width, int height) const;

		gl::MeshPtr view_mesh_;
		util::Timer timer_;
		gl::ShaderProgramPtr view_shader_program_;

		SceneMap scenes_;
		CameraMap cameras_;
		TextureMap textures_;
		ShaderMap shaders_;
		ShaderProgramMap shader_programs_;
		LightMap lights_;
		ModelMap models_;

};

typedef std::shared_ptr<AppBase> AppBasePtr;

} // namespace apphelper

#endif // APP_BASE_H_