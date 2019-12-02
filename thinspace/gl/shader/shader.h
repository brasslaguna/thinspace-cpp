
#ifndef GL_SHADER_H_
#define GL_SHADER_H_

#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include <gllib/gllib.h>

namespace gl {

typedef struct {

	std::string name;
	std::string file_path;
	GLenum type;

} ShaderConfig;

typedef std::map<const std::string, std::string> UniformStringMap;

class Shader {

	public:

		explicit Shader(const GLenum type) : type(type) {};

		~Shader() {

			glDeleteShader(id_);

		};

		bool load_file(const std::string& file_path);
		GLuint id(void) const;

		GLenum type;

	private:

		GLuint id_;
		
};

typedef std::shared_ptr<Shader> ShaderPtr;

} // namespace gl

#endif