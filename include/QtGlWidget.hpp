#include <QOpenGLWidget>

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
private:
    int _width;
    int _height;
public slots:
    // slots for xyz-rotation slider
    void setParam1(int param1);
    void setParam2(int param2);
    void setParam3(int param3);
    void setParam4(int param4);

protected slots:
    void _tick();
};
