
#include "scene.h"

namespace gl {

void Scene::Init(void) {

	framebuffer_ = FramebufferPtr(

		new Framebuffer(

			(FramebufferConfig) {

				.width = config_.width,
				.height = config_.height

			}

		)

	);
	
	framebuffer_->CreateBuffer(

		(RenderbufferConfig) {

			.name = "depth",
			.internal_format = GL_DEPTH_COMPONENT

		}

	);

	framebuffer_->Attach(

		"depth",
		GL_RENDERBUFFER,
		GL_DEPTH_ATTACHMENT

	);

	pipeline_ = glhelper::PassPipelinePtr(

		new glhelper::PassPipeline(

			framebuffer_

		)

	);
	
}

void Scene::Draw(void) const {

	pipeline_->Run(config_.clear_color);

}

void Scene::AddPasses(std::map<std::string, glhelper::Pass> passes) {

	pipeline_->Add(passes);

}

} // namespace gl
