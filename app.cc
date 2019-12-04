
#include "app.h"

#include "plane/plane.h"

namespace thinspace {

	void App::Init(void) {
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		int width, height;

		base_->GetViewportSize(width, height);

		auto scene_main = base_->Create((gl::SceneConfig) {

			.name = "main",
			.clear_color = glm::vec3(1.0f, 0.55f, 0.67f),
			.width = width,
			.height = height

		});

		auto plane_model = base_->Create(

			(gl::ModelConfig) {

				.name = "plane"
			
			}

		);

		plane_model->transformation_.scale_ = glm::vec3(0.3f, 0.3f, 0.3f);

		plane_model->meshes_.insert(

			{
				"plane",
				glshape::plane::Create(2, 2)
			}

		);

		base_->Create((gl::ShaderConfig) {

			.name = "dot_fragment",
			.file_path = root_dir_ + "/shader/dot/fragment.glsl",
			.type = GL_FRAGMENT_SHADER

		});

		base_->Create((gl::ShaderConfig) {

			.name = "dot_vertex",
			.file_path = root_dir_ + "/shader/dot/vertex.glsl",
			.type = GL_VERTEX_SHADER

		});

		auto dot_program = base_->Create((gl::ShaderProgramConfig) {

			.name = "dot",
			.vertex_shader_name = "dot_vertex",
			.fragment_shader_name = "dot_fragment"

		});

		scene_main->AddPasses({

			{
				"color",

				(glhelper::Pass) {

					.texture_config = {

						.name = "",
						.target = GL_TEXTURE_2D,
						.internal_format = GL_RGBA,
						.format = GL_RGBA,
						.width = width,
						.height = height,
						.pixel_type = GL_UNSIGNED_BYTE,

						.parametersi = (gl::TextureParametersi) {

							{ GL_TEXTURE_MAG_FILTER, GL_NEAREST },
							{ GL_TEXTURE_MIN_FILTER, GL_NEAREST },
							{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE },
							{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE }

						}

					},

					.iterations = {

						{
							.program = dot_program,

							.draw =
								[

									plane_model,
									width,
									height,
									this

								]
									(glhelper::Payload payload) {

										auto program = payload.program;

										program->SetUniform("time", this->animation_time_);

										program->SetUniform(

											"resolution", 

											glm::value_ptr(

												glm::vec2(width, height)

											)

										);

										plane_model->Draw(

											(gl::PreDrawMap) {

												{
													"plane",

													[
														program
													]
														(gl::ModelPayload payload) {

															program->SetUniform(

																"model",

																glm::value_ptr(

																	payload.matrix

																)

															);

														}

												}

											}

										);

									}

						}

					}

				}

			}

		});

		base_->views_ = (std::vector<apphelper::RenderViewConfig>) {

			(apphelper::RenderViewConfig) {

				.texture = std::static_pointer_cast<gl::Texture>(

					scene_main->framebuffer_->Get("color", GL_TEXTURE_2D)
				
				),

				.transformation = glm::translate(glm::vec3(0.0f)) * glm::scale(glm::vec3(1.0f))
			}
			
		};

		scene_main->SetComponentLoop(

			[

				this

			]
				(gl::Scene& scene) {

					this->animation_time_ += 0.003f;

					if(this->animation_time_ > 1.0f)

						this->animation_time_ = 0.0f;

				}

		);

	}

	void App::Draw(void) {

		base_->Render();
		
	}	

} // namespace thinspace
