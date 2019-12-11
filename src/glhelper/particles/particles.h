
#ifndef THINSPACE_GL_PARTICLES_H_
#define THINSPACE_GL_PARTICLES_H_

#include <functional>
#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>

#include "transformation/transformation.h"
#include "buffer/buffer.h"

namespace gl {

typedef std::vector<BufferPtr> BufferPtrs;

typedef struct {

	int total;
	BufferPtrs instance_buffers;

} ParticlesConfig;

typedef struct {

	Transformation transformation;

} Particle;

typedef struct {

	glm::vec3 offset;
	glm::vec3 rotation;
	glm::vec3 scale;

} ParticleBufferArray;

typedef std::vector<ParticleBufferArray> ParticleBuffer;

const std::vector<std::pair<GLuint, GLvoid*>> kParticleAttribPointerInitMap = {

	{3, (GLvoid*)offsetof(ParticleBufferArray, offset)},
	{3, (GLvoid*)offsetof(ParticleBufferArray, rotation)},
	{3, (GLvoid*)offsetof(ParticleBufferArray, scale)}

};

typedef struct {

	glm::mat4 matrix;
	int total;

} Payload;

typedef std::function<void (Payload)> DrawCallback;

class Particles {

	public:

		Particles(ParticlesConfig config) :
			config_(config),
			particle_buffer_(GL_ARRAY_BUFFER) {

				instance_buffers_ = config.instance_buffers;

				Init();

			};

		~Particles() {

			glDeleteVertexArrays(1, &vertex_attribute_id_);
			
		};

		void Update(std::function<void (Particle& particle, int index)> callback);
		void Draw(GLenum mode, DrawCallback draw);

		gl::Transformation transformation_;

	private:

		void Init(void);

		ParticlesConfig config_;
		std::vector<Particle> particles_;
		Buffer particle_buffer_;
		BufferPtrs instance_buffers_;
		GLuint vertex_attribute_id_;

};

typedef std::shared_ptr<Particles> ParticlesPtr;

} // namespace gl

#endif // THINSPACE_GL_PARTICLES_H_