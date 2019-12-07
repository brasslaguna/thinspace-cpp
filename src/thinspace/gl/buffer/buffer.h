
#ifndef THINSPACE_GL_BUFFER_H_
#define THINSPACE_GL_BUFFER_H_

#include <cassert>
#include <memory>

#include <gllib/gllib.h>

namespace gl {

typedef struct {

	void* data;
	const GLsizei size;
	const GLsizeiptr bytes;
	const GLenum usage;
	const GLintptr offset;

} BufferConfig;

class Buffer {

	public:

		explicit Buffer(const GLenum target) : target_(target) {
			
			glGenBuffers(1, &id_);

		};

		~Buffer() {

			glDeleteBuffers(1, &id_);

		};

		void InitData(const BufferConfig& bufferConfig);
		void UpdateData(const BufferConfig& bufferConfig);
		GLsizei Size(void) const;
		void Draw(const GLenum mode) const;
		void DrawInstanced(const GLenum mode, const GLsizei instances) const;
		void Bind(void) const;

	private:

		GLsizei size_ = 0;
		GLsizeiptr bytes_;
		GLuint id_;
		GLenum target_;

};

typedef std::shared_ptr<Buffer> BufferPtr;

} // namespace gl

#endif // THINSPACE_GL_BUFFER_H_