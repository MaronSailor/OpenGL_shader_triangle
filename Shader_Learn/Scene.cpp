// Scene.cpp

#include "Scene.h"
#define GLEW_STATIC

Triangle triangle;
Shader* shader;

Scene::Scene() {};



void Scene::initOpenGL() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("NewWindow");

	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed!" << std::endl;
		exit(EXIT_FAILURE);
	}

	CreateShader();

	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}


void Scene::RenderFunction() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->Use();
	triangle.Draw();
	glutSwapBuffers();
}


void Scene::Reshape(int w, int h) {

	glViewport(0, 0, w, h);
	glLoadIdentity();
}


void Scene::CreateShader() {
	shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl"); // Утворюємо нові шейдери
	shader->Use();
	triangle.Init(shader->ProgramId);								   // Переносимо використовуємо окремі шейдери для трикутника
}
