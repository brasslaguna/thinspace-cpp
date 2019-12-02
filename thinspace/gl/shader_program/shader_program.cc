
#include "shader_program.h"

namespace gl {

const char* GLTypeToString(GLenum type) {

	switch(type) {

		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";

		default: break;
	
	}

	return "other";

}

static void PrintInfo(GLuint id) {

	std::cout << "\n--------------------\nShader Program " << id << " info:\n" << std::endl;

	int params = -1;
	glGetProgramiv(id, GL_LINK_STATUS, &params);
	std::cout << "GL_LINK_STATUS = " << params << "\n" << std::endl;

	glGetProgramiv(id, GL_ATTACHED_SHADERS, &params);
	std::cout << "GL_ATTACHED_SHADERS = " << params << "\n" << std::endl;

	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &params);
	std::cout << "GL_ACTIVE_ATTRIBUTES = " << params << "\n" << std::endl;

	for(int i = 0; i < params; i++) {

		char name[64];
		int max_length = 64, actual_length = 0, size = 0;
		GLenum type;

		glGetActiveAttrib(
			id,
			i,
			max_length,
			&actual_length,
			&size,
			&type,
			name
		);

		if(size > 1) {

			for(int j = 0; j < size; j++) {

				char long_name[64];
				sprintf(long_name, "%s[%i]", name, j);
				int location = glGetAttribLocation(id, long_name);
				printf("  %i) type:%s name:%s location:%i\n", i, GLTypeToString(type), long_name, location);
			
			}

		} else {

		  int location = glGetAttribLocation(id, name);
		  printf("  %i) type:%s name:%s location:%i\n", i, GLTypeToString(type), name, location);
		
		}
	
	}

	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &params);

	std::cout << "GL_ACTIVE_UNIFORMS = " << params << "\n" << std::endl;

	for(int i = 0; i < params; i++) {

		char name[64];
		int max_length = 64, actual_length = 0, size = 0;
		GLenum type;

		glGetActiveUniform(
		  id,
		  i,
		  max_length,
		  &actual_length,
		  &size,
		  &type,
		  name
		);

		if(size > 1) {

		  for(int j = 0; j < size; j++) {

		    char long_name[64];
		    sprintf(long_name, "%s[%i]", name, j);
		    int location = glGetUniformLocation(id, long_name);
		    printf("  %i) type:%s name:%s location:%i\n", i, GLTypeToString(type), long_name, location);
		  }

		} else {
		  
		  int location = glGetUniformLocation(id, name);
		  printf("  %i) type:%s name:%s location:%i\n", i, GLTypeToString(type), name, location);
		
		}
	
	}

	int max_length = 2048, actual_length = 0;
	char program_log[2048];

	glGetProgramInfoLog(id, max_length, &actual_length, program_log);
	printf("program info log for GL index %u:\n%s\n", id, program_log);

}

void ShaderProgram::Link(void) const {

	glLinkProgram(id_);

}

void ShaderProgram::Attach(const Shader& shader) {

	glAttachShader(id_, shader.id());

}

void ShaderProgram::Use(void) const {

	glUseProgram(id_);

}

GLuint ShaderProgram::Id(void) const {

	return id_;

}

void ShaderProgram::GetUniforms(void) {

	GLint total;
	glGetProgramiv(id_, GL_ACTIVE_UNIFORMS, &total);

	for(int i = 0; i < total; i++) {

		GLenum type = 0;
		GLchar name_c_str[256];
		GLint name_length = 0;
		GLint array_size = 0;

		glGetActiveUniform(
			id_, 
			i, 
			256, 
			&name_length, 
			&array_size, 
			&type, 
			name_c_str
		);

		if(array_size > 1) {

			auto prefix = std::string(name_c_str, name_length);
			prefix = prefix.substr(0, prefix.size() - 3);

			for(int j = 0; j < array_size; ++j) {

				auto name = prefix + "[" + std::to_string(j) + "]";

				uniforms_[name] = 
					(gl::Uniform) {
						.id = glGetUniformLocation(id_, name.c_str()),
						.type = type
					};
			}

		} else {

			auto name = std::string(name_c_str, name_length);

			uniforms_[name] = 
				(gl::Uniform) {
					.id = glGetUniformLocation(id_, name.c_str()),
					.type = type
				};

		}

	}

}

void ShaderProgram::SetUniform(const std::string& name, const GLfloat* value) {

	auto iterator = uniforms_.find(name);

	if(iterator != uniforms_.end()) {

		const auto& uniform = iterator->second;

		switch(uniform.type) {

			case GL_FLOAT_VEC4:

				glUniform4fv(uniform.id, 1, value);

				break;

			case GL_FLOAT_VEC3:

				glUniform3fv(uniform.id, 1, value);

				break;

			case GL_FLOAT_VEC2:

				glUniform2fv(uniform.id, 1, value);

				break;

			case GL_FLOAT_MAT4:

				glUniformMatrix4fv(uniform.id, 1, GL_FALSE, value);

		}

	}

}

void ShaderProgram::SetUniform(const std::string& name, GLfloat value) {

	auto iterator = uniforms_.find(name);

	if(iterator != uniforms_.end()) {

		const auto& uniform = iterator->second;

		switch(uniform.type) {

			case GL_FLOAT:

				glUniform1f(uniform.id, value);

		}

	}

}

void ShaderProgram::SetUniform(const std::string& name, const GLuint value) {

	auto iterator = uniforms_.find(name);

	if(iterator != uniforms_.end()) {

		const auto& uniform = iterator->second;

		switch(uniform.type) {

			case GL_SAMPLER_2D:

				glUniform1i(uniform.id, value);

				break;

			case GL_SAMPLER_3D:

				glUniform1i(uniform.id, value);

				break;

			case GL_SAMPLER_CUBE:

				glUniform1i(uniform.id, value);

				break;

			case GL_INT:

				glUniform1i(uniform.id, value);

				break;

			case GL_BOOL:

				glUniform1i(uniform.id, value);


		}

	}
	
}

} // namespace gl

