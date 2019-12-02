
#include "cone.h"

namespace glshape {
namespace cone {

float CalculateTaper(int index, int segments, float taper) {

	return 1.0f - (((float)index/(float)segments) * (1.0f - taper));

}

gl::MeshPtr Create(
	int res,
	float height,
	float taper,
	int segments

) {

	auto mesh = gl::MeshPtr(
		
		new gl::Mesh()
	
	);

	mesh->mode_ = GL_TRIANGLES;

	mesh->Update(

		[
			res,
			height,
			taper,
			segments

		](gl::BufferPtrs& buffers) {

			std::vector<float> vertices;
			std::vector<int> indices;

			float segment_height = height/(float)segments;

			for(int i = 0; i < segments; i++) {

				float seg_taper = CalculateTaper(i, segments, taper);

				cylinder::Buffer band = cylinder::CreateBand(

					glm::vec3(0, 0, (float)i * segment_height),
					glm::vec2(seg_taper), 
					res, 
					segment_height,
					CalculateTaper(i + 1, segments, taper) / seg_taper,
					i

				);

				vertices.insert(vertices.end(), band.vertices.begin(), band.vertices.end());
				indices.insert(indices.end(), band.indices.begin(), band.indices.end());

			}

			auto vertex_buffer = gl::BufferPtr(
				new gl::Buffer(GL_ARRAY_BUFFER)
			);

			vertex_buffer->InitData(
				(gl::BufferConfig) {
					.usage = GL_STATIC_DRAW,
					.bytes = (GLsizeiptr)(sizeof(float) * vertices.size()),
					.size = (GLsizei)(vertices.size()),
					.data = &vertices[0]
				}
			);

			auto index_buffer = gl::BufferPtr(
				new gl::Buffer(GL_ELEMENT_ARRAY_BUFFER)
			);

			index_buffer->InitData(
				(gl::BufferConfig) {
					.usage = GL_STATIC_DRAW,
					.bytes = (GLsizeiptr)(sizeof(int) * indices.size()),
					.size = (GLsizei)(indices.size()),
					.data = &indices[0]
				}
			);

			buffers.push_back(vertex_buffer);
			buffers.push_back(index_buffer);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));

		}

	);

	return mesh;

}


} // namespace cone
} // namespace glshape