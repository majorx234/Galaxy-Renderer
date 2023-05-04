#ifndef QT_GL_WINDOW_HPP
#define QT_GL_WINDOW_HPP

#include <qevent.h>
#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <qopenglcontext.h>
#include <QSlider>
#include <glm/glm.hpp>

class QtGlWindow : public QWindow, protected QOpenGLFunctions
{
  Q_OBJECT
 public:
  explicit QtGlWindow(QWindow* parent = 0);
  virtual ~QtGlWindow();

  virtual void initialize();
  virtual void render();
  virtual void update(); // = 0;
  int getWidth() const;
  int getHeight() const;
 public slots:
  void renderLater();
  void renderNow();

 protected:
  const glm::vec3& getCamPos() const;
  const glm::vec3& getCamOrient() const;
  const glm::vec3& getCamLookAt() const;
  void setCameraOrientation(const glm::vec3& orientation);
  void setCamera(const glm::vec3& pos, const glm::vec3& lookAt,
                 const glm::vec3& orient);
  void adjustCamera();
  int getFPS() const;
  void scaleAxis(float scale);
  double getFOV() const;
  glm::vec2 getWindowPos(GLfloat x, GLfloat y, GLfloat z);

  float _fov;  ///< Length of an axis

  std::string _caption;

  int _width;   ///< Width of the window in pixel
  int _height;  ///< Height of the window in pixel
  int _fps;

  glm::vec3 _camPos;     ///< Position of the camera
  glm::vec3 _camLookAt;  ///< Point atwhich the camera is aimed
  glm::vec3 _camOrient;  ///< orientation of the camera (rotation as it aims at
                         ///< its target)

  glm::mat4 _matProjection;
  glm::mat4 _matView;

  void keyPressEvent(QKeyEvent *event);
  bool event(QEvent *event) override;
  void exposeEvent(QExposeEvent*event) override;

  QOpenGLContext *m_context;

  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer   m_vertexBufferObject;
  QOpenGLShaderProgram *m_program;
  bool needsInitialize;
};

#endif // QT_GL_WINDOW_HPP
