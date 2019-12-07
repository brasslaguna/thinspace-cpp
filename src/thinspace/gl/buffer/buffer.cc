
#include "buffer.h"

namespace gl {

void Buffer::InitData(const BufferConfig& bufferConfig) {

	size_ = bufferConfig.size;
	bytes_ = bufferConfig.bytes;

	Bind();

	glBufferData(
		target_, 
		bytes_, 
		bufferConfig.data, 
		bufferConfig.usage
	);

}

void Buffer::UpdateData(const BufferConfig& bufferConfig) {
	
	if(bufferConfig.size || bufferConfig.size == 0)

		size_ = bufferConfig.size;

	if(bufferConfig.bytes || bufferConfig.bytes == 0)

		bytes_ = bufferConfig.bytes;

	Bind();

	glBufferSubData(
		target_, 
		bufferConfig.offset, 
		bytes_, 
		bufferConfig.data
	);

}

void Buffer::Draw(const GLenum mode) const {

	switch(target_) {

		case GL_ARRAY_BUFFER:

			Bind();

			glDrawArrays(mode, 0, size_);

			break;

		case GL_ELEMENT_ARRAY_BUFFER:

			Bind();

			glDrawElements(mode, size_, GL_UNSIGNED_INT, 0);

			break;

		default:

			assert(false);

	}

}

void Buffer::DrawInstanced(const GLenum mode, const GLsizei instances) const {

	switch(target_) {

		case GL_ARRAY_BUFFER:

			Bind();

			glDrawArraysInstanced(mode, 0, size_, instances);

			break;
		
		case GL_ELEMENT_ARRAY_BUFFER:

			Bind();

			glDrawElementsInstanced(mode, size_, GL_UNSIGNED_INT, 0, instances);

			break;

		default:

			assert(false);

	}

}

GLsizei Buffer::Size(void) const {

	return size_;

}

void Buffer::Bind(void) const {

	glBindBuffer(target_, id_);
	
}

} // namespace gl