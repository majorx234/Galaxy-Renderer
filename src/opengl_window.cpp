#ifndef __APPLE__
//   #include <GL/glu.h>
#include <GL/glew.h>
#include <GL/glut.h>
#else
#include <glu.h>
#endif

#include <qcoreevent.h>
#include <qwindow.h>

#include <QEvent>
#include <QString>
#include <QTimer>
#include <iostream>

#include "opengl_window.hpp"

// forward declaration debug functions
#define printOpenGLError() printOglError(__FILE__, __LINE__)
int printOglError(char *file, int line);
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);

// Helper function for

void OpenGlWindow::adjustCamera() {
  double l = _fov / 2.0;
  double aspect = (double)width() / height();

  // new mvp matrices for glsl shaders via glm:
  _matProjection = glm::ortho(-l * aspect, l * aspect, -l, l, -l, l);

  glm::dvec3 camPos(_camPos.x, _camPos.y, _camPos.z);
  glm::dvec3 camLookAt(_camLookAt.x, _camLookAt.y, _camLookAt.z);
  glm::dvec3 camOrient(_camOrient.x, _camOrient.y, _camOrient.z);
  _matView = glm::lookAt(camPos, camLookAt, camOrient);
}

OpenGlWindow::OpenGlWindow(QWindow *parent)
    : QWindow(parent),
      needsInitialize(true),
      m_context(nullptr),
      _fov(15000),
      _fps(10),
      _camPos({0, 0, 2}),
      _camLookAt({0, 0, 0}),
      _camOrient({0, 1, 0}),
      _galaxy(),
      _vertDensityWaves(2),
      _vertVelocityCurve(1, GL_DYNAMIC_DRAW),
      _vertStars(GL_FUNC_ADD, GL_ONE),
      cycleTimer(this) {
  setSurfaceType(QWindow::OpenGLSurface);
  connect(&cycleTimer, &QTimer::timeout, this, &OpenGlWindow::renderNow);
}

OpenGlWindow::~OpenGlWindow() {
  /* // resource cleanup */
  /**/
  /* // since we release resources related to an OpenGL context, */
  /* // we make this context current before cleaning up our resources */
  /**/
  cycleTimer.stop();
  m_context->makeCurrent(this);
  this->releaseVertBuffer();
}

void OpenGlWindow::releaseVertBuffer() {
  _vertStars.Release();
  /* _vertDensityWaves.Release(); */
  /* _vertVelocityCurve.Release(); */
}

void OpenGlWindow::initialize() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }

  _galaxy.Reset(
      {13000,    // radius of the galaxy
       4000,     // radius of the core
       0.0004f,  // angluar offset of the density wave per parsec of radius
       0.85f,    // excentricity at the edge of the core
       0.95f,    // excentricity at the edge of the disk
       100000,   // total number of stars
       true,     // has dark matter
       2,        // Perturbations per full ellipse
       40,       // Amplitude damping factor of perturbation
       70,       // dust render size in pixel
       4000});
  _vertStars.Initialize();
  _vertDensityWaves.Initialize();
  _vertVelocityCurve.Initialize();

  glDisable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  this->_camOrient = {0, 1, 0};
  adjustCamera();
  cycleTimer.start(20);
}

void OpenGlWindow::render() {
  _time += TimeStepSize;
  /* m_vao.release(); */
  glViewport(0, 0, width(), height());
  UpdateStars();
  /* UpdateDensityWaves(); */
  /* UpdateVelocityCurve(); */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  adjustCamera();
  int features = 0;
  features |= 1 << 0;

  features |= 1 << 1;

  features |= 1 << 2;

  features |= 1 << 3;

  _vertStars.UpdateShaderVariables(_time, _galaxy.GetPertN(),
                                   _galaxy.GetPertAmp(),
                                   (int)_galaxy.GetDustRenderSize(), features);
  _vertStars.Draw(_matView, _matProjection);
  /* _vertDensityWaves.Draw(_matView, _matProjection); */
  /* _vertVelocityCurve.Draw(_matView, _matProjection); */
}

void OpenGlWindow::renderNow() {
  if (!isExposed()) return;
  // initialize on first call
  if (m_context == nullptr) {
    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());
    m_context->create();
  }

  m_context->makeCurrent(this);

  if (needsInitialize) {
    initializeOpenGLFunctions();
    initialize();  // call user code
    needsInitialize = false;
  }
  render();
  m_context->swapBuffers(this);
}

void OpenGlWindow::renderLater() {}

bool OpenGlWindow::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::UpdateRequest:
      renderNow();
      return true;
    default:
      return QWindow::event(event);
  }
}

