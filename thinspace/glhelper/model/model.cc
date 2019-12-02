
#include "model.h"

namespace gl {

void Model::Draw(PreDrawMap pre_draw_map) {

	auto end = pre_draw_map.end();

	auto payload = (ModelPayload) {

		.matrix = transformation_.Matrix()

	};

	for(auto item : meshes_) {

		auto pre_draw = pre_draw_map.find(

			item.first

		);

		if(pre_draw != end) {

			payload.mesh = item.second;

			pre_draw->second(

				payload

			);

			item.second->Draw();

		}

	}

}

void Model::DrawInstanced(const GLsizei instances, PreDrawMap pre_draw_map) {

	auto end = pre_draw_map.end();

	auto payload = (ModelPayload) {

		.matrix = transformation_.Matrix()

	};

	for(auto item : meshes_) {

		auto pre_draw = pre_draw_map.find(

			item.first

		);

		if(pre_draw != end) {

			payload.mesh = item.second;

			pre_draw->second(

				payload

			);

			item.second->DrawInstanced(instances);

		}

	}
	
}

} // namespace gl