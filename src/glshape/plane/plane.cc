
#include "plane.h"

namespace glshape {
namespace plane {

void Generate(
	int resolution_x, 
	int resolution_y, 
	float* vertices, 
	int* indices, 
	const std::function<void (int index, int x, int y, int size, int vertex_size, float* vertices)> callback
	) {

	int indices_index = 0;

	int size = resolution_x * resolution_y;

	for(int i = 0; i < size; i++) {

		auto index = i * kVertexSize;

		int x = i % resolution_x;
		int y = i / resolution_y;

		auto x_clamp = (((float)x / (float)(resolution_x - 1)) - 0.5f) * 2.0f;
		auto y_clamp = (((float)y / (float)(resolution_y - 1)) - 0.5f) * 2.0f;

		// position
		vertices[index] = x_clamp;
		vertices[index+1] = y_clamp;
		vertices[index+2] = 0.0f;

		// normal
		vertices[index+3] = 0.0f;
		vertices[index+4] = 0.0f;
		vertices[index+5] = 0.0f;

		// texture
		vertices[index+6] = (float)x / (float)(resolution_x - 1);
		vertices[index+7] = (float)y / (float)(resolution_y - 1);

		// tangent
		vertices[index+8] = 0.0f;
		vertices[index+9] = 0.0f;
		vertices[index+10] = 0.0f;

		// bitangent
		vertices[index+11] = 0.0f;
		vertices[index+12] = 0.0f;
		vertices[index+13] = 0.0f;

		if(x != resolution_x - 1 && y != resolution_y - 1) {

			indices[indices_index] = resolution_x * y + x;
			indices[indices_index+1] = resolution_x * y + x + resolution_x;
			indices[indices_index+2] = resolution_x * y + x + resolution_x + 1;
			indices[indices_index+3] = indices[indices_index];
			indices[indices_index+4] = indices[indices_index+2];
			indices[indices_index+5] = resolution_x * y + x + 1;

			indices_index += 6;
		}
	}

	if(callback)

		for(int i = 0; i < size; i++) {

			auto index = i * kVertexSize;

			int x = i % resolution_x;
			int y = i / resolution_y;

			callback(
				index,
				x,
				y,
				size,
				kVertexSize,
				vertices
			);

		}
}

gl::MeshPtr Create(
	int resolution_x, 
	int resolution_y, 
	const std::function<void (int index, int x, int y, int size, int vertex_size, float* vertices)> callback
	) {

	auto mesh = gl::MeshPtr(
		new gl::Mesh()
	);

	mesh->mode_ = GL_TRIANGLES;

	mesh->Update(
		[
			resolution_x, 
			resolution_y,
			callback
		]
			(gl::BufferPtrs& buffers) {

				float vertices[resolution_x * resolution_y * kVertexSize];
				int indices[(resolution_x - 1) * (resolution_y - 1) * 6];

				Generate(
					resolution_x, 
					resolution_y, 
					vertices, 
					indices, 
					callback
				);

				auto vertex = gl::BufferPtr(
					new gl::Buffer(GL_ARRAY_BUFFER)
				);

				vertex->InitData(
					(gl::BufferConfig) {

						.data = vertices,
						.size = resolution_x * resolution_y,
						.bytes = (GLsizeiptr)(sizeof(vertices)),
						.usage = GL_STATIC_DRAW
						
					}
				);

				buffers.push_back(vertex);

				auto index = gl::BufferPtr(
					new gl::Buffer(GL_ELEMENT_ARRAY_BUFFER)
				);

				index->InitData(
					(gl::BufferConfig) {
						
						.data = indices,
						.size = (resolution_x - 1) * (resolution_y - 1) * 6,
						.bytes = (GLsizeiptr)(sizeof(indices)),
						.usage = GL_STATIC_DRAW
						
					}
				);

				buffers.push_back(index);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * kVertexSize, (GLvoid*)0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * kVertexSize, (GLvoid*)(3 * sizeof(float)));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * kVertexSize, (GLvoid*)(6 * sizeof(float)));

				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * kVertexSize, (GLvoid*)(8 * sizeof(float)));

				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * kVertexSize, (GLvoid*)(11 * sizeof(float)));
			}
	);

	return mesh;

}

} // namespace plane
} // namespace glshape
