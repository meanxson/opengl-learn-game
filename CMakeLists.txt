cmake_minimum_required(VERSION 3.25)
project(opengl_learn_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl_learn_game main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/external/glew/include)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

add_subdirectory(external/glew/build/cmake ${CMAKE_CURRENT_BINARY_DIR}/glew)
target_link_libraries(${PROJECT_NAME} PRIVATE glew)

add_subdirectory(external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)