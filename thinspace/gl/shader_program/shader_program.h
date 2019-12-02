
#ifndef GL_SHADER_PROGRAM_H_
#define GL_SHADER_PROGRAM_H_

#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <iostream>
#include <cstdio>

#include <gllib/gllib.h>

#include "shader/shader.h"

namespace gl {

typedef struct {

	std::string name;
	std::string vertex_shader_name;
	std::string geometry_shader_name;
	std::string fragment_shader_name;

} ShaderProgramConfig;

typedef struct {

	GLint id;
	GLenum type;

} Uniform;

class ShaderProgram {

	public:

		ShaderProgram() {

			id_ = glCreateProgram();

		};

		~ShaderProgram() {

			glDeleteProgram(id_);

		};

		void Attach(const Shader& shader);
		void Use(void) const;
		void Link(void) const;
		void GetUniforms(void);
		GLuint Id(void) const;
		void SetUniform(const std::string& name, const GLfloat*);
		void SetUniform(const std::string& name, GLfloat value);
		void SetUniform(const std::string& name, const GLuint value);

	private:

		GLuint id_;
		std::map<std::string, Uniform> uniforms_;
		
};

typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

} // namespace gl

#endif