
#ifdef INCLUDE_GL_PI_4

#ifndef THINSPACE_CONTEXT_DRM_CONTEXT_H_
#define THINSPACE_CONTEXT_DRM_CONTEXT_H_

namespace context {

class DRMContext {

	public:

		void Init(void);
		void SwapBuffers(void);

};

} // namespace context

#endif // THINSPACE_CONTEXT_DRM_CONTEXT_H_

#endif // INCLUDE_GL_PI_4