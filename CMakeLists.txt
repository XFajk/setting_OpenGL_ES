cmake_minimum_required(VERSION 3.25)
project(setting_OpenGL_ES)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-DGLEW_STATIC -DSDL_MAIN_HANDLED -DGL_SILENCE_DEPRECATION)

add_executable(${PROJECT_NAME} "main.cpp" lib/utils/shader.cpp lib/utils/shader.h lib/utils/error.cpp lib/utils/error.h)

add_subdirectory("${PROJECT_SOURCE_DIR}/dep/GLAD/")

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/GLAD/include/")

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/GLFW/include/")
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/GLFW/lib")

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/SDL2/include/SDL2/")
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/SDL2/lib/")

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/CGLM/include/")
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/dep/MacOS/CGLM/lib/")

target_link_libraries(${PROJECT_NAME} PUBLIC
        libSDL2.dylib
        glad
        libglfw.3.3.dylib
        libcglm.0.9.1.dylib
        ${OPENGL_LIBRARIES}
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/shaders"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        )
