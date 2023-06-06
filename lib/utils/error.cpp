//
// Created by Rudolf Vrbenský on 23/05/2023.
//

#include "error.h"

void getGLErrors(GLenum error) {
    while ((error = glGetError()) != GL_NO_ERROR)
        switch (error) {
            case GL_INVALID_OPERATION:
                printf("OpenGL error GL_INVALID_OPERATION number of error: %i", error);
                break;
            case GL_INVALID_VALUE:
                printf("OpenGL error GL_INVALID_VALUE number of error: %i", error);
                break;
            default:
                printf("unknown OpenGL error:: %i", error);
                break;
        }
}