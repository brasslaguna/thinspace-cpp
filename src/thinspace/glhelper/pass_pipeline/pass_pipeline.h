
#ifndef THINSPACE_GLHELPER_PASS_PIPELINE_H_
#define THINSPACE_GLHELPER_PASS_PIPELINE_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <memory>

#include <glm/vec3.hpp>

#include "framebuffer/framebuffer.h"
#include "shader_program/shader_program.h"

namespace glhelper {

typedef struct {

	std::string name;
	gl::ShaderProgramPtr program;
	gl::FramebufferPtr framebuffer;
	GLenum attachment_id;

} Payload;

typedef struct {

	gl::ShaderProgramPtr program;
	std::function<void (Payload)> draw;

} ProgramIteration;

typedef struct {

	std::string name;
	gl::TextureConfig texture_config;
	GLenum attachment_id;
	std::vector<ProgramIteration> iterations;

} Pass;

class PassPipeline {

	public:

		PassPipeline(gl::FramebufferPtr framebuffer)
			: framebuffer_(framebuffer) {};

		void Add(std::map<std::string, Pass>);
		void Run(glm::vec3 clear_color) const;

	private:
		
		gl::FramebufferPtr framebuffer_;
		std::vector<Pass> passes_;

};

typedef std::shared_ptr<PassPipeline> PassPipelinePtr;

} // namespace glhelper

#endif // THINSPACE_GLHELPER_PASS_PIPELINE_H_