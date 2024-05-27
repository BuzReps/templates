#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLValue {
  GLenum val;
  const char * str;
};

#define GL(val_)                                                               \
  GLValue {                                                                    \
    .val = val_, .str = #val_                                                  \
  }

static const std::vector<GLValue> kAllSources = {
  GL(GL_DEBUG_SOURCE_API),
  GL(GL_DEBUG_SOURCE_WINDOW_SYSTEM),
  GL(GL_DEBUG_SOURCE_SHADER_COMPILER),
  GL(GL_DEBUG_SOURCE_THIRD_PARTY),
  GL(GL_DEBUG_SOURCE_APPLICATION),
  GL(GL_DEBUG_SOURCE_OTHER),
};

static const std::vector<GLValue> kAllTypes = {
  GL(GL_DEBUG_TYPE_ERROR),
  GL(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR),
  GL(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR),
  GL(GL_DEBUG_TYPE_PORTABILITY),
  GL(GL_DEBUG_TYPE_PERFORMANCE),
  GL(GL_DEBUG_TYPE_MARKER),
  GL(GL_DEBUG_TYPE_PUSH_GROUP),
  GL(GL_DEBUG_TYPE_POP_GROUP),
  GL(GL_DEBUG_TYPE_OTHER),
};

static const std::vector<GLValue> kAllSeverities = {
  GL(GL_DEBUG_SEVERITY_LOW),
  GL(GL_DEBUG_SEVERITY_MEDIUM),
  GL(GL_DEBUG_SEVERITY_HIGH),
  GL(GL_DEBUG_SEVERITY_NOTIFICATION),
};

static GLValue FindGLValue(GLenum gl_value,
                           const std::vector<GLValue> & values) {
  for (const auto & value : values) {
    if (value.val == gl_value) {
      return value;
    }
  }
  return GLValue{.val = gl_value, .str = "UNKNOWN"};
}

static void GLAPIENTRY DebugMessageCallback(GLenum source,
                                            GLenum type,
                                            GLenum id,
                                            GLenum severity,
                                            GLsizei /*length*/,
                                            const GLchar * message,
                                            const void * userParam) {
  (void)userParam;
  static int i = 0;
  std::cout << std::format(
    "{}) Source:{} Type:{} ID:0x{:X} Severity:{} Messaage:{}\n",
    ++i,
    FindGLValue(source, kAllSources).str,
    FindGLValue(type, kAllTypes).str,
    id,
    FindGLValue(severity, kAllSeverities).str,
    message);
}

static void WindowResizeCallback(GLFWwindow * window, int width, int height) {
  glViewport(0, 0, width, height);
}

static GLFWwindow * CreateWindow() {
  if (!glfwInit()) {
    throw std::runtime_error("Cannot initialize GLFW");
  }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_SAMPLES, 4);
  const bool fullscreen = false;
  GLFWmonitor * monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
  GLFWwindow * window =
    glfwCreateWindow(1200, 900, "My OpenGL", monitor, nullptr);
  if (nullptr == window) {
    throw std::runtime_error("Could not create window.");
  }
  glfwMakeContextCurrent(window);
  glewInit();
  glfwSwapInterval(1);

  glfwSetFramebufferSizeCallback(window, &WindowResizeCallback);
  return window;
}

GLuint CreateProgram() {
  GLuint program = glCreateProgram();
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  const char * vert_shader_source = R"glsl(
    #version 430
    out vec4 vertex_color;
    const vec4 points[] = {
      vec4(-0.5f, -0.5f, 0.0f, 1.0f),
      vec4(0.0f, 0.5f, 0.0f, 1.0f),
      vec4(0.5f, -0.5f, 0.0f, 1.0f),
    };
    const vec4 colors[] = {
      vec4(1.0f, 0.0f, 0.0f, 1.0f),
      vec4(0.0f, 1.0f, 0.0f, 1.0f),
      vec4(0.0f, 0.0f, 1.0f, 1.0f),
    };
    void main() {
      gl_Position = points[gl_VertexID];
      vertex_color = colors[gl_VertexID];
    }
  )glsl";
  const char * frag_shader_source = R"glsl(
    #version 430
    in vec4 vertex_color;
    out vec4 color;
    void main() {
      color = vertex_color;
    }
  )glsl";
  glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
  glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
  glCompileShader(vert_shader);
  glCompileShader(frag_shader);
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);
  GLint param;
  glGetProgramiv(program, GL_LINK_STATUS, &param);
  if (GL_TRUE != param) {
    throw "Cannot link program";
  }
  return program;
}

int main(int argc, char * argv[]) {
  GLFWwindow * window = CreateWindow();

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(DebugMessageCallback, nullptr);

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  GLuint vao;
  glCreateVertexArrays(1, &vao);

  GLuint program = CreateProgram();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
