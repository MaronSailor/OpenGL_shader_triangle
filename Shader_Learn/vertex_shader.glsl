#version 330 core
in vec3 in_vertex;
in vec3 in_color;
out vec3 vColor;

void main() {
    gl_Position = vec4(in_vertex, 1.0);
    vColor = in_color;
}
