
#ifdef INCLUDE_GL_PI_4

#ifndef CONTEXT_DRM_CONTEXT_H_
#define CONTEXT_DRM_CONTEXT_H_

namespace context {

class DRMContext {

	public:

		void Init(void);
		void SwapBuffers(void);

};

} // namespace context

#endif // CONTEXT_DRM_CONTEXT_H_

#endif // INCLUDE_GL_PI_4