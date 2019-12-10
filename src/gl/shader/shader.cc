
#include "shader.h"
#include "file/file.h"

namespace gl {

bool static compile_status(const GLuint& id) {

	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if(status == GL_TRUE) {

		return true;
		
	} else {

		char buffer[512];
		glGetShaderInfoLog(id, 512, NULL, buffer);
		std::cout << buffer << std::endl;

		return false;

	}

}

bool Shader::load_file(const std::string& file_path) {

	auto file = util::file::Load(file_path);

	id_ = glCreateShader(type);

	std::string shaderSource = "#version " + std::string(DEFINE_GLSL_VERSION) + "\n" + file;

	const GLchar* buffer = shaderSource.c_str();

	glShaderSource(id_, 1, &buffer, NULL);
	glCompileShader(id_);

	return compile_status(id_);

}

GLuint Shader::id(void) const {

	return id_;
	
}

} // namespace gl