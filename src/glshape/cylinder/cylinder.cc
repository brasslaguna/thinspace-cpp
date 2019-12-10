
#include "cylinder.h"

namespace glshape {
namespace cylinder {

gl::MeshPtr Create(
	int res,
	float height,
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
			segments

		](gl::BufferPtrs& buffers) {

			std::vector<float> vertices;
			std::vector<int> indices;

			float segment_height = height/(float)segments;

			for(int i = 0; i < segments; i++) {

				Buffer band = CreateBand(

					glm::vec3(0, 0, (float)i * segment_height),
					glm::vec2(1.0f, 1.0f),
					res,
					segment_height,
					1.0f,
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
					
					.data = &vertices[0],
					.size = (GLsizei)(vertices.size()),
					.bytes = (GLsizeiptr)(sizeof(float) * vertices.size()),
					.usage = GL_STATIC_DRAW
					
				}
			);

			auto index_buffer = gl::BufferPtr(
				new gl::Buffer(GL_ELEMENT_ARRAY_BUFFER)
			);

			index_buffer->InitData(
				(gl::BufferConfig) {

					.data = &indices[0],
					.size = (GLsizei)(indices.size()),
					.bytes = (GLsizeiptr)(sizeof(int) * indices.size()),
					.usage = GL_STATIC_DRAW
					
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

Buffer CreateBand(
	glm::vec3 origin, 
	glm::vec2 radius, 
	int res, 
	float height,
	float taper,
	int seg_index

) {

	std::vector<float> circle;

	for(int i = 0; i < res; i++) {

		float angle = (M_PI * 2.0f) * ((float)(i)/(float)res);

		circle.insert(

			circle.end(),

			{
				origin.x + cosf(angle) * radius.x,
				origin.y + sinf(angle) * radius.y,
				origin.z
			}

		);

	}

	int total = circle.size() / 3;

	std::vector<float> vertices;
	std::vector<int> indices;
	std::vector<std::vector<int>> quad_indices;

	bool odd = total % 2 == 1;

	for(int i = 0; i < total; i += 2) {

		int index = i * 3;
		bool end = i + 2 >= total;

		std::vector<float> tl {

			circle[index],
			circle[index + 1],
			circle[index + 2]

		};

		if(end && odd) index = 0;

		std::vector<float> tr {

			circle[index + 3],
			circle[index + 4],
			circle[index + 5]

		};

		std::vector<std::vector<float>> vertex {

			tl,
			tr,
			std::vector<float> { tr[0] * taper, tr[1] * taper, tr[2] + height },
			std::vector<float> { tl[0] * taper, tl[1] * taper, tl[2] + height },

		};

		for(int j = 0; j < 4; j++) {

			std::vector<float> end;

			switch(j) {

				case 0:

					end.insert(end.end(), { (float)i/(float)total, 1.0f });

					break;

				case 1:

					end.insert(end.end(), { ((float)i+1.0f)/(float)total, 1.0f });

					break;

				case 2:

					end.insert(end.end(), { ((float)i+1.0f)/(float)total, 0.0f });

					break;

				case 3:

					end.insert(end.end(), { (float)i/(float)total, 0.0f });

					break;

			}

			vertices.insert(

				vertices.end(),

				{
					vertex[j][0], vertex[j][1], vertex[j][2],
					vertex[j][0], vertex[j][1], vertex[j][2],
					end[0],
					end[1]
				}

			);

		}

		index = (i/2) * 4;

		index += (int)(ceil(total/2.0f) * 4.0f) * seg_index;

		quad_indices.insert(

			quad_indices.end(),

			std::vector<int> { index, index + 1, index + 2, index + 2, index + 3, index }

		);

	}

	for(int i = 0; i < total; i++) {

		bool even = i % 2 == 0,
			 end = i == total - 1;

		if(even && !end) {

			indices.insert(

				indices.end(), 
				quad_indices[i/2].begin(),
				quad_indices[i/2].end()

			);

			continue;
		
		}

		if(!even || end) {

			int index = (i - 1)/2;

			std::vector<int> pre, quad;

			if(end) {

				pre.insert(pre.end(), indices.end() - 6, indices.end());
				
				quad = quad_indices[0];

			} else {

				pre = quad_indices[index];

				quad = quad_indices[index + 1];

			}

			indices.insert(

				indices.end(),

				{ pre[1], quad[0], quad[4], quad[4], pre[2], pre[1] }

			);

		}

	}

	return (Buffer) {

		.vertices = vertices,
		.indices = indices

	};

}


} // namespace glshape
} // namespace cylinder