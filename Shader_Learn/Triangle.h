// Triangle.h

#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <GL/glew.h>
#include <GL/freeglut.h>

class Triangle {
public:
    Triangle();
    void Init(GLuint programId);   // створення VAO/VBO після компіляції шейдерів
    void Draw();                   // відмальовування
private:
    GLfloat Vertices[9];
    GLfloat Colors[9];

    GLuint VAO = 0;                // Vertex Array Object - для прив'язки VBO i CBO, бо VBO i CBO не знають, кому вони належать 
    GLuint VBO = 0;                // Vertex Buffer Object - для зберігання вершин
    GLuint CBO = 0;                // Color Buffer Object - для зберігання кольорів
    GLint vertexLoc = -1;
    GLint colorLoc = -1;
};

#endif // !TRIANGLE_H