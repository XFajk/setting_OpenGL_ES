#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>

#include "lib/utils/shader.h"
#include "lib/utils/error.h"

int main() {

    // Initialize ------------------------------------------------------------------------------------------------------

    int width = 640;
    int height = 480;

    const int RES_MOD = 1;

    // initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version and forward compatibility
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL program", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Create an OpenGL context
    GLenum gladError = gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
    if (!gladError) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Check for OpenGL errors
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR) {
        printf("OpenGL had an error error code: %i\n", glError);
        glfwTerminate();
        return -1;
    }

    //------------------------------------------------------------------------------------------------------------------

    // Logic variables and game initialization -------------------------------------------------------------------------
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.3f, 0.1f, 1.0f);

    GLuint default_vao;

    //------------------------------------------------------------------------------------------------------------------

    // OpenGL program variables ----------------------------------------------------------------------------------------

    unsigned int vertex_shader = addToShaderProgram("shaders/vertex.glsl", GL_VERTEX_SHADER);
    unsigned int fragment_shader = addToShaderProgram("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

    // Create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(shaderProgram);

    getGLErrors(gladError);

    //------------------------------------------------------------------------------------------------------------------

    // Game loop -------------------------------------------------------------------------------------------------------

    // setting the constant uniforms

    getGLErrors(gladError);

    // Loop  until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);



        // Swap buffers
        glfwSwapBuffers(window);

    }

    //------------------------------------------------------------------------------------------------------------------

    // Destruction -----------------------------------------------------------------------------------------------------

    glfwTerminate();

    //------------------------------------------------------------------------------------------------------------------

    return 0;
}
