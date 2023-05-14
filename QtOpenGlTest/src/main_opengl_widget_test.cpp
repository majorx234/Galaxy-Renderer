#include <QApplication>
#include "opengl_widget.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // For OpenGL Graphics
    OpenGLWidget gl_widget;
    gl_widget.show();

    return app.exec();
}

