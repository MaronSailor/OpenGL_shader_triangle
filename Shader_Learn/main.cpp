// main.cpp

#include "Scene.h"

#include <GL/freeglut.h>

Scene scene;

void DisplayWrapper() { scene.RenderFunction(); }
void ReshapeWrapper(int w, int h) { scene.Reshape(w, h); }

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	scene.initOpenGL();


	glutDisplayFunc(DisplayWrapper);
	glutIdleFunc(DisplayWrapper);
	glutReshapeFunc(ReshapeWrapper);



	glutMainLoop();
	exit(EXIT_SUCCESS);
}