
#ifndef THINSPACE_GL_MESH_H_
#define THINSPACE_GL_MESH_H_

#include <functional>
#include <vector>
#include <memory>

#include <gllib/gllib.h>

#include "buffer/buffer.h"

namespace gl {

typedef std::vector<BufferPtr> BufferPtrs;
typedef std::function<void (BufferPtrs&)> UpdateCall;

class Mesh {

	public:

		~Mesh() {

			glDeleteVertexArrays(1, &vertex_attribute_id_);

		};

		void Draw();
		void DrawInstanced(const GLsizei instances);
		void Update(UpdateCall update_call);
		BufferPtrs buffers_;
		GLenum mode_;

	private:

		GLuint vertex_attribute_id_;

};

typedef std::shared_ptr<Mesh> MeshPtr;

} // namespace gl

#endif // THINSPACE_GL_MESH_H_