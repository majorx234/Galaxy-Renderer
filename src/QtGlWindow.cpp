#include <cmath>
#include <ctime>

#ifndef __APPLE__
 //   #include <GL/glu.h>
    #include <GL/glew.h>
    #include <GL/glut.h>
#else
    #include <glu.h>
#endif

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "QtGlWindow.hpp"
#include <qcoreevent.h>
#include <qwindow.h>

#include <iostream>
#include <QEvent>
#include <QTimer>
#include <QString>
#include <QSlider>

QtGlWindow::QtGlWindow(QWindow *parent)
  : QWindow(parent)
  , m_context(nullptr)
  , needsInitialize(true)
  , _fov(0)
  , _width(0)
  , _height(0)
  , _caption()
  , _fps(0)
  , _camPos({0, 0, 2})
  , _camLookAt({0, 0, 0})
  , _camOrient({0, 1, 0})
  , _matProjection()
  , _matView()
{
  setSurfaceType(QWindow::OpenGLSurface);
}

QtGlWindow::~QtGlWindow() {
  m_context->makeCurrent(this);

  m_vao.destroy();
  m_vertexBufferObject.destroy();
  delete m_program;
}

void QtGlWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    keyPressEvent(e);
}

void QtGlWindow::initialize() {
  _fov = 35000.0;  // axisLength
  _width = width();
  _height = height();

  // shader part
  m_program = new QOpenGLShaderProgram();
  // shaderProgram = glCreateProgram();
  if (!m_program->addShaderFromSourceFile(
      QOpenGLShader::Vertex, ":/src/shader/pass_through.vert"))
  {
    qDebug() << "Vertex shader errors :\n" << m_program->log();
  }

  if (!m_program->addShaderFromSourceFile(
      QOpenGLShader::Fragment, ":/src/shader/uniform_color.frag"))
  {
    qDebug() << "Fragment shader errors :\n" << m_program->log();
  }

  if (!m_program->link())
    qDebug() << "Shader linker errors :\n" << m_program->log();

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  // create a new buffer for the vertices
  m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
  m_vertexBufferObject.create(); // create underlying OpenGL object
  m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw); // must be called before allocate

  m_vertexBufferObject.bind(); // set it active in the context, so that we can write to it
  // int bufSize = sizeof(vertices) = 9 * sizeof(float) = 9*4 = 36 bytes
  m_vertexBufferObject.allocate(vertices, sizeof(vertices) ); // copy data into buffer

  // Initialize the Vertex Array Object (VAO) to record and remember subsequent attribute assocations with
  // generated vertex buffer(s)
  m_vao.create(); // create underlying OpenGL object
  m_vao.bind(); // sets the Vertex Array Object current to the OpenGL context so it monitors attribute assignments
  // now all following enableAttributeArray(), disableAttributeArray() and setAttributeBuffer() calls are
  // "recorded" in the currently bound VBA.

  // Enable attribute array at layout location 0
  m_program->enableAttributeArray(0);
  m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);
  // This maps the data we have set in the VBO to the "position" attribute.
  // 0 - offset - means the "position" data starts at the begin of the memory array
  // 3 - size of each vertex (=vec3) - means that each position-tuple has the size of 3 floats (those are the 3 coordinates,
  //     mind: this is the size of GL_FLOAT, not the size in bytes!

  // Release (unbind) all
  m_vertexBufferObject.release();
  m_vao.release(); // not really necessary, but done for completeness
}

void QtGlWindow::update() {
  
}

void QtGlWindow::render() {
  // this function is called for every frame to be rendered on screen
  const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // set the background color = clear color
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // use our shader program
  m_program->bind();
  // bind the vertex array object, which in turn binds the vertex buffer object and
  // sets the attribute buffer in the OpenGL context
  m_vao.bind();
  // now draw the triangles:
  // - GL_TRIANGLES - draw individual triangles
  // - 0 index of first triangle to draw
  // - 3 number of vertices to process
  glDrawArrays(GL_TRIANGLES, 0, 3);
  // finally release VAO again (not really necessary, just for completeness)
  m_vao.release();
}

void QtGlWindow::renderNow() {
  int ct = 0;
  double dt = 0;
  time_t t1(time(nullptr)), t2;
  if (!isExposed())
    return;
  // initialize on first call
  if (m_context == nullptr) {
    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());
    m_context->create();
  }

  m_context->makeCurrent(this);

  if (needsInitialize) {
    initializeOpenGLFunctions();
    initialize(); // call user code
    needsInitialize = false;
  }
  update();
  render();
  ++ct;

  t2 = time(nullptr);
  dt = difftime(t2, t1);
  if (dt > 1) {
    _fps = (int)((double)ct / dt);
    ct = 0;
    t1 = t2;
  }
  m_context->swapBuffers(this);
}

void QtGlWindow::renderLater() {
}

bool QtGlWindow::event(QEvent *event) {
    switch (event->type()) {
      case QEvent::UpdateRequest:
        renderNow();
        return true;
      default:
        return QWindow::event(event);
    }
}

void QtGlWindow::exposeEvent(QExposeEvent * /*event*/) {
    renderNow(); // simply redirect call to renderNow()
}

glm::vec2 QtGlWindow::getWindowPos(GLfloat x, GLfloat y, GLfloat z) {
  glm::vec3 pos = glm::vec3(x, y, z);
  glm::mat4 matModel = glm::mat4(1.0);
  glm::vec4 viewPort = glm::vec4(0.0f, 0.0f, (float)_width, (float)_height);
  glm::vec3 projected = glm::project(pos, matModel, _matProjection, viewPort);
  return glm::vec2(projected.x, projected.y);
}

void QtGlWindow::scaleAxis(float scale) {
  _fov *= scale;
  adjustCamera();
}

const glm::vec3& QtGlWindow::getCamPos() const { return _camPos; }

const glm::vec3& QtGlWindow::getCamOrient() const { return _camOrient; }

const glm::vec3& QtGlWindow::getCamLookAt() const { return _camLookAt; }

void QtGlWindow::setCameraOrientation(const glm::vec3& orient) {
  _camOrient = orient;
  adjustCamera();
}

void QtGlWindow::setCamera(const glm::vec3& pos, const glm::vec3& lookAt,
                          const glm::vec3& orient) {
  _camOrient = orient;
  _camPos = pos;
  _camLookAt = lookAt;
  adjustCamera();
}

void QtGlWindow::adjustCamera() {
  double l = _fov / 2.0;
  double aspect = (double)_width / _height;

  // new mvp matrices for glsl shaders via glm:
  _matProjection = glm::ortho(-l * aspect, l * aspect, -l, l, -l, l);

  glm::dvec3 camPos(_camPos.x, _camPos.y, _camPos.z);
  glm::dvec3 camLookAt(_camLookAt.x, _camLookAt.y, _camLookAt.z);
  glm::dvec3 camOrient(_camOrient.x, _camOrient.y, _camOrient.z);
  _matView = glm::lookAt(camPos, camLookAt, camOrient);
}

double QtGlWindow::getFOV() const { return _fov; }

int QtGlWindow::getFPS() const { return _fps; }

int QtGlWindow::getWidth() const { return _width; }

int QtGlWindow::getHeight() const { return _height; }
