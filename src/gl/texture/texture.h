
#ifndef THINSPACE_GL_TEXTURE_H_
#define THINSPACE_GL_TEXTURE_H_

#include <memory>
#include <map>

#include <gllib/gllib.h>
#include "image/image.h"

namespace gl {

typedef std::map<GLenum, GLint> TextureParametersi;
typedef std::map<GLenum, GLfloat*> TextureParametersfv;

typedef struct {

	std::string name;
	GLenum target;
	GLenum internal_format;
	GLenum format;
	GLsizei width;
	GLsizei height;
	GLenum pixel_type;
	TextureParametersi parametersi;
	TextureParametersfv parametersfv;

} TextureConfig;

typedef struct {

	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLvoid* buffer;

} TextureUpdateConfig;

class Texture {

	public:

		Texture(TextureConfig config) : config_(config) {

		  	glGenTextures(1, &id_);

		};

		~Texture() {

			glDeleteTextures(1, &id_);

		};

		bool LoadImage(const std::string& file_path, GLenum target);
		void CreateImage(const GLvoid* buffer);
		void CreateCubeMap(const GLvoid* buffer);
		void UpdateImage(TextureUpdateConfig config);
		GLuint Id(void) const;
		void Bind(void) const;
		void Bind(GLuint unit) const;

		TextureConfig config_;

	private:

		void SetParameters(void) const;
		GLuint id_;
		
};

typedef std::shared_ptr<Texture> TexturePtr;

} // namespace gl

#endif // THINSPACE_GL_TEXTURE_H_