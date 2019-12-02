
#include "sphere.h"

namespace glshape {
namespace sphere {

gl::MeshPtr Create(int res_x, int res_y) {

	auto mesh = gl::MeshPtr(
		
		new gl::Mesh()
	
	);

	mesh->mode_ = GL_TRIANGLES;

	mesh->Update(

		[
			res_x,
			res_y

		](gl::BufferPtrs& buffers) {

			std::vector<float> vertices;
			std::vector<int> indices;

			int index = 0;
			std::vector<int> index_rows;
			std::vector<int> grid;

			const float kTheta = M_PI,
						kPhi = M_PI * 2.0f;

			for(int i = 0; i <= res_x; i++) {

				index_rows.clear();

				float y = (float)i / (float)res_y;

				for(int j = 0; j <= res_x; j++) {

					float x = (float)j / (float)res_x,
						  x_progress = x * kPhi,
						  y_progress = y * kTheta;

					std::vector<float> vertex {

						-cosf(x_progress) * sinf(y_progress),
						cosf(y_progress),
						sinf(x_progress) * sinf(y_progress)

					};

					vertices.insert(vertices.end(), vertex.begin(), vertex.end());
					vertices.insert(vertices.end(), vertex.begin(), vertex.end());

					vertices.push_back(x);
					vertices.push_back(y);

					index_rows.push_back(index++);

				}

				grid.insert(grid.begin(), index_rows.begin(), index_rows.end());

			}

			for(int i = 0; i <= res_y; i++) {

				int row = i * res_y;

				for(int j = 0; j <= res_x; j++) {

					int a, b, c, d;

					a = grid[row + j + 1];
					b = grid[row + j];
					c = grid[(row + res_y) + j];
					d = grid[(row + res_y) + j + 1];

					if(i != 0)

						indices.insert(indices.end(), { a, b, d });

					indices.insert(indices.end(), { b, c, d });

				}

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
 
} // namespace sphere
} // namespace glshape