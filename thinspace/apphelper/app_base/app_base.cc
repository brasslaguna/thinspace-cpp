
#include "app_base.h"
#include "plane/plane.h"

namespace apphelper {

static void UpdateViewport(int width, int height) {

	glViewport(
		0,
		0,
		width,
		height
	);

}

AppBase::AppBase(std::string root_dir) {

	motion_factory_ = util::MotionFactoryPtr(

		new util::MotionFactory()

	);

	view_mesh_ = glshape::plane::Create(2, 2);

	Create(

		(gl::ShaderConfig) {

			.name = "view_fragment",
			.type = GL_FRAGMENT_SHADER,
			.file_path = root_dir + "/shader/view/fragment.glsl"

		}

	);

	Create(

		(gl::ShaderConfig) {

			.name = "view_vertex",
			.type = GL_VERTEX_SHADER,
			.file_path = root_dir + "/shader/view/vertex.glsl"

		}

	);

	view_shader_program_ = Create(

		(gl::ShaderProgramConfig) {

			.name = "view",
			.vertex_shader_name = "view_vertex",
			.fragment_shader_name = "view_fragment"

		}

	);

}

void AppBase::Render(void) {

	int width, height;
	GetViewportSize(width, height);

	auto update_frame = timer_.UpdateFrame();

	if(update_frame)

		motion_factory_->Run();

	for(auto item : scenes_) {

		auto scene = item.second;
		auto framebuffer = scene->framebuffer_;

		UpdateViewport(
			framebuffer->config_.width,
			framebuffer->config_.height
		);

		if(update_frame)

			scene->ComponentLoop();

		scene->Draw();

	}

	RenderViews(width, height);

}

void AppBase::RenderViews(int width, int height) const {

	UpdateViewport(width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, buffers);

	view_shader_program_->Use();

	for(const auto& view : views_) {

		view_shader_program_->SetUniform(

			"model",
			
			glm::value_ptr(

				view.transformation

			)

		);

		if(view.texture)

			view.texture->Bind();

		view_mesh_->Draw();

	}

}

void AppBase::GetViewportSize(int& width, int& height) const {

	GLint viewport_size[4];
	glGetIntegerv(GL_VIEWPORT, viewport_size);
	width = viewport_size[2];
	height = viewport_size[3];

}

gl::ScenePtr AppBase::Create(gl::SceneConfig config) {

	gl::ScenePtr scene(new gl::Scene(config));

	scenes_.insert(

		std::make_pair(config.name, scene)

	);

	return scene;

}

gl::CameraPtr AppBase::Create(gl::CameraConfig config) {

	gl::CameraPtr camera(new gl::Camera(config));

	cameras_.insert(

		std::make_pair(config.name, camera)

	);

	return camera;

}

gl::TexturePtr AppBase::Create(gl::TextureConfig config) {

	gl::TexturePtr texture(new gl::Texture(config));

	textures_.insert(

		std::make_pair(config.name, texture)

	);

	return texture;

}

gl::LightPtr AppBase::Create(gl::LightConfig config) {

	gl::LightPtr light(new gl::Light(config));

	lights_.insert(

		std::make_pair(config.name, light)

	);

	return light;

}

gl::ModelPtr AppBase::Create(gl::ModelConfig config) {

	gl::ModelPtr model(new gl::Model(config));

	models_.insert(

		std::make_pair(config.name, model)

	);

	return model;

}

bool AppBase::Create(gl::ShaderConfig config) {
	
	gl::ShaderPtr shader(new gl::Shader(config.type));

	if(shader->load_file(config.file_path)) {

		shaders_.insert(

			std::make_pair(config.name, shader)

		);

		return true;

	} else {

		return false;

	}

}

gl::ShaderProgramPtr AppBase::Create(gl::ShaderProgramConfig config) {

	auto vertex_shader = shaders_.find(config.vertex_shader_name);
	auto geometry_shader = shaders_.find(config.geometry_shader_name);
	auto fragment_shader = shaders_.find(config.fragment_shader_name);

	gl::ShaderProgramPtr shader_program(new gl::ShaderProgram);

	if(vertex_shader != shaders_.end())

		shader_program->Attach(*vertex_shader->second);

	if(geometry_shader != shaders_.end())

		shader_program->Attach(*geometry_shader->second);

	if(fragment_shader != shaders_.end())

		shader_program->Attach(*fragment_shader->second);

	shader_program->Link();

	shader_program->GetUniforms();

	shader_programs_.insert(

		{ config.name, shader_program }

	);

	return shader_program;

}

} // namespace apphelper