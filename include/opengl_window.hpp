#ifndef OPENGL_WINDOW_HPP_
#define OPENGL_WINDOW_HPP_
#include "Galaxy.hpp"
#include "VertexBufferLines.hpp"
#include "VertexBufferStars.hpp"
#include <qevent.h>
#include <qopenglcontext.h>
#include <qtimer.h>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QWindow>


class OpenGlWindow : public QWindow, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit OpenGlWindow(QWindow* parent = 0);
  virtual ~OpenGlWindow();

  /* OpenGL initialization, viewport resizing, and painting */

  virtual void initialize();
  virtual void render();
 public slots:
  void renderLater();
  void renderNow();

 protected:
 private:
  // test object for updating
  QTimer cycleTimer;

  bool event(QEvent* event) override;
  void exposeEvent(QExposeEvent* event) override;
  void UpdateStars();
  void UpdateVelocityCurve();
  void UpdateDensityWaves();
  void AddEllipsisVertices(std::vector<VertexColor>& vert,
                           std::vector<int>& vertIdx, float a, float b,
                           float angle, uint32_t pertNum, float pertAmp,
                           Color col) const;

  QOpenGLContext* m_context;
  /* QOpenGLVertexArrayObject m_vao; */
  /* QOpenGLBuffer	m_vertexBufferObject; */
  /* QOpenGLShaderProgram *m_program; */
  bool needsInitialize;

  const float TimeStepSize = 200000.0f;

  void releaseVertBuffer();

  // Galaxy renderer specific stuff
  Galaxy _galaxy;

  VertexBufferLines _vertDensityWaves;
  VertexBufferLines _vertVelocityCurve;
  VertexBufferStars _vertStars;

  float _time;
  float _fov;
  int _fps;

  glm::mat4 _matProjection;
  glm::mat4 _matView;

  glm::vec3 _camOrient;
  glm::vec3 _camPos;
  glm::vec3 _camLookAt;

  void adjustCamera();
};

#endif  // OPENGL_WINDOW_HPP_
