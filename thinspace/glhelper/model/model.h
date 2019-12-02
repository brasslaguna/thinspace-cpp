
#ifndef GL_MODEL_H_
#define GL_MODEL_H_

#include <memory>
#include <map>
#include <string>

#include <glm/mat4x4.hpp>

#include "mesh/mesh.h"
#include "transformation/transformation.h"

namespace gl {

typedef struct {

	std::string name;

} ModelConfig;

typedef struct {

	glm::mat4 matrix;
	MeshPtr mesh;

} ModelPayload;

typedef std::map<std::string, std::function<void (ModelPayload)>> PreDrawMap;
typedef std::map<std::string, MeshPtr> MeshMap;

class Model {

	public:

		Model(ModelConfig config) {};
		void Draw(PreDrawMap pre_draw_map);
		void DrawInstanced(const GLsizei instances, PreDrawMap pre_draw_map);
		Transformation transformation_;
		MeshMap meshes_;
		
};

typedef std::shared_ptr<Model> ModelPtr;

} // namespace gl

#endif // GL_MODEL_H_