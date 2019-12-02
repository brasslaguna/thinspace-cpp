
#ifndef SCENE_COMPONENT_H_
#define SCENE_COMPONENT_H_

#include <functional>

namespace gl {

template <class ComponentType>

class SceneComponent {

	protected:

		std::function<void (ComponentType&)> component_loop_;

	public:

		virtual void ComponentLoop(ComponentType& component) {

			if(component_loop_)

				component_loop_(component);

		};

		void SetComponentLoop(std::function<void (ComponentType&)> component_loop) {

			component_loop_ = component_loop;

		};

		bool component_visible = true;
		
};

} // namespace gl

#endif //SCENE_COMPONENT_H_