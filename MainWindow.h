//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_MAINWINDOW_H
#define INC_1760_MAINWINDOW_H

#include "global/Macro.h"
#include "GLWidget.h"
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QKeyEvent>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow() {
    widget = new GLWidget;
    setCentralWidget(widget);
    setMouseTracking(true);
    connect(widget, SIGNAL(setWindowName(const QString&)), this, SLOT(setName(const QString&)));
    connect(widget, SIGNAL(terminate()), this, SLOT(close()));
  }

  void keyPressEvent(QKeyEvent* event) override {
    widget->keyPress(event->key());
  }

  void keyReleaseEvent(QKeyEvent* event) override {
    widget->keyRelease(event->key());
  }

  void mousePressEvent(QMouseEvent* event) override {
    widget->mouseClick(event->pos());
  }

  void mouseReleaseEvent(QMouseEvent* event) override {
    widget->mouseRelease(event->pos());
  }

  void mouseMoveEvent(QMouseEvent* event) override {
    widget->mouseMove(event->pos());
  }

public slots:

  void setName(const QString& name) {
    setWindowTitle(name);
  };

private:
  GLWidget* widget;

};


#endif //INC_1760_MAINWINDOW_H
