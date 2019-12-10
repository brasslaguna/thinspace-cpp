
#include "framebuffer.h"

namespace gl {

GLenum Framebuffer::GetStatus(void) {

	Bind();

	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch(status) {

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:

			std::cerr << "Framebuffer incomplete attachment." << std::endl;
			
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			
			std::cerr << "Framebuffer incomplete missing attachment." << std::endl;
			
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED:

			std::cerr << "Framebuffer unsupported." << std::endl;

	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return status;

}

void Framebuffer::CreateBuffer(RenderbufferConfig config) {

	config.width = config_.width;
	config.height = config_.height;

	buffers_.insert(

		std::pair<std::string, RenderbufferPtr> (

			config.name,

			RenderbufferPtr(

				new Renderbuffer(config)

			)

		)

	);

}

void Framebuffer::CreateBuffer(TextureConfig config) {

	config.width = config_.width;
	config.height = config_.height;

	TexturePtr texture(

		new Texture(config)

	);

	if(config.target == GL_TEXTURE_CUBE_MAP) {

		texture->CreateCubeMap(0);

	} else {

		texture->CreateImage(0);

	}

	textures_.insert(

		std::pair<std::string, TexturePtr> (

			config.name,
			texture
		
		)
	
	);

}

bool Framebuffer::Attach(std::string name, GLenum renderbuffer_target, GLenum attachment) {

	switch(renderbuffer_target) {

		case GL_RENDERBUFFER: {

			auto item = buffers_.find(name);

			if(item != buffers_.end()) {

				Bind();

				glFramebufferRenderbuffer(

					GL_FRAMEBUFFER, 
					attachment, 
					GL_RENDERBUFFER, 
					item->second->Id()

				);

			}

		} 

		break;

		default: {

			auto item = textures_.find(name);

			if(item != textures_.end()) {

				Bind();

				glFramebufferTexture2D(

					GL_FRAMEBUFFER,
					attachment,
					GL_TEXTURE_2D,
					item->second->Id(),
					0

				);

			}

		}

	}

	return GetStatus() == GL_FRAMEBUFFER_COMPLETE;

}

std::shared_ptr<void> Framebuffer::Get(std::string name, GLenum renderbuffer_target) {

	switch(renderbuffer_target) {

		case GL_RENDERBUFFER: {

			auto item = buffers_.find(name);

			if(item != buffers_.end())

				return item->second;

			break;

		}

		default: {

			auto item = textures_.find(name);

			if(item != textures_.end())

				return item->second;

		}

	}

	return NULL;
}

void Framebuffer::Bind(void) {

	glBindFramebuffer(GL_FRAMEBUFFER, id_);

}

GLuint Framebuffer::Id(void) const {

	return id_;

}

} // namespace gl