void OpenGlWindow::exposeEvent(QExposeEvent * /*event*/) {
  renderNow();  // simply redirect call to renderNow()
}

//
//
//
// from GalaxyWnd
//
//
//

void OpenGlWindow::UpdateVelocityCurve() {
  // I don't need every star for the curve.
  const auto &stars = _galaxy.GetStars();

  std::vector<VertexColor> vert;
  vert.reserve(1000);

  std::vector<int> idx;
  idx.reserve(1000);

  float dt_in_sec = TimeStepSize * Helper::SEC_PER_YEAR;
  float r = 0, v = 0;
  float cr = 0.5, cg = 1, cb = 1, ca = 1;
  for (int r = 0; r < _galaxy.GetFarFieldRad(); r += 100) {
    idx.push_back((int)vert.size());

    if (_galaxy.HasDarkMatter())
      vert.push_back({(float)r, Helper::VelocityWithDarkMatter((float)r) * 10.f,
                      0, cr, cg, cb, ca});
    else
      vert.push_back({(float)r,
                      Helper::VelocityWithoutDarkMatter((float)r) * 10.f, 0, cr,
                      cg, cb, ca});
  }

  _vertVelocityCurve.CreateBuffer(vert, idx, GL_POINTS);
}

void OpenGlWindow::AddEllipsisVertices(std::vector<VertexColor> &vert,
                                       std::vector<int> &vertIdx, float a,
                                       float b, float angle, uint32_t pertNum,
                                       float pertAmp, Color col) const {
  const int steps = 100;
  const float x = 0;
  const float y = 0;

  // Angle is given by Degree Value
  float beta = -angle * Helper::DEG_TO_RAD;
  float sinbeta = std::sin(beta);
  float cosbeta = std::cos(beta);

  int firstPointIdx = static_cast<int>(vert.size());
  for (int i = 0; i < 360; i += 360 / steps) {
    float alpha = i * Helper::DEG_TO_RAD;
    float sinalpha = std::sin(alpha);
    float cosalpha = std::cos(alpha);

    GLfloat fx =
        (GLfloat)(x + (a * cosalpha * cosbeta - b * sinalpha * sinbeta));
    GLfloat fy =
        (GLfloat)(y + (a * cosalpha * sinbeta + b * sinalpha * cosbeta));

    if (pertNum > 0) {
      fx += (GLfloat)((a / pertAmp) * std::sin(alpha * 2 * pertNum));
      fy += (GLfloat)((a / pertAmp) * std::cos(alpha * 2 * pertNum));
    }

    vertIdx.push_back((int)vert.size());

    VertexColor vc = {fx, fy, 0, col.r, col.g, col.b, col.a};
    vert.push_back(vc);
  }

  // Close the loop and reset the element index array
  vertIdx.push_back(firstPointIdx);
  vertIdx.push_back(0xFFFF);
}

void OpenGlWindow::UpdateDensityWaves() {
  std::vector<VertexColor> vert;
  std::vector<int> idx;

  //
  // First add the density waves
  //

  int num = 100;
  float dr = _galaxy.GetFarFieldRad() / num;
  for (int i = 0; i <= num; ++i) {
    float r = dr * (i + 1);
    AddEllipsisVertices(vert, idx, r, r * _galaxy.GetExcentricity(r),
                        Helper::RAD_TO_DEG * _galaxy.GetAngularOffset(r),
                        _galaxy.GetPertN(), _galaxy.GetPertAmp(),
                        {1, 1, 1, 0.2f});
  }

  //
  // Add three circles at the boundaries of core, galaxy and galactic medium
  //

  int pertNum = 0;
  float pertAmp = 0;
  auto r = _galaxy.GetCoreRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 1, 0, 0.5});

  r = _galaxy.GetRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {0, 1, 0, 0.5});

  r = _galaxy.GetFarFieldRad();
  AddEllipsisVertices(vert, idx, r, r, 0, pertNum, pertAmp, {1, 0, 0, 0.5});

  _vertDensityWaves.CreateBuffer(vert, idx, GL_LINE_STRIP);
}

void OpenGlWindow::UpdateStars() {
  std::vector<VertexStar> vert;
  std::vector<int> idx;

  const auto &stars = _galaxy.GetStars();

  float a = 1;
  Color color = {1, 1, 1, a};

  for (int i = 1; i < stars.size(); ++i) {
    const Color &col = Helper::ColorFromTemperature(stars[i].temp);
    color = {col.r, col.g, col.b, a};

    idx.push_back((int)vert.size());
    vert.push_back({stars[i], color});
  }

  _vertStars.CreateBuffer(vert, idx, GL_POINTS);
}
