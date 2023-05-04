#include <QApplication>
#include <QDesktopWidget>

#include "QtGlWindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QtGlWindow qt_gl_window;
  //qt_gl_window.resize(qt_gl_window.sizeHint());
  int desktopArea = QApplication::desktop()->width() *
                    QApplication::desktop()->height();
  int widgetArea = qt_gl_window.width() * qt_gl_window.height();

  //qt_gl_window.setWindowTitle("OpenGL with Qt");

  if (((float)widgetArea / (float)desktopArea) < 0.75f)
    qt_gl_window.show();
  else
    qt_gl_window.showMaximized();
  return app.exec();
}
