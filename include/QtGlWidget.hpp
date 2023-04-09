#ifndef QT_GL_WIDGET_HPP
#define QT_GL_WIDGET_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <QOpenGLWidget>
#include <atomic>
#include <QEvent>

class QtGlWidget : public QOpenGLWidget
{
  Q_OBJECT
public:
  explicit QtGlWidget(QWidget* parent = 0);
  virtual ~QtGlWidget();

  /* OpenGL initialization, viewport resizing, and painting */
  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height);
  void setShaders(std::string shader_path);

  /* general init */
  void init(int width, int height, float axisLen, const std::string& caption);
  int getWidth() const;
  int getHeight() const;
public slots:
  // slots for xyz-rotation slider
  void setParam1(int param1);
  void setParam2(int param2);
  void setParam3(int param3);
  void setParam4(int param4);

protected slots:
  void _tick();
protected:
  virtual void InitSimulation() = 0;
  const glm::vec3& GetCamPos() const;
  const glm::vec3& GetCamOrient() const;
  const glm::vec3& GetCamLookAt() const;

  void SetCameraOrientation(const glm::vec3& orientation);
  void SetCamera(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& orient);
  void AdjustCamera();
  int GetFPS() const;
  void ScaleAxis(float scale);
  double GetFOV() const;
  glm::vec2 GetWindowPos(GLfloat x, GLfloat y, GLfloat z);

  QEvent _event;

  float _fov; // Length of an axis
  std::string _caption;

  int _width;
  int _height;
  int _fps;

  glm::vec3 _camPos; // Position of the camera
  glm::vec3 _camLookAt; // Point atwhich the camera is aimed
  glm::vec3 _camOrient; // orientation of the camera (rotation as it aims at its target))

  glm::mat4 _matProjection;
  glm::mat4 _matView;

  std::atomic_bool _running;
};

#endif // QT_GL_WIDGET_HPP
