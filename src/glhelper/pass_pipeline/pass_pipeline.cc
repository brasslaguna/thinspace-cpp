
#include "pass_pipeline.h"

namespace glhelper {

static void Clear(glm::vec3 color) {

 	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

static GLenum GetVacantAttachment(std::set<GLenum>& reserved) {

	auto available = GL_COLOR_ATTACHMENT0;

	for(const auto& id : reserved)

		if(id == available)

			available++;

	reserved.insert(

		available

	);

	return available;

}

void PassPipeline::Add(std::map<std::string, Pass> passes) {

	std::set<GLenum> reserved_attachments;

	for(auto i = passes_.begin(); i != passes_.end();) {

		reserved_attachments.insert(

			i->attachment_id

		);

		if(passes.find(i->texture_config.name) != passes.end()) {
			
			i = passes_.erase(i);

		} else {

			i++;

		}

	}

	for(const auto& item : passes) {

		auto pass = item.second;
		auto name = item.first;
		auto& texture_config = pass.texture_config;

		auto attachment = GetVacantAttachment(

			reserved_attachments

		);

		if(texture_config.format == GL_DEPTH_COMPONENT)

			attachment = GL_DEPTH_ATTACHMENT;

		pass.name = name;
		pass.attachment_id = attachment;
		texture_config.name = name;

		framebuffer_->CreateBuffer(

			texture_config

		);

		framebuffer_->Attach(

			name,
			texture_config.target,
			attachment

		);

		passes_.push_back(pass);

	}

}

void PassPipeline::Run(glm::vec3 clear_color) const {

	if(framebuffer_ == NULL)

		return;

	framebuffer_->Bind();

	auto payload = (Payload) {

		.framebuffer = framebuffer_

	};

	for(const auto& pass : passes_ ) {

		const GLenum attachments[1] = { pass.attachment_id };
		glDrawBuffers(1, attachments);

		Clear(clear_color);

		payload.attachment_id = pass.attachment_id;
		payload.name = pass.name;

		for(const auto& iteration : pass.iterations) {

			auto draw = iteration.draw;

			if(draw == NULL)
				
				continue;

			draw(payload);

		}

	}

}

} // namespace glhelper