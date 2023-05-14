#include <QApplication>
#include <QSurfaceFormat>
#include "opengl_window.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

	// Set OpenGL Version information
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3,3);
  // For OpenGL Graphics
  OpenGlWindow opengl_window;
  opengl_window.setFormat(format);
  opengl_window.resize(800,600);
  opengl_window.show();

  return app.exec();
}

