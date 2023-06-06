//
// Created by Rudolf Vrbenský on 23/05/2023.
//

#include "shader.h"

unsigned int addToShaderProgram(const char* filepath, GLenum shader_type) {
    // Create vertex shader
    std::ifstream shader(filepath);
    if (!shader.is_open()) {
        std::cout << "Error opening the file." << std::endl;
        return 0;
    }

    std::string line;
    std::string source;

    while (std::getline(shader, line)) {
        source += line + "\n";
    }

    shader.close();

    const char* c_source = source.c_str();

    unsigned int Shader = glCreateShader(shader_type);
    glShaderSource(Shader, 1, &c_source, nullptr);
    glCompileShader(Shader);

    int success = 0;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int logSize = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<char> errorLog(logSize);
        glGetShaderInfoLog(Shader, logSize, &logSize, errorLog.data());
        std::cerr << filepath << " shader compilation failed:\n" << errorLog.data() << std::endl;
        return 1;
    }
    return Shader;
}






