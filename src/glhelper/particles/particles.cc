
#include "particles/particles.h"

namespace karma {

void Particles::Init(void) {

	glGenVertexArrays(1, &vertex_attribute_id_);
	glBindVertexArray(vertex_attribute_id_);

	particles_.reserve(config_.total);

	gl::BufferPtr instance_buffer = instance_buffers_.back();

	instance_buffer->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));

	particle_buffer_.InitData(

		(gl::BufferConfig) {

			.bytes = (GLsizeiptr)(
				config_.total * sizeof(ParticleBufferArray)
			),

			.usage = GL_STREAM_DRAW

		}

	);

	GLuint index = 3;

	for(auto item : kParticleAttribPointerInitMap) {

		auto size = item.first;
		auto offset = item.second;

		particle_buffer_.Bind();

		glEnableVertexAttribArray(index);

		glVertexAttribPointer(
			index,
			size,
			GL_FLOAT,
			GL_FALSE,
			sizeof(ParticleBufferArray),
			offset
		);

		glVertexAttribDivisor(index, 1);

		index++;

	}

	ParticleBuffer buffer;

	buffer.reserve(config_.total);

	for(int i = 0; i < config_.total; i++) {

		Particle particle;

		particle.transformation.scale_ = glm::vec3(1.0f);

		particles_.push_back(particle);

		buffer.push_back(

			(ParticleBufferArray) {

				.offset = particles_[i].transformation.translation_,
				.rotation = particles_[i].transformation.rotation_,
				.scale = particles_[i].transformation.scale_,

			}

		);

	}

	glBindVertexArray(vertex_attribute_id_);

	particle_buffer_.UpdateData(

		(gl::BufferConfig) {

			.size = (GLsizei)buffer.size(),

			.bytes = (GLsizeiptr)(
				buffer.size() * sizeof(ParticleBufferArray)
			),

			.offset = 0,

			.data = (!buffer.size()) ? NULL : &buffer[0]

		}

	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Particles::Update(std::function<void (Particle& particle, int index)> callback) {

	ParticleBuffer buffer;

	buffer.reserve(config_.total);

	for(int i = 0; i < config_.total; i++) {

		callback(particles_[i], i);

		buffer.push_back(

			(ParticleBufferArray) {

				.offset = particles_[i].transformation.translation_,
				.rotation = particles_[i].transformation.rotation_,
				.scale = particles_[i].transformation.scale_

			}

		);

	}

	glBindVertexArray(vertex_attribute_id_);

	particle_buffer_.UpdateData(

		(gl::BufferConfig) {

			.size = (GLsizei)buffer.size(),

			.bytes = (GLsizeiptr)(
				buffer.size() * sizeof(ParticleBufferArray)
			),

			.offset = 0,

			.data = (!buffer.size()) ? NULL : &buffer[0]

		}
		
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Particles::Draw(GLenum mode, DrawCallback draw) {

	auto payload = (Payload) {

		.matrix = transformation_.Matrix(),
		.total = (int)particles_.size()

	};

	glBindVertexArray(vertex_attribute_id_);

	draw(payload);

	instance_buffers_.back()->DrawInstanced(mode, config_.total);

	glBindVertexArray(0);

}

} // namespace karma