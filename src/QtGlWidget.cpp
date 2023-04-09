#include "QtGlWidget.hpp"

QtGlWidget::QtGlWidget(QWidget *parent) : QGLWidget(parent)
  : _event()
  _fov(0),
  _width(0),
  _height(0),
  _caption(),
  _fps(0),
  _camPos({ 0, 0, 2 }),
  _camLookAt({ 0, 0, 0 }),
  _camOrient({ 0, 1, 0 }),
  _matProjection(),
  _matView(),
  _running(true) {
}

QtGlWidget::~QtGlWidget() {

}

void QtGlWidget::_tick() {
  // triggers paintGL()
  //update();

  // Set timer according to FPS
  //QTimer::singleShot(1000/_fps, this, SLOT(_tick()));
}

glm::vec2 QtGlWidget::GetWindowPos(GLfloat x, GLfloat y, GLfloat z)
{
  glm::vec3 pos = glm::vec3(x, y, z);
  glm::mat4 matModel = glm::mat4(1.0);
  glm::vec4 viewPort = glm::vec4(0.0f, 0.0f, (float)_width, (float)_height);
  glm::vec3 projected = glm::project(pos, matModel, _matProjection, viewPort);
  return glm::vec2(projected.x, projected.y);
}

void QtGlWidget::initializeGL() {}

void QtGlWidget::paintGL() {}

void QtGlWidget::resizeGL(int w, int h) {}

void QtGlWidget::setShaders(std::string shader_path) {}

void QtGlWidget::init(int width, int height, float axisLen, const std::string &caption) {
  this._fov = axisLen;
  this._width = width;
  this._height = height;

  glewInit();
  std::cout << "OpenGL Version Information:" << glGetString(GL_VERSION) << std::endl;
  std::cout << "- OpenGL:     " << glGetString(GL_VERSION) << std::endl;
  std::cout << "- GLSL:       " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "- Vendor/GPU: " << glGetString(GL_VENDOR) << "/" << glGetString(GL_RENDERER) << std::endl;

  InitGL();
  InitSimulation();
}

int QtGlWidget::getWidth() {
  return this._width;
}

int QtGlWidget::getHeight() {
  return this._height;
}

void QtGlWidget::setParam1(int param1) {}

void QtGlWidget::setParam2(int param2) {}

void QtGlWidget::setParam3(int param3) {}

void QtGlWidget::setParam4(int param4) {}

const glm::vec3& QtGlWidget::GetCamPos() {
  return glm::vec3(0.0f, 0.0f, 0.0f);
}

const glm::vec3& QtGlWidget::GetCamOrient() {
  return glm::vec3(0.0f, 0.0f, 0.0f);
}

const glm::vec3& QtGlWidget::GetCamLookAt() {
  return glm::vec3(0.0f, 0.0f, 0.0f);
}

void QtGlWidget::SetCameraOrientation(const glm::vec3& orientation) {}

void QtGlWidget::SetCamera(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& orient) {}

void QtGlWidget::AdjustCamera() {}

int QtGlWidget::GetFPS() {
  return this._fps;
}

void QtGlWidget::ScaleAxis(float scale) {
  this._fov *= scale;
  AdjustCamera();
}

double QtGlWidget::GetFOV() {
  return 0.0;
}

glm::vec2 QtGlWidget::GetWindowPos(GLfloat x, GLfloat y, GLfloat z) {
  return glm::vec3(0.0f, 0.0f);
}

/**************** Debug Functions ***************/

int printOglError(char *file, int line) {
  //
  // Returns 1 if an OpenGL error occurred, 0 otherwise.
  //
  GLenum glErr;
  int retCode = 0;

  glErr = glGetError();
  while (glErr != GL_NO_ERROR) {

    printf("glError in file %s @ line %d: %s\n", file, line,
           gluErrorString(glErr));
    retCode = 1;
    glErr = glGetError();
  }
  return retCode;
}

void printShaderInfoLog(GLuint obj) {
  int infologLength = 0;
  int charsWritten = 0;
  char *infoLog;

  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 0) {
    infoLog = (char *)malloc(infologLength);
    glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
    printf("%s\n", infoLog);
    free(infoLog);
  }
}

void printProgramInfoLog(GLuint obj) {
  int infologLength = 0;
  int charsWritten = 0;
  char *infoLog;

  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 0) {
    infoLog = (char *)malloc(infologLength);
    glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
    printf("%s\n", infoLog);
    free(infoLog);
  }
}


