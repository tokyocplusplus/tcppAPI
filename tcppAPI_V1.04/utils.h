#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

constexpr uint16_t SCR_WIDTH = 1280;
constexpr uint16_t SCR_HEIGHT = 720;
constexpr uint16_t GRID_ROWS = 1000;
constexpr uint16_t GRID_COLUMNS = 1000;

float lastTime = glfwGetTime();
int frameCount = 0;

// Camera parameters
float mouseSensitivity = 0.1f;
float cameraSpeed = 0.05f;
glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 10.0f);
float yaw = -90.0f; // Yaw is initialized to -90 degrees
float pitch = 0.0f; // Pitch is initialized to 0 degrees
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;


/* ---------- INDICES AND VERTICES ---------- */

// cube vertices
std::vector<GLfloat> vertices = {
    -0.5f, -0.5f, -0.5f,  // back bottom left
     0.5f, -0.5f, -0.5f,  // back bottom right
     0.5f,  0.5f, -0.5f,  // back top right
    -0.5f,  0.5f, -0.5f,  // back top left
    -0.5f, -0.5f,  0.5f,  // front bottom left
     0.5f, -0.5f,  0.5f,  // front bottom right
     0.5f,  0.5f,  0.5f,  // front top right
    -0.5f,  0.5f,  0.5f   // front top left
};

// cube indices
std::vector<GLuint> indices = {
    0, 1, 2, 2, 3, 0, // back face
    4, 5, 6, 6, 7, 4, // front face
    0, 4, 7, 7, 3, 0, // left face
    1, 2, 6, 6, 5, 1, // right face
    3, 2, 6, 6, 7, 3, // top face
    0, 1, 5, 5, 4, 0  // bottom face
};

/* ---------- END OF INDICES AND VERTICES ---------- */

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Clamp pitch
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw))), glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int compileShader(GLenum type, const char* source) {
    unsigned int shader = glCreateShader(type); // Create a shader object
    glShaderSource(shader, 1, &source, nullptr); // Provide the shader source code
    glCompileShader(shader); // Compile the shader

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader; // Return the compiled shader
}

void updateWindowTitle(GLFWwindow* window, float& lastTime, int& frameCount) {
    double currentTime = glfwGetTime();
    frameCount++;

    // Update the title every second
    if (currentTime - lastTime >= 1.0f) {
        float fps = frameCount / (currentTime - lastTime);
        std::string title = "FPS: " + std::to_string(static_cast<int>(fps));
        glfwSetWindowTitle(window, title.c_str());

        // Reset for the next interval
        lastTime = currentTime;
        frameCount = 0;
    }
}

#endif // OPENGL_UTILS_H
