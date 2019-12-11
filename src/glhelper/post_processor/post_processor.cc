
#include "post_processor.h"

namespace gl {

static void LoadInputTextures(ShaderProgramPtr program, std::vector<TexturePtr> textures, int offset) {

	for(unsigned int i = 0; i < textures.size(); i++) {

		auto texture = textures[i];
		GLuint index = i + offset;

		texture->Bind(index);

		program->SetUniform(

			"texture" + std::to_string(index),

			index

		);

	}

}

static void Prepare(PostProcessorPass pass, gl::TexturePtr previous_texture) {

	auto program = pass.program;
	auto pre_draw = pass.pre_draw;
	int texture_index_offset = 0;

	if(pre_draw != NULL)

		pre_draw(program);

	if(previous_texture != NULL) {

		previous_texture->Bind();

		program->SetUniform(

			"texture0",

			(GLuint)0

		);

		texture_index_offset++;

	}

	LoadInputTextures(

		program,
		pass.input_textures,
		texture_index_offset

	);

}

static TextureConfig CreateAttachmentConfig(std::string name) {

	return (gl::TextureConfig) {

		.name = name,
		.target = GL_TEXTURE_2D,
		.internal_format = GL_RGBA,
		.format = GL_RGBA,
		.pixel_type = GL_UNSIGNED_BYTE,

		.parametersi = (TextureParametersi) {

			{ GL_TEXTURE_MAG_FILTER, GL_NEAREST },
			{ GL_TEXTURE_MIN_FILTER, GL_NEAREST },
			{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE },
			{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE }

		}

	};

}

void PostProcessor::UpdatePasses(std::vector<PostProcessorPass> passes) {

	int index = 0;
	auto self = this;

	for(auto& item : passes) {

		auto& pass = item.pass;
		bool end = index == passes.size() - 1;

		pass.texture_config = CreateAttachmentConfig(

			pass.name
		
		);

		pass.iterations = {

			{
				.draw =
					[
						item, 
						self,
						end
					]
						(glhelper::Payload payload) {

							Prepare(item, self->progress_);

							self->view_mesh_->Draw();

							self->progress_ = 

								std::static_pointer_cast<gl::Texture>(

									payload.framebuffer->Get(

										payload.name,
										GL_TEXTURE_2D

									)

								);

							if(end)

								self->progress_ = 0;

						}
			}

		};

		pipeline_->Add({

			{
				"pass" + std::to_string(index),

				pass
			}

		});

		index++;

	}

}

void PostProcessor::Run(void) const {

	pipeline_->Run(glm::vec3());

}

} // namespace gl