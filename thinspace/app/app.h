
#ifndef APP_APP_H_
#define APP_APP_H_

#define GLM_ENABLE_EXPERIMENTAL

#include "app_base/app_base.h"

namespace thinspace {

class App {

	public:

		App(char** argv) {

				auto exe_name = std::string(argv[0]);
				root_dir_ = exe_name.substr(0, exe_name.find_last_of("\\/")) + "/..";

				base_ = apphelper::AppBasePtr(

					new apphelper::AppBase(root_dir_ + "/thinspace")

				);

				Init();

		};

		void Draw(void);

	private:

		apphelper::AppBasePtr base_;

		std::string root_dir_;

		float animation_time_ = 0.0f;

		void Init(void);

};

} // namespace thinspace

#endif // APP_APP_H_