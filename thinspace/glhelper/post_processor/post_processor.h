
#ifndef GL_POST_PROCESSOR_H_
#define GL_POST_PROCESSOR_H_

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "plane/plane.h"
#include "pass_pipeline/pass_pipeline.h"
#include "shader_program/shader_program.h"
#include "mesh/mesh.h"

namespace gl {

typedef struct {

	ShaderProgramPtr program;
	std::vector<TexturePtr> input_textures;
	std::function<void (ShaderProgramPtr)> pre_draw;
	glhelper::Pass pass;

} PostProcessorPass;

class PostProcessor {

	public:

		PostProcessor(FramebufferConfig config) {

			framebuffer_ = FramebufferPtr(

				new Framebuffer(

					config

				)

			);

			pipeline_ = glhelper::PassPipelinePtr(

				new glhelper::PassPipeline(

					framebuffer_

				)

			);

			view_mesh_ = glshape::plane::Create(2, 2);

		};

		void UpdatePasses(std::vector<PostProcessorPass>);
		void Run(void) const;

		FramebufferPtr framebuffer_;

	private:
		
		TexturePtr progress_;
		glhelper::PassPipelinePtr pipeline_;
		MeshPtr view_mesh_;

};

typedef std::shared_ptr<PostProcessor> PostProcessorPtr;

} // namespace gl

#endif // GL_POST_PROCESSOR_H_