#ifndef SHADERS_H
#define SHADERS_H

const char* vertexShaderSource = R"(
#version 460 core
layout(location = 0) in vec3 aPos; // CUBE VERTEXES POSITION
layout(location = 1) in vec3 instancePosition; // ACTUAL SEVERAL CUBE POSITIONS

uniform mat4 view; // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    gl_Position = projection * view * vec4(aPos + instancePosition, 1.0); // Combine position and instance offset
}
)";

const char* fragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 1.0, 1.0); // Set color to pink
}
)";


#endif // SHADERS_H
