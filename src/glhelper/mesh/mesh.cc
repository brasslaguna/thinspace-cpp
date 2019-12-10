
#include "mesh.h"

namespace gl {

void Mesh::Draw(void) {

	if(!buffers_.size())

		return;

	auto buffer = buffers_.back();

	glBindVertexArray(vertex_attribute_id_);

	buffer->Draw(mode_);

	glBindVertexArray(0);

}

void Mesh::DrawInstanced(const GLsizei instances) {

	if(!buffers_.size())

		return;

	auto buffer = buffers_.back();

	buffer->DrawInstanced(mode_, instances);

}

void Mesh::Update(UpdateCall update_call) {

	if(!buffers_.size())
		
		glGenVertexArrays(1, &vertex_attribute_id_);

	glBindVertexArray(vertex_attribute_id_);

	update_call(buffers_);
	
	glBindVertexArray(0);
}

} // namespace gl