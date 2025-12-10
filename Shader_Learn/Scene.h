//Scene.h

#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Triangle.h"
#include "Shaders.h"

class Scene {
public:
	Scene();
	void RenderFunction();
	void Reshape(int width, int height);
	void initOpenGL();

	void CreateShader();
	static const GLchar* VertexShader;
	static const GLchar* FragmentShader;
private:
	int Width = 800;
	int Height = 600;
};

#endif // !SCENE_H
