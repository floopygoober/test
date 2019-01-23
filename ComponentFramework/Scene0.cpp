#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Scene0.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"

Scene0::Scene0(){

}


Scene0::~Scene0() {}

bool Scene0::OnCreate() {

	camera = new Camera();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}
	Mesh *meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	Shader *shaderPtr = new Shader("phongVert.glsl", "phongFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
	ball = new GameObject(meshPtr, shaderPtr);

	lightSource = Vec3(3.0, 6.0, 0.0);

	return true;
}


void Scene0::OnDestroy() {}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene0::Update(const float deltaTime_) {}

void Scene0::Render() const {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = ball->getShader()->getProgram();
	glUseProgram(program);

	/// This should not be done here. You only need to get these
	/// ID's once after the sharder has been created - TODO
	GLint projectionMatrixID = glGetUniformLocation(program, "projectionMatrix");
	GLint viewMatrixID = glGetUniformLocation(program, "viewMatrix");
	GLint lightPosID = glGetUniformLocation(program, "lightPos");
	GLint modelMatrixID = glGetUniformLocation(program, "modelMatrix");
	GLint normalMatrixID = glGetUniformLocation(program, "normalMatrix");

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(lightPosID, 1, lightSource);

	/// These really should be in the GameObject class, it passes
	/// the model matrix to the GPU - TODO 
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, Matrix4());
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, Matrix3());

	ball->Render();

	glUseProgram(0);
}

