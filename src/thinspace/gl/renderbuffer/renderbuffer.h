
#ifndef THINSPACE_GL_RENDERBUFFER_H_
#define THINSPACE_GL_RENDERBUFFER_H_

#include <memory>

namespace gl {

typedef struct {

	std::string name;
	GLenum internal_format;
	int width;
	int height;

} RenderbufferConfig;

class Renderbuffer {

	public:

		Renderbuffer(RenderbufferConfig config) {

			glGenRenderbuffers(1, &id_);
			Bind();

			glRenderbufferStorage(

				GL_RENDERBUFFER, 
				config.internal_format, 
				config.width, 
				config.height

			);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);

		};

		~Renderbuffer(void) {

			glDeleteRenderbuffers(1, &id_);

		};

		void Bind(void) {

			glBindRenderbuffer(GL_RENDERBUFFER, id_);

		}

		GLuint Id(void) {

			return id_;

		}

	private:
		
		GLuint id_;

};

typedef std::shared_ptr<Renderbuffer> RenderbufferPtr;

} // namespace gl

#endif // THINSPACE_GL_RENDERBUFFER_H_