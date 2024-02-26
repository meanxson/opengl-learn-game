#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

const char *vertexShaderSource = "# version 330 core \n"
                                 "layout(location = 0) in vec3 vertex_position;\n"
                                 "void main()\n {"
                                 "gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);\n"
                                 "} \0";

const char *fragmentShaderSource = "#version 330 core \n"
                                   "out vec4 frag_color;\n"
                                   "void main() { \n"
                                   "frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
                                   "}\n\0";


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Open GL Learn", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Has problem with creating GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //========Shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int successCode;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successCode);

    if (!successCode) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "HAS PROBLEM WITH LOADING VERTEX SHADER \n";
    }


    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successCode);

    if (!successCode) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "HAS PROBLEM WITH LOADING FRAGMENT SHADER \n";
    }

    //Linking Shader
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successCode);

    if (!successCode) {
        glGetProgramInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "HAS PROBLEM WITH LOADING SHADER PROGRAM \n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //================

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f

    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //================


    glViewport(0, 0, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


