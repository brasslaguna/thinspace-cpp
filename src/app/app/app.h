
#ifndef THINSPACE_APP_APP_H_
#define THINSPACE_APP_APP_H_

#include "app_base/app_base.h"

namespace thinspace {

class App {

	public:

		App(char** argv) {

				auto exe_name = std::string(argv[0]);
				root_dir_ = exe_name.substr(0, exe_name.find_last_of("\\/")) + "/..";

				base_ = apphelper::AppBasePtr(

					new apphelper::AppBase(std::string(root_dir_ + "/thinspace/src"))

				);

		};

		void Draw(void);

		void Init(void);

	protected:

		apphelper::AppBasePtr base_;

		std::string root_dir_;

};

} // namespace thinspace

#endif // THINSPACE_APP_APP_H_