#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define WHEIGHT 768
#define WWIDTH 1024

void init_gl (){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0,0,width, height);
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f, 0.0f,
};

unsigned int VBO;

unsigned int VAO;


std::string vertexShaderSource;
unsigned int vertexShader;

std::string fragmentShaderSource;
unsigned int fragmentShader;

unsigned int shaderProgram;

void load_shader(std::string &targetString, const char *filename)
{
  std::ifstream t;
  t.open(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  std::string str = buffer.str();
  targetString = str.c_str();
  std::cout << str << std::endl;
  t.close();
}

void setup_shader(int shader, const std::string &shaderSrc) {
  const char *css = shaderSrc.c_str();
  glShaderSource(shader, 1, &css, NULL);
  glCompileShader(shader);
  int success;
  char infoLog[412];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER:COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

void setup_program(const int vertexShader, const int fragmentShader) {

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  int success;
  char infoLog[412];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
}

void setup_shaders()
{

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  std::cout << "VERT. SHADER SETUP" << std::endl;
  load_shader(vertexShaderSource, "shaders/simple.vert");
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  setup_shader(vertexShader, vertexShaderSource);

  std::cout << "FRAG. SHADER SETUP" << std::endl;
  load_shader(fragmentShaderSource, "shaders/simple.frag");
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  setup_shader(fragmentShader, fragmentShaderSource);
  setup_program(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

}

void draw_object() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

}

void render_loop(GLFWwindow* window)
{
  while(!glfwWindowShouldClose(window))
    {
      processInput(window);

      glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      draw_object();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
}


int make_GLFW_window () {
  GLFWwindow* window = glfwCreateWindow(WWIDTH, WHEIGHT, "TestOpenGL", NULL, NULL);
  if (window==NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to init GLAD" << std::endl;
      return -1;
    }
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glViewport(0,0,WWIDTH, WHEIGHT);
  setup_shaders();
  render_loop(window);
  glfwTerminate();
  return 0;
}

int main () {
  std::cout << "Initializing OpenGL\n";
  init_gl();
  // std::cout << "Done.\n";
  return make_GLFW_window();
}
