#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

GameObject::GameObject(Mesh *mesh_, Shader *shader_) :mesh(nullptr), shader(nullptr) {
	mesh = mesh_;
	shader = shader_;
}

GameObject::~GameObject() {
	if (mesh) delete mesh;
}

void GameObject::Render() const {
	mesh->Render();
}
