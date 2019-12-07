
#include "texture.h"

namespace gl {

void Texture::SetParameters(void) const {

	for(const auto parameteri : config_.parametersi)

		glTexParameteri(config_.target, parameteri.first, parameteri.second);

	for(const auto parameterfv : config_.parametersfv)

		glTexParameterfv(config_.target, parameterfv.first, parameterfv.second);

}

bool Texture::LoadImage(const std::string& file_path, GLenum target) {

	util::Image image;

	if(image.load(file_path)) {

		Bind();
		SetParameters();

		glTexImage2D(

			target,
			0,
			GL_RGBA,
			image.width(),
			image.height(),
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.bitmap32()

		);

		return true;

	} else {

		return false;

	}

}

void Texture::CreateImage(const GLvoid* buffer) {

	Bind();
	SetParameters();

	glTexImage2D(

		config_.target,
		0,
		config_.internal_format,
		config_.width,
		config_.height,
		0,
		config_.format,
		config_.pixel_type,
		buffer

	);

}

void Texture::CreateCubeMap(const GLvoid* buffer) {

	Bind();
	SetParameters();

	for(GLuint i = 0; i < 6; ++i)

		glTexImage2D(

			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			config_.internal_format,
			config_.width,
			config_.height,
			0,
			config_.format,
			config_.pixel_type,
			buffer

		);


}

void Texture::UpdateImage(TextureUpdateConfig config) {

	Bind();

	glTexSubImage2D(

		config_.target,
		0,
		config.x,
		config.y,
		config.width,
		config.height,
		config_.format,
		config_.pixel_type,
		config.buffer

	);

}

GLuint Texture::Id(void) const {

	return id_;

}

void Texture::Bind(void) const {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(config_.target, id_);

}

void Texture::Bind(GLuint unit) const {

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(config_.target, id_);
	
}

} // namespace gl