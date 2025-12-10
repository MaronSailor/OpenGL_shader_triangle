// Triangle.cpp

#include "Triangle.h"

Triangle::Triangle() {
    GLfloat initVertices[9] = {
        -0.5f, -0.25f, 0.0f,
         0.0f, 0.75f, 0.0f,
         0.5f, -0.25f, 0.0f
    };
    for (int i = 0; i < 9; i++) Vertices[i] = initVertices[i];

    GLfloat initColors[9] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    for (int i = 0; i < 9; i++) Colors[i] = initColors[i];
}

void Triangle::Init(GLuint programId) {
    vertexLoc = glGetAttribLocation(programId, "in_vertex"); // Особистий ProgramId і in_vertex з vertex_shader.glsl
    colorLoc = glGetAttribLocation(programId, "in_color");   // in_color з vertex_shader.glsl

    glGenVertexArrays(1, &VAO);                     // Створення VAO, де 1 - к-кість буферів
    glBindVertexArray(VAO);                         // Просто активація VAO, бо мама сама по собі не "з'являється"

    glGenBuffers(1, &VBO);                          // Створення VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);             // Прив'язуємо VBO до VAO (GL_ARRAY_BUFFER). Тобто до glBindVertexArray(VAO)
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  // Закидуємо в буфер всі вершини (Vertices) з умовою, що ці вершини будуть статичні і не рухатимуться
    glVertexAttribPointer( // void glVertexAttribPointer(GLuint index, GLint size,GLenum type, GLboolean normalized, GLsizei stride, const void* pointer );

        vertexLoc,      // Вказує на vertexLoc = glGetAttribLocation(programId, "in_vertex");
        3,              // К-кість компонентів на вершину (3, бо треба 3 точки: x,y,z для визначення вершии)
        GL_FLOAT,       // Тип даних, які передаються
        GL_FALSE,       // Нормалізувати, чи нє (не графіка і не Normals). Тут FALSE, бо ми вже передаємо дані в вигляді FLOAT
        0,              // Відстань у байтах між вершинами. size*sizeof(type(GL_FLOAT)). 
        0);             // Відступ від початку масиву в байтах

    glEnableVertexAttribArray(vertexLoc);   // Включаємо те, що накалапуцяли вище

    glGenBuffers(1, &CBO);                  // Basically the same, що і в glGenBuffers
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);    // Підключаємо до того ж VAO, щоб він зберігав обидва атрибути 

    glBindVertexArray(0);                   // Відв'язуємо VAO. Він типу мами, яка зібрала своїх дітей, а потім викинула з дому, що потім впустити когось іншого...
    // Ну або типу контейнера, який взяв груз, довіз його, розгрузив і готовий до нового грузу    
}

void Triangle::Draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
