#include "opengl_widget.hpp"

#include <iostream>
#include <QKeyEvent>
#include <QTimer>
#include <QString>

// forward declaration debug functions
#define printOpenGLError() printOglError(__FILE__, __LINE__)
int printOglError(char *file, int line); 
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);

OpenGLWidget::OpenGLWidget(QWidget *parent)
: QOpenGLWidget(parent)
{
  _width = 0;
  _height = 0;
  //_texture = 0;
  _fps = 1.0;
}

OpenGLWidget::~OpenGLWidget() {
}

void OpenGLWidget::_tick()
{
    // triggers paintGL()
    update();

    // Set timer according to FPS
    QTimer::singleShot(1000/_fps, this, SLOT(_tick()));
}

void OpenGLWidget::initializeGL()
{
    int camera_num;
    std::string shader_path;

    glewInit();

    _tick();
}

void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::resizeGL( int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    if(w == 0)
        w = 1;


    _width = w;
    _height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (h == 0)  // Calculate aspect ratio of the window
       gluPerspective(60, (float) w, 1.0, 50.0);
    else
       gluPerspective(60, (float) w / (float) h, 1.0, 50.0);

    gluLookAt(0.0,  0.0, 2.0,   // eye
              0.0,  0.0, 0.0,   // center
              0.0,  1.0, 0.0);  // up

    glMatrixMode(GL_MODELVIEW);  // Select the model view matrix
    glLoadIdentity();           // Reset the model view matrix
}
/**************** Debug Functions ***************/

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
