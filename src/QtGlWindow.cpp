#include <QtWidgets>
#include "QtGlWindow.hpp"
#include "ui_qtglwindow.h"

#include "QtGlWidget.hpp"

QtGlWindow::QtGlWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QtGlWindow) {
  ui->setupUi(this);  
}

QtGlWindow::~QtGlWindow() {
  delete ui;
  
}

void QtGlWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
  
}
