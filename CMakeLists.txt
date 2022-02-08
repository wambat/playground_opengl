cmake_minimum_required(VERSION "3.16.3")

project("GLTest")

add_library(GLAD "glad.c")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenGL REQUIRED)
# find_package(GLM REQUIRED)
find_package(GLFW3 REQUIRED)
# if(NOT OPENGL_FOUND)
#   message("ERROR: OpenGL not found")
# endif(NOT OPENGL_FOUND)
# set(GL_LIBRARY GL GLU X11)
# set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARY} STB_IMAGE)
set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD ${CMAKE_DL_LIBS} )
add_executable("${PROJECT_NAME}" "main.cpp")

target_link_libraries("${PROJECT_NAME}" "${LIBS}")

# install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
# install(FILES "${main.c}" DESTINATION src)
