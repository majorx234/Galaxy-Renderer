#ifndef QT_GL_WINDOW_HPP
#define QT_GL_WINDOW_HPP

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QSlider>

namespace Ui {
class QtGlWindow;

}

class QtGlWindow : public QMainWindow {
      Q_OBJECT

 public:
  explicit QtGlWindow(QWidget *parent = 0);
  ~QtGlWindow();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private:
  Ui::QtGlWindow *ui;
  
};

#endif // QT_GL_WINDOW_HPP
