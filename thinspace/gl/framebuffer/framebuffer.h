
#ifndef GL_FRAMEBUFFER_H_
#define GL_FRAMEBUFFER_H_

#include <string>
#include <memory>
#include <map>
#include <iostream>

#include <gllib/gllib.h>

#include "renderbuffer/renderbuffer.h"
#include "texture/texture.h"

namespace gl {

typedef struct {

	std::string name;
	int width;
	int height;

} FramebufferConfig;

typedef std::map<std::string, RenderbufferPtr> RenderbufferMap;
typedef std::map<std::string, TexturePtr> TextureMap;

class Framebuffer {

	public:

		Framebuffer(FramebufferConfig config) : config_(config)  {

				glGenFramebuffers(1, &id_);

		};

		~Framebuffer() {

			glDeleteFramebuffers(1, &id_);

		};

		bool Attach(std::string name, GLenum renderbuffer_target, GLenum attachment);
		void CreateBuffer(RenderbufferConfig config);
		void CreateBuffer(TextureConfig config);
		std::shared_ptr<void> Get(std::string name, GLenum renderbuffer_target);
		void Bind(void);
		GLenum Statu(void);
		GLuint Id(void) const;
		GLenum Attachment(void) const;

		FramebufferConfig config_;

	private:

		GLuint id_;

		RenderbufferMap buffers_;
		TextureMap textures_;
		
};

typedef std::shared_ptr<Framebuffer> FramebufferPtr;

} // namespace gl

#endif // GL_FRAME_BUFFER_H_
