//
// Created by Yixiang Tu on 25/05/2018.
//

#ifndef INC_1760_GLWIDGET_H
#define INC_1760_GLWIDGET_H

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <vector>
#include "global/Macro.h"
#include "Transform3D.h"
#include "KeyMonitor.h"
#include "template/Scene.h"

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions {
Q_OBJECT

  friend class Body;

public:
  GLWidget();

  //explicit GLWidget(QWidget *parent = nullptr);
  ~GLWidget() override;

  void changeScene(int sceneId, void* data = nullptr);

  void changeSceneImmediately(int sceneId, void* data = nullptr);

  void nextScene();

protected:
  void initializeGL() override;

  void resizeGL(int width, int height) override;

  void paintGL() override;

public slots:

  void onFrame();

  void keyPress(int key);

  void keyRelease(int key);

  void mouseClick(const QPoint& position);

  void mouseMove(const QPoint& position);

  void mouseRelease(const QPoint& position);

signals:

  void setWindowName(const QString&);

  void terminate();


protected:
  QMatrix4x4 perspective;

  void renderText();

  Scene* activeScene;

  bool changingScene = false;

};


#endif //INC_1760_GLWIDGET_H
