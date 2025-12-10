// Shaders.cpp

#include "Shaders.h"
#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) { // Створюємо конструктор для классу

    std::string vCode = LoadFile(vertexPath);
    std::string fCode = LoadFile(fragmentPath);

    GLuint vShader = Compile(GL_VERTEX_SHADER, vCode.c_str()); // Функція перевірки справності. Якщо спрацює, то перекине справний шейдер в vShader.    Перетворити GLSL в машинний код
    GLuint fShader = Compile(GL_FRAGMENT_SHADER, fCode.c_str());

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, vShader);
    glAttachShader(ProgramId, fShader);
    glLinkProgram(ProgramId);               // База, що і в Tutorial: прикріплюємо шейдери і фрагменти до програми

    GLint success;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ProgramId, 512, NULL, infoLog);
        std::cerr << "Error: Program linking failed\n" << infoLog << std::endl; // Не пройшло перевірку? Тримай логи
    }

    glDeleteShader(vShader);                // Ми вже все під'єднали в glLinkProgram(ProgramId). Більше нам об'єкти непотрібні      Якщо не видалити, то пам'ять GPU засреться
    glDeleteShader(fShader);
}

void Shader::Use() {
    glUseProgram(ProgramId);
}

std::string Shader::LoadFile(const char* path) {
    std::ifstream file(path);                               // Базова функція від fstream. Ми відкриваємо файл, щоб читати його
    if (!file.is_open()) {
        std::cerr << "Error: could not open shader file " << path << std::endl; // Якщо файл відсутній, чи тупо не відкрився, то error
        exit(EXIT_FAILURE);
    }
    std::stringstream buf;                                  // Рядковий потік, щоб прочитати весь файл
    buf << file.rdbuf();                                    // Весь текст з файлу тепер в buf
    return buf.str();                                       // Повертаємо у вигляді string
}

GLuint Shader::Compile(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);     // Передаємо інфу по типу, щоб не писати дві різні функції: GL_VERTEX_SHADER i GL_FRAGMENT_SHADER         Створює шейдер на GPU
    glShaderSource( // glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);                                        Передає код шейдера на GPU
        shader,          // Тип шейдеру (вище); 
        1,               // К-кість рядків, які ми передаємо в джерело шейдерів. Тут один, бо функція c_str(), яка перетворює весь файл в один string
        &source,         // Джерело, або ж файл (vCode = LoadFile(vertexPath);) або (fCode = LoadFile(fragmentPath);)
        NULL);           // NULL визначить кінець рядка через \n
    glCompileShader(shader);         // Коли все визначили, то компілюємо (створюємо)

    GLint success;  // GL_TRUE || GL_FALSE                 
    glGetShaderiv( // glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
        shader,            // Знову відсилка на GLuint shader = glCreateShader(type(GL_VERTEX_SHADER або GL_FRAGMENT_SHADER))
        GL_COMPILE_STATUS, // Чи готова компіляція? glCompileShader(shader)
        &success);         // Те, куди записано результат. Чому &success? Бо *params
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Error: Shader compilation failed\n" << infoLog << std::endl; // Якщо помилка, - ось тобі Logs
    }
    return shader; // Шейдер пройшов перевірку. На, тримай його назад   
}

//  По суті, це новіша версія
// 
//  Нема сенсу змушувати Scene провантажувати кожен раз шейдери. Плюс стає дуже важко розібратись
// 
//  Vertex
//  Scene::VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
//  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
//  glCompileShader(VertexShaderId);
//  PrintShaderLog(VertexShaderId);
//
//  Fragment 
//  Scene::FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
//  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
//  glCompileShader(FragmentShaderId);
//  PrintShaderLog(VertexShaderId);